// #include "Hooks.h"
// #include "Manager.h"


#include "JContainers/jc_interface.h"

/*
void MessageHandler(SKSE::MessagingInterface::Message* a_message)
{
	switch (a_message->type) {
	case SKSE::MessagingInterface::kPostLoad:
		BaseObjectSwapper::Install();
		break;
	case SKSE::MessagingInterface::kPostPostLoad:
		{
			logger::info("{:*^30}", "MERGES");
			MergeMapperPluginAPI::GetMergeMapperInterface001();
			if (g_mergeMapperInterface) {
				const auto version = g_mergeMapperInterface->GetBuildNumber();
				logger::info("Got MergeMapper interface buildnumber {}", version);
			} else {
				logger::info("MergeMapper not detected");
			}
		}
		break;
	case SKSE::MessagingInterface::kDataLoaded:
		FormSwap::Manager::GetSingleton()->PrintConflicts();
		break;
	default:
		break;
	}
}
*/



namespace
{
	template <class F>
	void get_class_function(const jc::reflection_interface* refl, const char* a_funcName, const char* a_className, F& a_func)
	{
		a_func = reinterpret_cast<F>(refl->tes_function_of_class(a_funcName, a_className));
		if (!a_func) {
			logger::error("slavetats_ng: couldn't obtain function {}::{}", a_className, a_funcName);
		} else {
			logger::info("slavetats_ng: found function {}::{}", a_className, a_funcName);
		}
	}
}

namespace slavetats_ng
{
	namespace jcwrapper
	{
		inline void* jc_default_domain = nullptr;



		// JMap
		inline int32_t           (*jmap_all_keys_func)(void*, int32_t a_obj) = nullptr;
		inline int32_t           (*jmap_all_values_func)(void*, int32_t a_obj) = nullptr;
		inline int32_t           (*jmap_count_func)(void*, int32_t a_obj) = nullptr;
		inline float             (*jmap_get_flt_func)(void*, int32_t a_obj, RE::BSFixedString a_key, float a_default) = nullptr;
		inline int32_t           (*jmap_get_int_func)(void*, int32_t a_obj, RE::BSFixedString a_key, int32_t a_default) = nullptr;
		inline int32_t           (*jmap_get_obj_func)(void*, int32_t a_obj, RE::BSFixedString a_key, int32_t a_default) = nullptr;
		inline RE::BSFixedString (*jmap_get_str_func)(void*, int32_t a_obj, RE::BSFixedString a_key, RE::BSFixedString a_default) = nullptr;
		inline bool              (*jmap_has_key_func)(void*, int32_t a_obj, RE::BSFixedString a_key) = nullptr;
		inline RE::BSFixedString (*jmap_next_key_func)(void*, int32_t a_obj, RE::BSFixedString a_previous_key, RE::BSFixedString a_end_key) = nullptr;
		inline int32_t           (*jmap_object_func)(void*) = nullptr;
		inline void              (*jmap_set_flt_func)(void*, int32_t a_obj, RE::BSFixedString a_key, float a_value) = nullptr;
		inline void              (*jmap_set_int_func)(void*, int32_t a_obj, RE::BSFixedString a_key, int32_t a_value) = nullptr;
		inline void              (*jmap_set_obj_func)(void*, int32_t a_obj, RE::BSFixedString a_key, int32_t a_value) = nullptr;
		inline void              (*jmap_set_str_func)(void*, int32_t a_obj, RE::BSFixedString a_key, RE::BSFixedString a_value) = nullptr;

		// JArray
		inline void              (*jarray_add_obj_func)(void*, int32_t a_arr, int32_t a_obj, int32_t a_index) = nullptr;
		inline void              (*jarray_clear_func)(void*, int32_t a_obj) = nullptr;
		inline int32_t           (*jarray_count_func)(void*, int32_t a_obj) = nullptr;
		inline void		         (*jarray_erase_index_func)(void*, int32_t a_arr, int32_t a_index) = nullptr;
		inline int32_t           (*jarray_get_obj_func)(void*, int32_t a_obj, int32_t a_index) = nullptr;
		inline RE::BSFixedString (*jarray_get_str_func)(void*, int32_t a_obj, int32_t a_index, RE::BSFixedString a_default) = nullptr;

		// JValue (object)
		inline int32_t (*jvalue_add_to_pool_func)(void*, int32_t a_obj, RE::BSFixedString a_pool_name) = nullptr;
		inline int32_t (*jvalue_clean_pool_func)(void*, RE::BSFixedString a_pool_name) = nullptr;
		inline bool    (*jvalue_is_array_func)(void*, int32_t a_obj) = nullptr;
		inline int32_t (*jvalue_read_from_directory_func)(void*, RE::BSFixedString a_directory_path, RE::BSFixedString a_extension) = nullptr;
		inline int32_t (*jvalue_read_from_file_func)(void*, RE::BSFixedString a_file_path) = nullptr;
		inline int32_t (*jvalue_write_to_file_func)(void*, int32_t a_obj, RE::BSFixedString a_file_path) = nullptr;

		// JDB
		inline int32_t (*jdb_solve_obj_func)(void*, RE::BSFixedString a_path, int32_t a_default_obj) = nullptr;
		inline int32_t (*jdb_solve_obj_setter_func)(void*, RE::BSFixedString a_path, int32_t a_obj, bool a_create_missing_keys) = nullptr;


		class JCWrapper
		{
		public:
			static inline void Init(const jc::root_interface* root)
			{
				auto refl = root->query_interface<jc::reflection_interface>();
				
				// JMap
				get_class_function(refl, "allKeys", "JMap", jmap_all_keys_func);
				get_class_function(refl, "allValues", "JMap", jmap_all_values_func);
				get_class_function(refl, "count", "JMap", jmap_count_func);
				get_class_function(refl, "getFlt", "JMap", jmap_get_flt_func);
				get_class_function(refl, "getInt", "JMap", jmap_get_int_func);
				get_class_function(refl, "getObj", "JMap", jmap_get_obj_func);
				get_class_function(refl, "getStr", "JMap", jmap_get_str_func);
				get_class_function(refl, "hasKey", "JMap", jmap_has_key_func);
				get_class_function(refl, "nextKey", "JMap", jmap_next_key_func);
				get_class_function(refl, "object", "JMap", jmap_object_func);
				get_class_function(refl, "setFlt", "JMap", jmap_set_flt_func);
				get_class_function(refl, "setInt", "JMap", jmap_set_int_func);
				get_class_function(refl, "setObj", "JMap", jmap_set_obj_func);
				get_class_function(refl, "setStr", "JMap", jmap_set_str_func);

				// JArray
				get_class_function(refl, "addObj", "JArray", jarray_add_obj_func);
				get_class_function(refl, "clear", "JArray", jarray_clear_func);
				get_class_function(refl, "count", "JArray", jarray_count_func);
				get_class_function(refl, "eraseIndex", "JArray", jarray_erase_index_func);
				get_class_function(refl, "getObj", "JArray", jarray_get_obj_func);
				get_class_function(refl, "getStr", "JArray", jarray_get_str_func);

				// JValue (object)
				get_class_function(refl, "addToPool", "JValue", jvalue_add_to_pool_func);
				get_class_function(refl, "cleanPool", "JValue", jvalue_clean_pool_func);
				get_class_function(refl, "isArray", "JValue", jvalue_is_array_func);
				get_class_function(refl, "readFromDirectory", "JValue", jvalue_read_from_directory_func);
				get_class_function(refl, "readFromFile", "JValue", jvalue_read_from_file_func);
				get_class_function(refl, "writeToFile", "JValue", jvalue_write_to_file_func);

				// JDB
				get_class_function(refl, "solveObj", "JDB", jdb_solve_obj_func);
				get_class_function(refl, "solveObjSetter", "JDB", jdb_solve_obj_setter_func);
			}

		};
	}

}










static std::string MyNativeFunction(RE::StaticFunctionTag*)
{
	return "Hello from C++!";
}

namespace
{
	bool BindPapyrusFunctions(RE::BSScript::IVirtualMachine* vm)
	{
		vm->RegisterFunction("MyNativeFunction", "MyPapyrusScript", MyNativeFunction);
		return true;
	}

	void InitializePapyrus()
	{
		SKSE::GetPapyrusInterface()->Register(BindPapyrusFunctions);
	}

	void InitializeLog()
	{
		auto path = logger::log_directory();
		if (!path) {
			stl::report_and_fail("Failed to find standard logging directory"sv);
		}

		*path /= fmt::format(FMT_STRING("{}.log"), Version::PROJECT);
		auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);

		auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));

		log->set_level(spdlog::level::info);
		log->flush_on(spdlog::level::info);

		spdlog::set_default_logger(std::move(log));
		spdlog::set_pattern("[%H:%M:%S:%e] %v"s);

		logger::info(FMT_STRING("{} v{}"), Version::PROJECT, Version::NAME);
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
		default:
			break;
		}
	}
}



#ifdef SKYRIM_AE
extern "C" DLLEXPORT constinit auto SKSEPlugin_Version = []() {
	SKSE::PluginVersionData v;
	v.PluginVersion({ Version::MAJOR, Version::MINOR, Version::PATCH });
	v.PluginName("SlaveTatsNG");
	v.AuthorName("nopse0");
	v.UsesAddressLibrary();
	v.UsesUpdatedStructs();
	v.CompatibleVersions({ SKSE::RUNTIME_LATEST });

	return v;
}();
#else
extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Query(const SKSE::QueryInterface* a_skse, SKSE::PluginInfo* a_info)
{
	a_info->infoVersion = SKSE::PluginInfo::kVersion;
	a_info->name = "SlaveTatsNG";
	a_info->version = Version::MAJOR;

	if (a_skse->IsEditor()) {
		logger::critical("Loaded in editor, marking as incompatible"sv);
		return false;
	}

	const auto ver = a_skse->RuntimeVersion();
	if (ver
#	ifndef SKYRIMVR
		< SKSE::RUNTIME_1_5_39
#	else
		> SKSE::RUNTIME_VR_1_4_15_1
#	endif
	) {
		logger::critical(FMT_STRING("Unsupported runtime version {}"), ver.string());
		return false;
	}

	return true;
}
#endif

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
