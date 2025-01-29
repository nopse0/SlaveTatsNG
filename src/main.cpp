#include "../include/jcontainers_wrapper.h"
#include "../include/nioverride_wrapper.h"
#include "../include/papyrus_interface.h"
#include "../include/high_level_api.h"
#include "../include/primary_api.h"
#include "../include/tattoo.h"
#include "../include/overlays.h"
#include "../include/query.h"
#include "../include/cache.h"
#include "../include/logging.h"

namespace slavetats_ng
{
	const char* const config_file = "data/skse/plugins/SlaveTatsNG.ini";

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
			if (a_message->type == SKSE::MessagingInterface::kPostLoad) {
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
		case SKSE::MessagingInterface::kDataLoaded:
			slavetats_ng::jcwrapper::JCWrapper::GetSingleton()->Init();
			slavetats_ng::skee_wrapper::NiOverride::Init();
			break;
				
		default:
			break;
		}
	}
}

extern "C"
{
	DLLEXPORT bool simple_add_tattoo(RE::Actor* target, RE::BSFixedString section, RE::BSFixedString name, int color = 0, bool last = true, bool silent = false, float alpha = 1.0) {
		return slavetats_ng::simple_add_tattoo(target, section, name, color, last, silent, alpha);
	}
	DLLEXPORT bool simple_remove_tattoo(RE::Actor* target, RE::BSFixedString section, RE::BSFixedString name, bool last = true, bool silent = false) {
		return slavetats_ng::simple_remove_tattoo(target, section, name, last, silent);
	}
	DLLEXPORT bool tattoo_matches(int a_template, int tattoo, bool include_configurable = false) {
		return slavetats_ng::tattoo_matches(a_template, tattoo, include_configurable);
	}
	DLLEXPORT bool is_tattoo(int tattoo) {
		return slavetats_ng::is_tattoo(tattoo);
	}
	DLLEXPORT int find_tattoo(int array, int a_template) {
		return slavetats_ng::find_tattoo(array, a_template);
	}
	DLLEXPORT int find_excluding_tattoo(int applied, int tattoo) {
		return slavetats_ng::find_excluding_tattoo(applied, tattoo);
	}
	DLLEXPORT int find_required_tattoo(int applied, int tattoo) {
		return slavetats_ng::find_required_tattoo(applied, tattoo);
	}
	DLLEXPORT bool has_required_plugin(int tattoo) {
		return slavetats_ng::has_required_plugin(tattoo);
	}
	DLLEXPORT void _cache_tattoo(int cache, int tattoo) {
		slavetats_ng::_cache_tattoo(cache, tattoo);
	}
	DLLEXPORT int compile_cache() {
		return slavetats_ng::compile_cache();
	}
	DLLEXPORT int acquire_cache() {
		return slavetats_ng::acquire_cache();
	}
	DLLEXPORT void _append(int dest, int val) {
		slavetats_ng::_append(dest, val);
	}
	DLLEXPORT void _extend_matching(int dest, int src, int a_template, int applied = 0, RE::BSFixedString domain = "default") {
		slavetats_ng::_extend_matching(dest, src, a_template, applied, domain);
	}
	DLLEXPORT bool query_available_tattoos(int a_template, int matches, int applied = 0, RE::BSFixedString domain = "default") {
		return slavetats_ng::query_available_tattoos(a_template, matches, applied, domain);
	}
	DLLEXPORT bool query_applied_tattoos(RE::Actor* target, int a_template, int matches, RE::BSFixedString except_area = "", int except_slot = -1) {
		return slavetats_ng::query_applied_tattoos(target, a_template, matches, except_area, except_slot);
	}
	DLLEXPORT bool query_applied_tattoos_with_attribute(RE::Actor* target, RE::BSFixedString attrib, int matches, RE::BSFixedString except_area = "", int except_slot = -1) {
		return slavetats_ng::query_applied_tattoos_with_attribute(target, attrib, matches, except_area, except_slot);
	}
	DLLEXPORT bool has_applied_tattoos_with_attribute(RE::Actor* target, RE::BSFixedString attrib, RE::BSFixedString except_area = "", int except_slot = -1) {
		return slavetats_ng::has_applied_tattoos_with_attribute(target, attrib, except_area, except_slot);
	}
	DLLEXPORT bool remove_tattoos(RE::Actor* target, int a_template, bool ignore_lock = false, bool silent = false) {
		return slavetats_ng::remove_tattoos(target, a_template, ignore_lock, silent);
	}
	DLLEXPORT bool remove_tattoo_from_slot(RE::Actor* target, RE::BSFixedString area, int slot) {
		return slavetats_ng::remove_tattoo_from_slot(target, area, slot);
	}
	DLLEXPORT int get_applied_tattoo_in_slot(RE::Actor* target, RE::BSFixedString area, int slot) {
		return slavetats_ng::get_applied_tattoo_in_slot(target, area, slot);
	}
	DLLEXPORT bool get_applied_tattoos_by_area(RE::Actor* target, int on_body, int on_face, int on_hands, int on_feet) {
		return slavetats_ng::get_applied_tattoos_by_area(target, on_body, on_face, on_hands, on_feet);
	}
	DLLEXPORT bool external_slots(RE::Actor* target, RE::BSFixedString area, int matches) {
		return slavetats_ng::external_slots(target, area, matches);
	}
	DLLEXPORT bool add_tattoo(RE::Actor* target, int tattoo, int slot = -1, bool ignore_lock = false, bool silent = false) {
		return slavetats_ng::add_tattoo(target, tattoo, slot, ignore_lock, silent);
	}
	DLLEXPORT int add_and_get_tattoo(RE::Actor* target, int tattoo, int slot = -1, bool ignore_lock = false, bool silent = false) {
		return slavetats_ng::add_and_get_tattoo(target, tattoo, slot, ignore_lock, silent);
	}
	DLLEXPORT RE::TESForm* get_form(int tattoo, RE::BSFixedString plugin_field, RE::BSFixedString formid_field, RE::TESForm* a_default = nullptr) {
		return slavetats_ng::get_form(tattoo, plugin_field, formid_field, a_default);
	}
	// Insert tattoo magic here when finished
	DLLEXPORT bool upgrade_tattoos(RE::Actor* target) {
		return slavetats_ng::upgrade_tattoos(target);
	}
	DLLEXPORT bool synchronize_tattoos(RE::Actor* target, bool silent = false) {
		return slavetats_ng::synchronize_tattoos(target, silent);
	}
	DLLEXPORT void _log_jcontainer(int jc, RE::BSFixedString indent) {
		return slavetats_ng::_log_jcontainer(jc, indent);
	}
	DLLEXPORT void log_tattoo(RE::BSFixedString message, int tattoo) {
		return slavetats_ng::log_tattoo(message, tattoo);
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
