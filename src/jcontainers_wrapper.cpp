#include <jcontainers_wrapper.h>

namespace slavetats_ng
{
	namespace jcwrapper
	{

		void JCWrapper::PreInit(const jc::root_interface* a_root)
		{
			root_interface = a_root;
		}

		void JCWrapper::Init()
		{
			if (!root_interface) {
				logger::info("JCWrapper::Init(): JContainers root interface not set.");
				std::abort();
			}
			logger::info("JCWrapper::Init() started");

			auto refl = root_interface->query_interface<jc::reflection_interface>();
			logger::info("query_interface<jc::reflection_interface>: refl = {}", (void*)refl);
			if (!refl) {
				logger::info("JCWrapper::Init(): Could not get JContainers reflection interface.");
				std::abort();
			}

			auto dom = root_interface->query_interface<jc::domain_interface>();
			logger::info("query_interface<jc::domain_interface>: dom = {}", (void*)dom);
			if (!dom) {
				logger::info("JCWrapper::Init(): Could not get JContainers domain interface.");
				std::abort();
			}

			jc_default_domain = dom->get_default_domain();
			logger::info("dom->get_default_domain(): default_domain = {}", (void*)jc_default_domain);
			if (!jc_default_domain) {
				logger::info("JCWrapper::Init(): Could not get JContainers default domain.");
				std::abort();
			}

			// JMap
			get_class_function(refl, "allKeys", "JMap", jmap_all_keys_func);
			logger::info("After get_class_function(allKeys, JMap)");
			get_class_function(refl, "allValues", "JMap", jmap_all_values_func);
			get_class_function(refl, "count", "JMap", jmap_count_func);
			get_class_function(refl, "getFlt", "JMap", jmap_get_flt_func);
			get_class_function(refl, "getForm", "JMap", jmap_get_form_func);
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
			get_class_function(refl, "valueType", "JMap", jmap_value_type_func);

			// JArray
			get_class_function(refl, "addFromArray", "JArray", jarray_add_from_array_func);
			get_class_function(refl, "addObj", "JArray", jarray_add_obj_func);
			get_class_function(refl, "addInt", "JArray", jarray_add_int_func);
			get_class_function(refl, "clear", "JArray", jarray_clear_func);
			get_class_function(refl, "count", "JArray", jarray_count_func);
			get_class_function(refl, "eraseIndex", "JArray", jarray_erase_index_func);
			get_class_function(refl, "findInt", "JArray", jarray_find_int_func);
			get_class_function(refl, "findObj", "JArray", jarray_find_obj_func);
			get_class_function(refl, "getInt", "JArray", jarray_get_int_func);
			get_class_function(refl, "getFlt", "JArray", jarray_get_flt_func);
			get_class_function(refl, "getObj", "JArray", jarray_get_obj_func);
			get_class_function(refl, "getStr", "JArray", jarray_get_str_func);
			get_class_function(refl, "object", "JArray", jarray_object_func);
			get_class_function(refl, "valueType", "JArray", jarray_value_type_func);

			// JValue (object)
			get_class_function(refl, "addToPool", "JValue", jvalue_add_to_pool_func);
			get_class_function(refl, "cleanPool", "JValue", jvalue_clean_pool_func);
			get_class_function(refl, "deepCopy", "JValue", jvalue_deep_copy_func);
			get_class_function(refl, "isArray", "JValue", jvalue_is_array_func);
			get_class_function(refl, "isFormMap", "JValue", jvalue_is_form_map_func);
			get_class_function(refl, "isMap", "JValue", jvalue_is_map_func);
			get_class_function(refl, "readFromDirectory", "JValue", jvalue_read_from_directory_func);
			get_class_function(refl, "readFromFile", "JValue", jvalue_read_from_file_func);
			get_class_function(refl, "shallowCopy", "JValue", jvalue_shallow_copy_func);
			get_class_function(refl, "writeToFile", "JValue", jvalue_write_to_file_func);

			// JDB
			get_class_function(refl, "solveObj", "JDB", jdb_solve_obj_func);
			get_class_function(refl, "solveObjSetter", "JDB", jdb_solve_obj_setter_func);
			get_class_function(refl, "setObj", "JDB", jdb_set_obj_func);
			get_class_function(refl, "root", "JDB", jdb_root_func);

			// JFormDB
			get_class_function(refl, "getObj", "JFormDB", jformdb_get_obj_func);
			get_class_function(refl, "getInt", "JFormDB", jformdb_get_int_func);
			get_class_function(refl, "getStr", "JFormDB", jformdb_get_str_func);
			get_class_function(refl, "makeEntry", "JFormDB", jformdb_make_entry_func);
			get_class_function(refl, "setEntry", "JFormDB", jformdb_set_entry_func);
			get_class_function(refl, "setInt", "JFormDB", jformdb_set_int_func);
			get_class_function(refl, "setObj", "JFormDB", jformdb_set_obj_func);
			get_class_function(refl, "setStr", "JFormDB", jformdb_set_str_func);

			// JAtomic
			get_class_function(refl, "compareExchangeInt", "JAtomic", jatomic_compare_exchange_int_func);
			get_class_function(refl, "fetchAddInt", "JAtomic", jatomic_fetch_add_int_func);
			
			// JContainers
			get_class_function(refl, "fileExistsAtPath", "JContainers", jcontainers_file_exists_at_path_func);
		}
	}

}

