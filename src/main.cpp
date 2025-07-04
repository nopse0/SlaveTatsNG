#include "../include/jcontainers_wrapper.h"
#include "../include/nioverride_wrapper.h"
#include "../include/papyrus_interface.h"
#include "config.h"
#include "threading.h"
#include "utility.h"
#include "cache.h"
#include "skee_addresses.h"

#include "SlaveTatsNG_InterFace.h"

namespace SlaveTatsNG
{
	extern Addresses addresses_instance;
}

namespace slavetats_ng
{
	const char* const config_file = "data/skse/plugins/SlaveTatsNG/SlaveTatsNG.ini";
}

namespace
{
	void InitializePapyrus()
	{
		SKSE::GetPapyrusInterface()->Register(
			[](RE::BSScript::IVirtualMachine* vm) { return slavetats_ng::papyrus::register_functions(vm, 
				slavetats_ng::config::Config::GetSingleton()->use_vmhook); });
	}

	void InitializeLog()
	{
		auto path = logger::log_directory();
		if (!path) {
			SKSE::stl::report_and_fail("Failed to find standard logging directory"sv);
		}

		auto pluginName = SKSE::PluginDeclaration::GetSingleton()->GetName();
		*path /= fmt::format(FMT_STRING("{}.log"), pluginName);

		auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);

		auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));

		log->set_level(spdlog::level::info);
		log->flush_on(spdlog::level::info);

		spdlog::set_default_logger(std::move(log));
		spdlog::set_pattern("[%H:%M:%S:%e] %v"s);

		auto pluginVersion = SKSE::PluginDeclaration::GetSingleton()->GetVersion();
		logger::info(FMT_STRING("{} v{}"), pluginName, pluginVersion.string());
	}

	std::string getJContainersPluginName()
	{
		auto patchVersion = REL::Module::get().version().patch();

		std::string pluginName{ "JContainers64" };
		if (REL::Module::IsVR()) {
			pluginName = "JContainersVR";
		} else if (patchVersion == 659 || patchVersion == 1179) {
			pluginName = "JContainersGOG";
		}

		return pluginName;
	}

	void messagingHook(SKSE::MessagingInterface::Message* a_message)
	{
		switch (a_message->type) {
		case SKSE::MessagingInterface::kPostLoad:
			{
				std::string pluginName = getJContainersPluginName();
				logger::info("JContainers Plugin Name seems to be: {}", pluginName);

				SKSE::GetMessagingInterface()->RegisterListener(pluginName.c_str(), [](SKSE::MessagingInterface::Message* a_msg) {
					logger::info("a_msg={}, msgtype={}, message_root_interface={}", (void*)a_msg, a_msg ? a_msg->type : -1, (int)jc::message_root_interface);
					if (a_msg && a_msg->type == jc::message_root_interface) {
						const jc::root_interface* root = jc::root_interface::from_void(a_msg->data);
						logger::info("root_interface={}", (void*)root);
						if (root)
							// Seems to be a deadlock or so here, so we defer the actual JContainers initialization
							slavetats_ng::jcwrapper::JCWrapper::GetSingleton()->PreInit(root);
					}
				});
			}
			break;

		case SKSE::MessagingInterface::kPostPostLoad:
			// publish C++ interface	
			SKSE::GetMessagingInterface()->Dispatch(SlaveTatsNG::MessageType::Interface, (void*)&SlaveTatsNG::addresses_instance, sizeof(void*), nullptr);
			break;

		case SKSE::MessagingInterface::kDataLoaded:
			{
				slavetats_ng::jcwrapper::JCWrapper::GetSingleton()->Init();
				slavetats_ng::skee_wrapper::NiOverride::Init();
			}
			break;

		case SKSE::MessagingInterface::kSaveGame:
			{
				auto system = slavetats_ng::utility::System::GetSingleton();
				system->set_last_save_time();
			}
			break;

		case SKSE::MessagingInterface::kPostLoadGame:
			{
				// Force SlaveTats to update it's cache of installed tattoos
				auto areas = slavetats_ng::compile_cache();
				logger::info("kPostLoadGame: Recompiled SlaveTats cache, cache id: {}", areas);
			}
			break;

		default:
			break;
		}
	}
}

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
{
	SKSE::Init(a_skse);

	InitializeLog();

	CSimpleIniA config;
	SI_Error    rc = config.LoadFile(slavetats_ng::config_file);
	logger::info("Load {}, result = {}", slavetats_ng::config_file, rc);
	auto ini = slavetats_ng::config::Config::GetSingleton();
	logger::info("blank_texture_name = {}", ini->blank_texture_name);
	if (rc >= 0) {
		clib_util::ini::get_value(config, ini->skee_dll_name, "Config", "skeeDllName", ";");
		logger::info("skee_dll_name = {}", ini->skee_dll_name);
		clib_util::ini::get_value(config, ini->blank_texture_name, "Config", "blankTextureName", ";");
		logger::info("blank_texture_name = {}", ini->blank_texture_name);
		clib_util::ini::get_value(config, ini->use_vmhook, "Config", "vmHook", ";");
		logger::info("blank_texture_name = {}", ini->blank_texture_name);
	}
	
	InitializePapyrus();

	logger::info("Game version : {}", a_skse->RuntimeVersion().string());

	const auto messaging = SKSE::GetMessagingInterface();
	messaging->RegisterListener(messagingHook);

	// This doesn't work, the thread which executes SKSE tasks changes over the time, it isn't the Skyrim main thread itself (I guess, it is a forked thread,
	// and the Skyrim main thread only waits, until it's finished)
	SKSE::GetTaskInterface()->AddTask([] {
		auto id = std::this_thread::get_id();
		auto system = slavetats_ng::threading::System::GetSingleton();
		{
			std::lock_guard lk(system->main_thread_id_mutex);
			system->_main_thread_id = id;
			system->main_thread_id_initialized = true;
		}
		system->main_thread_id_cv.notify_all();
		logger::info("main thread id is {}", slavetats_ng::threading::thread_id_to_string(id));
	});

	return true;
}
