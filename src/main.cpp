#include "../include/jcontainers_wrapper.h"
#include "../include/nioverride_wrapper.h"
#include "../include/papyrus_interface.h"

/*
static std::string MyNativeFunction(RE::StaticFunctionTag*)
{
	return "Hello from C++!";
}
*/

namespace
{
	/*
	bool BindPapyrusFunctions(RE::BSScript::IVirtualMachine* vm)
	{
		vm->RegisterFunction("MyNativeFunction", "MyPapyrusScript", MyNativeFunction);
		return true;
	}
	*/

	void InitializePapyrus()
	{
		SKSE::GetPapyrusInterface()->Register(slavetats_ng::papyrus::register_functions);
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

		logger::info("Hello World Test Version");

		logger::info(FMT_STRING("{} v{}"), Plugin::NAME, Plugin::VERSION.string());
	}

	void messagingHook(SKSE::MessagingInterface::Message* a_message)
	{
		switch (a_message->type) {
		case SKSE::MessagingInterface::kPostLoad:
			if (a_message->type == SKSE::MessagingInterface::kPostLoad) {
				std::string pluginName{ "JContainers64" };
				logger::info("JContainers Plugin Name: {}", pluginName);

				SKSE::GetMessagingInterface()->RegisterListener(pluginName.c_str(), [](SKSE::MessagingInterface::Message* a_msg) {
					if (a_msg && a_msg->type == jc::message_root_interface) {
						if (const jc::root_interface* root = jc::root_interface::from_void(a_msg->data))
							slavetats_ng::jcwrapper::JCWrapper::Init(root);
					}
				});
			}
			break;
		case SKSE::MessagingInterface::kDataLoaded:
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
	InitializePapyrus();

	logger::info("Game version : {}", a_skse->RuntimeVersion().string());

	const auto messaging = SKSE::GetMessagingInterface();
	messaging->RegisterListener(messagingHook);

	return true;
}
