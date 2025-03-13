#include "../include/jcontainers_wrapper.h"
#include "../include/nioverride_wrapper.h"
#include "../include/papyrus_interface.h"

#include "SlaveTatsNG_InterFace.h"

namespace SlaveTatsNG
{
	extern Addresses addresses_instance;
}

namespace slavetats_ng
{
	const char* const config_file = "data/skse/plugins/SlaveTatsNG/SlaveTatsNG.ini";

	class config
	{
	public:
		inline static bool vm_hook = false;
	};
}

namespace
{
	void InitializePapyrus()
	{
		SKSE::GetPapyrusInterface()->Register(
			[](RE::BSScript::IVirtualMachine* vm) { return slavetats_ng::papyrus::register_functions(vm, slavetats_ng::config::vm_hook); });
	}

	void InitializeLog()
	{
		auto path = logger::log_directory();
		if (!path) {
			stl::report_and_fail("Failed to find standard logging directory"sv);
		}

		*path /= fmt::format(FMT_STRING("{}.log"), Plugin::NAME);
		auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);

		auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));

		log->set_level(spdlog::level::info);
		log->flush_on(spdlog::level::info);

		spdlog::set_default_logger(std::move(log));
		spdlog::set_pattern("[%H:%M:%S:%e] %v"s);

		logger::info(FMT_STRING("{} v{}"), Plugin::NAME, Plugin::VERSION.string());
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
			slavetats_ng::jcwrapper::JCWrapper::GetSingleton()->Init();
			slavetats_ng::skee_wrapper::NiOverride::Init();
			break;


		default:
			break;
		}
	}
}


extern "C" DLLEXPORT constinit auto SKSEPlugin_Version = []() noexcept {
	SKSE::PluginVersionData v;
	v.PluginName(Plugin::NAME.data());
	v.PluginVersion(Plugin::VERSION);
	v.UsesAddressLibrary(true);
	v.HasNoStructUse();
	return v;
}();

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Query([[maybe_unused]] const SKSE::QueryInterface* a_skse, SKSE::PluginInfo* a_info)
{
	a_info->name = SKSEPlugin_Version.pluginName;
	a_info->infoVersion = SKSE::PluginInfo::kVersion;
	a_info->version = SKSEPlugin_Version.pluginVersion;
	return true;
}

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
{
	SKSE::Init(a_skse);

	InitializeLog();

	CSimpleIniA config;
	SI_Error    rc = config.LoadFile(slavetats_ng::config_file);
	logger::info("Load {}, result = {}", slavetats_ng::config_file, rc);
	if (rc >= 0) {
		clib_util::ini::get_value(config, slavetats_ng::config::vm_hook, "Config", "vmHook", ";");
	}
	
	InitializePapyrus();

	logger::info("Game version : {}", a_skse->RuntimeVersion().string());

	const auto messaging = SKSE::GetMessagingInterface();
	messaging->RegisterListener(messagingHook);

	return true;
}
