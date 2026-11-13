#include "jcontainers_wrapper.h"
#include "nioverride_wrapper.h"
#include "papyrus_interface.h"
#include "config.h"
#include "threading.h"
#include "utility.h"
#include "cache.h"
#include "skee_addresses.h"
#include "overlays.h"
#include "spdlog/cfg/helpers.h"
#include "spdlog/sinks/sink.h"
#include "synchronizer.h"

#include "SlaveTatsNG_InterFace.h"

namespace slavetats
{
	extern Addresses addresses_instance;
}

namespace slavetats_ng
{
	const char* const config_file = "data/skse/plugins/SlaveTatsNG/SlaveTatsNG.ini";
}

namespace main_loop
{
	void install();
}

namespace
{
	// 2. Erstelle den Event Sink 
	class NiNodeUpdateEventSink : public RE::BSTEventSink<SKSE::NiNodeUpdateEvent>, public singleton<NiNodeUpdateEventSink>
	{
	public:
		RE::BSEventNotifyControl ProcessEvent(const SKSE::NiNodeUpdateEvent* a_event, RE::BSTEventSource<SKSE::NiNodeUpdateEvent>* a_eventSource) override
		{
			if (!a_event || !a_event->reference) {
				return RE::BSEventNotifyControl::kContinue;
			}
			RE::Actor* actor = skyrim_cast<RE::Actor*>(a_event->reference);
			if (actor) {
				int applied = slavetats_ng::jcwrapper::JFormDB::getObj(actor, ".SlaveTats.applied");
				if (applied == 0) {
					return RE::BSEventNotifyControl::kContinue;
				}
				slavetats_ng::jcwrapper::JFormDB::setInt(actor, ".SlaveTats.updated", 1);
				auto formId = actor->GetFormID();
				SKSE::GetTaskInterface()->AddTask([actor]() {
					//slavetats_ng::synchronizer::synchronizer::get_instance().schedule(formId, 3);
					slavetats_ng::synchronize_tattoos(actor, true);
				});
			}
			return RE::BSEventNotifyControl::kContinue;
		}
	};

	void RegisterNiNodeSink()
	{
		auto eventSource = SKSE::GetNiNodeUpdateEventSource();
		if (eventSource) {
			eventSource->AddEventSink(&NiNodeUpdateEventSink::get_instance());
		}
	}


	void InitializePapyrus()
	{
		SKSE::GetPapyrusInterface()->Register(
			[](RE::BSScript::IVirtualMachine* vm) { return slavetats_ng::papyrus::register_functions(vm, 
				slavetats_ng::config::Config::get_instance().use_vmhook); });
	}

	void InitializeLoggers(std::optional<CSimpleIniA*> a_ini)
	{
		//event_chain::logger_custom::init_logger();
		//fsm::logger_custom::init_logger();
		//animation::logger_custom::init_logger();
		//controller::logger_custom::init_logger();
		//scanner::logger_custom::init_logger();

		spdlog::level::level_enum global_level = spdlog::level::info;
		std::string               cfg_string = "";

		if (a_ini.has_value()) {
			CSimpleIniA& ini = *a_ini.value();
			const char*  global_level_str = ini.GetValue("Config", "LogLevel", "info");
			logger::info("global_level_str = {}", global_level_str);
			cfg_string = global_level_str;

			const char* default_pattern = "[%T.%f] [%=5t] [%n] [%L] %v";
			const char* custom_pattern = ini.GetValue("Config", "LogPatternFormat", default_pattern);
			spdlog::set_pattern(custom_pattern);

			// 2. Alle Custom-Logger aus der Sektion [LogLevels] auslesen
			CSimpleIniA::TNamesDepend keys;
			if (ini.GetAllKeys("LogLevels", keys)) {
				for (const auto& key : keys) {
					const char* custom_level = ini.GetValue("LogLevels", key.pItem, "info");
					// Format anfügen: ,logger_name=level
					cfg_string += std::format(",{}={}", key.pItem, custom_level);
				}
			}
		} else {
			logger::info("InitializeLogging no ini, using defaults");
			cfg_string = "info";  // Fallback

			// Fallback-Pattern für den Fehlerfall
			if (auto def_logger = spdlog::default_logger()) {
				for (auto& sink : def_logger->sinks()) {
					sink->set_pattern("[%T.%f] [%n] [%L] %v");
				}
			}
		}

		// 3. Magierunde: spdlog konfigurieren!
		// Übergibt z.B.: "info,event_chain=debug,network=err"
		logger::info("InitializeLoggers cfg_string = {}", cfg_string);
		spdlog::cfg::helpers::load_levels(cfg_string);

		//event_chain::logger_custom::debug("event_chain::logger_custom");
		//fsm::logger_custom::debug("fsm::logger_custom");
		//animation::logger_custom::debug("animation::logger_custom");
		//controller::logger_custom::debug("controller::logger_custom");
		//scanner::logger_custom::debug("scanner::logger_custom");
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
							slavetats_ng::jcwrapper::JCWrapper::get_instance().PreInit(root);
					}
				});
			}
			break;

		case SKSE::MessagingInterface::kPostPostLoad:
			// publish C++ interface	
			SKSE::GetMessagingInterface()->Dispatch(slavetats::MessageType::Interface, (void*)&slavetats::addresses_instance, sizeof(void*), nullptr);
			break;

		case SKSE::MessagingInterface::kDataLoaded:
			{
				slavetats_ng::jcwrapper::JCWrapper::get_instance().Init();
				slavetats_ng::skee_wrapper::NiOverride::Init();
				//main_loop::install();
				//RegisterNiNodeSink();
			}
			break;

		case SKSE::MessagingInterface::kSaveGame:
			{
				auto system = &slavetats_ng::utility::System::get_instance();
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

extern "C" __declspec(dllexport) bool SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
{
	SKSE::Init(a_skse, SKSE::InitInfo{ .logRotate = 2 });

	CSimpleIniA ini;
	SI_Error rc = ini.LoadFile(slavetats_ng::config_file);
	logger::info("Load {}, result = {}", slavetats_ng::config_file, rc);
	auto config = &slavetats_ng::config::Config::get_instance();
	logger::info("blank_texture_name = {}", config->blank_texture_name);
	spdlog::level::level_enum level = spdlog::level::info;
	if (rc == SI_OK) {
		InitializeLoggers(&ini);
		config->skee_dll_name = ini.GetValue("Config", "skeeDllName", config->skee_dll_name.c_str());
		config->blank_texture_name = ini.GetValue("Config", "blankTextureName", config->blank_texture_name.c_str());
		std::string vmHookStr = ini.GetValue("Config", "vmHook", config->use_vmhook ? "true" : "false");
		config->use_vmhook = (vmHookStr == "true" || vmHookStr == "1");
	}
	
	InitializePapyrus();

	logger::info("Game version : {}", a_skse->RuntimeVersion().string());

	const auto messaging = SKSE::GetMessagingInterface();
	messaging->RegisterListener(messagingHook);

	// Memory for hooks
	SKSE::AllocTrampoline(1400);

	return true;
}
