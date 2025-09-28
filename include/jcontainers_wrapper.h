#pragma once

#include "JContainers/jc_interface.h"

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
		class JCWrapper : public clib_util::singleton::ISingleton<JCWrapper>
		{
		private:
			const jc::root_interface* root_interface = nullptr;
		public:
			void PreInit(const jc::root_interface* a_root);
			void Init();
		};

		inline void* jc_default_domain = nullptr;

		// JMap
		inline int32_t           (*jmap_all_keys_func)(void*, int32_t a_obj) = nullptr;
		inline int32_t           (*jmap_all_values_func)(void*, int32_t a_obj) = nullptr;
		inline int32_t           (*jmap_count_func)(void*, int32_t a_obj) = nullptr;
		inline float             (*jmap_get_flt_func)(void*, int32_t a_obj, RE::BSFixedString a_key, float a_default) = nullptr;
		inline RE::TESForm*      (*jmap_get_form_func)(void*, int32_t a_obj, RE::BSFixedString a_key, RE::TESForm* a_default) = nullptr;
		inline int32_t           (*jmap_get_int_func)(void*, int32_t a_obj, RE::BSFixedString a_key, int32_t a_default) = nullptr;
		inline int32_t           (*jmap_get_obj_func)(void*, int32_t a_obj, RE::BSFixedString a_key, int32_t a_default) = nullptr;
		inline RE::BSFixedString (*jmap_get_str_func)(void*, int32_t a_obj, RE::BSFixedString a_key, RE::BSFixedString a_default) = nullptr;
		inline bool              (*jmap_has_key_func)(void*, int32_t a_obj, RE::BSFixedString a_key) = nullptr;
		inline RE::BSFixedString (*jmap_next_key_func)(void*, int32_t a_obj, RE::BSFixedString a_previous_key, RE::BSFixedString a_end_key) = nullptr;
		inline int32_t           (*jmap_object_func)(void*) = nullptr;
		inline bool              (*jmap_remove_key_func)(void*, int32_t a_obj, RE::BSFixedString a_key) = nullptr;
		inline void              (*jmap_set_flt_func)(void*, int32_t a_obj, RE::BSFixedString a_key, float a_value) = nullptr;
		inline void              (*jmap_set_int_func)(void*, int32_t a_obj, RE::BSFixedString a_key, int32_t a_value) = nullptr;
		inline void              (*jmap_set_obj_func)(void*, int32_t a_obj, RE::BSFixedString a_key, int32_t a_value) = nullptr;
		inline void              (*jmap_set_str_func)(void*, int32_t a_obj, RE::BSFixedString a_key, RE::BSFixedString a_value) = nullptr;
		inline int32_t           (*jmap_value_type_func)(void*, int32_t a_obj, RE::BSFixedString a_key) = nullptr;

		// JArray
		inline void              (*jarray_add_from_array_func)(void*, int32_t a_arr, int32_t a_source, int32_t a_insert_index) = nullptr;
		inline void              (*jarray_add_obj_func)(void*, int32_t a_arr, int32_t a_obj, int32_t a_index) = nullptr;
		inline void				 (*jarray_add_int_func)(void*, int32_t a_arr, int32_t a_int, int32_t a_index) = nullptr;
		inline void              (*jarray_clear_func)(void*, int32_t a_obj) = nullptr;
		inline int32_t           (*jarray_find_int_func)(void*, int32_t a_arr, int32_t a_value, int32_t a_search_startindex) = nullptr;
		inline int32_t           (*jarray_find_obj_func)(void*, int32_t a_arr, int32_t a_container, int32_t a_search_startindex) = nullptr;
		inline int32_t           (*jarray_count_func)(void*, int32_t a_obj) = nullptr;
		inline void              (*jarray_erase_index_func)(void*, int32_t a_arr, int32_t a_index) = nullptr;
		inline int32_t           (*jarray_get_int_func)(void*, int32_t a_obj, int32_t a_index, int32_t a_default) = nullptr;
		inline float             (*jarray_get_flt_func)(void*, int32_t a_obj, int32_t a_index, float a_default) = nullptr;
		inline int32_t           (*jarray_get_obj_func)(void*, int32_t a_obj, int32_t a_index, int32_t a_default) = nullptr;
		inline RE::BSFixedString (*jarray_get_str_func)(void*, int32_t a_obj, int32_t a_index, RE::BSFixedString a_default) = nullptr;
		inline int32_t           (*jarray_object_func)(void*) = nullptr;
		inline int32_t           (*jarray_value_type_func)(void*, int32_t a_obj, int32_t a_index) = nullptr;


		// JValue (object)
		inline int32_t (*jvalue_add_to_pool_func)(void*, int32_t a_obj, RE::BSFixedString a_pool_name) = nullptr;
		inline int32_t (*jvalue_clean_pool_func)(void*, RE::BSFixedString a_pool_name) = nullptr;
		inline int32_t (*jvalue_deep_copy_func)(void*, int32_t a_obj) = nullptr;
		inline bool    (*jvalue_is_array_func)(void*, int32_t a_obj) = nullptr;
		inline bool    (*jvalue_is_form_map_func)(void*, int32_t a_obj) = nullptr;
		inline bool    (*jvalue_is_map_func)(void*, int32_t a_obj) = nullptr;
		inline int32_t (*jvalue_read_from_directory_func)(void*, RE::BSFixedString a_directory_path, RE::BSFixedString a_extension) = nullptr;
		inline int32_t (*jvalue_read_from_file_func)(void*, RE::BSFixedString a_file_path) = nullptr;
		inline int32_t (*jvalue_release_func)(void*, int32_t a_obj) = nullptr;
		inline void    (*jvalue_release_objects_with_tag_func)(void*, RE::BSFixedString a_tag) = nullptr;
		inline int32_t (*jvalue_retain_func)(void*, int32_t a_obj, RE::BSFixedString a_tag) = nullptr;

		inline int32_t (*jvalue_shallow_copy_func)(void*, int32_t a_obj) = nullptr;
		inline void    (*jvalue_write_to_file_func)(void*, int32_t a_obj, RE::BSFixedString a_file_path) = nullptr;

		// JDB
		inline int32_t (*jdb_solve_obj_func)(void*, RE::BSFixedString a_path, int32_t a_default_obj) = nullptr;
		inline bool    (*jdb_solve_obj_setter_func)(void*, RE::BSFixedString a_path, int32_t a_obj, bool a_create_missing_keys) = nullptr;
		inline void    (*jdb_set_obj_func)(void*, RE::BSFixedString a_path, int32_t a_obj) = nullptr;
		inline int32_t (*jdb_root_func)(void*) = nullptr;

		// JFormDB
		inline int32_t           (*jformdb_get_obj_func)(void*, RE::TESForm* a_fKey, RE::BSFixedString a_key) = nullptr;
		inline int32_t           (*jformdb_get_int_func)(void*, RE::TESForm* a_fKey, RE::BSFixedString a_key) = nullptr;
		inline RE::BSFixedString (*jformdb_get_str_func)(void*, RE::TESForm* a_fKey, RE::BSFixedString a_key) = nullptr;
		inline int32_t           (*jformdb_make_entry_func)(void*, RE::BSFixedString a_storage_name, RE::TESForm* a_fKey) = nullptr;
		inline void              (*jformdb_set_entry_func)(void*, RE::BSFixedString a_storage_name, RE::TESForm* a_fKey, int32_t a_entry) = nullptr;
		inline void              (*jformdb_set_int_func)(void*, RE::TESForm* a_fKey, RE::BSFixedString a_key, int32_t a_value) = nullptr;
		inline void              (*jformdb_set_obj_func)(void*, RE::TESForm* a_fKey, RE::BSFixedString a_key, int32_t a_container) = nullptr;
		inline void              (*jformdb_set_str_func)(void*, RE::TESForm* a_fKey, RE::BSFixedString a_key, RE::BSFixedString a_value) = nullptr;

		// JAtomic
		inline int32_t (*jatomic_fetch_add_int_func)(void*, int32_t a_obj, RE::BSFixedString a_path, int32_t a_value, int32_t a_initial_value,
			bool a_create_missing_keys, int32_t a_result_on_error) = nullptr;
		inline int32_t (*jatomic_compare_exchange_int_func)(void*, int32_t a_obj, RE::BSFixedString a_path, int32_t a_desired, int32_t a_expected,
			bool a_create_missing_keys, int32_t a_result_on_error) = nullptr;


		// JContainers
		inline bool	   (*jcontainers_file_exists_at_path_func)(void*, RE::BSFixedString a_path);



		class JMap
		{
		public:
			static inline int allKeys(int32_t a_obj)
			{
				return jmap_all_keys_func ? jmap_all_keys_func(jc_default_domain, a_obj) : 0;
			}
			static inline int allValues(int32_t a_obj)
			{
				return jmap_all_values_func ? jmap_all_values_func(jc_default_domain, a_obj) : 0;
			}
			static inline int count(int32_t a_obj)
			{
				return jmap_count_func ? jmap_count_func(jc_default_domain, a_obj) : 0;
			}
			static inline float getFlt(int32_t a_obj, RE::BSFixedString a_key, float a_default = 0.f)
			{
				return jmap_get_flt_func ? jmap_get_flt_func(jc_default_domain, a_obj, a_key, a_default) : 0.f;
			}
			static inline RE::TESForm* getForm(int32_t a_obj, RE::BSFixedString a_key, RE::TESForm* a_default = nullptr)
			{
				return jmap_get_form_func ? jmap_get_form_func(jc_default_domain, a_obj, a_key, a_default = nullptr) : nullptr;
			}
			static inline int getInt(int32_t a_obj, RE::BSFixedString a_key, int32_t a_default = 0)
			{
				return jmap_get_int_func ? jmap_get_int_func(jc_default_domain, a_obj, a_key, a_default) : 0;
			}
			static inline int getObj(int32_t a_obj, RE::BSFixedString a_key, int a_default = 0)
			{
				return jmap_get_obj_func ? jmap_get_obj_func(jc_default_domain, a_obj, a_key, a_default) : 0;
			}
			static inline RE::BSFixedString getStr(int32_t a_obj, RE::BSFixedString a_key, RE::BSFixedString a_default = "")
			{
				return jmap_get_str_func ? jmap_get_str_func(jc_default_domain, a_obj, a_key, a_default) : "";
			}
			static inline bool hasKey(int32_t a_obj, RE::BSFixedString a_key)
			{
				return jmap_has_key_func ? jmap_has_key_func(jc_default_domain, a_obj, a_key) : false;
			}
			static inline int object()
			{
				return jmap_object_func ? jmap_object_func(jc_default_domain) : 0;
			}
			static inline RE::BSFixedString nextKey(int32_t a_obj, RE::BSFixedString a_previous_key = "", RE::BSFixedString a_end_key = "")
			{
				return jmap_next_key_func ? jmap_next_key_func(jc_default_domain, a_obj, a_previous_key, a_end_key) : a_end_key;
			}
			static inline bool removeKey(int32_t a_obj, RE::BSFixedString a_key)
			{
				return jmap_remove_key_func ? jmap_remove_key_func(jc_default_domain, a_obj, a_key) : false;
			}
			static inline void setFlt(int32_t a_obj, RE::BSFixedString a_key, float a_value)
			{
				if (jmap_set_flt_func) 
					jmap_set_flt_func(jc_default_domain, a_obj, a_key, a_value);
			}
			static inline void setInt(int32_t a_obj, RE::BSFixedString a_key, int32_t a_value)
			{
				if (jmap_set_int_func)
					jmap_set_int_func(jc_default_domain, a_obj, a_key, a_value);
			}
			static inline void setObj(int32_t a_obj, RE::BSFixedString a_key, int32_t a_value)
			{
				if (jmap_set_obj_func)
					jmap_set_obj_func(jc_default_domain, a_obj, a_key, a_value);
			}
			static inline void setStr(int32_t a_obj, RE::BSFixedString a_key, RE::BSFixedString a_value)
			{
				if (jmap_set_str_func)
					jmap_set_str_func(jc_default_domain, a_obj, a_key, a_value);
			}
			static inline int valueType(int32_t a_obj, RE::BSFixedString a_key)
			{
				return jmap_value_type_func ? jmap_value_type_func(jc_default_domain, a_obj, a_key) : 0;
			}
		};

		class JArray
		{
		public:
			static inline void addFromArray(int32_t a_arr, int32_t a_source, int32_t a_insert_index = -1)
			{
				if (jarray_add_from_array_func)
					jarray_add_from_array_func(jc_default_domain, a_arr, a_source, a_insert_index);
			}
			static inline void addObj(int32_t a_arr, int32_t a_obj, int32_t a_index = -1)
			{
				if (jarray_add_obj_func)
					jarray_add_obj_func(jc_default_domain, a_arr, a_obj, a_index);
			}
			static inline void addInt(int32_t a_arr, int32_t a_int, int32_t a_index = -1)
			{
				if (jarray_add_int_func)
					jarray_add_int_func(jc_default_domain, a_arr, a_int, a_index);
			}
			static inline void clear(int32_t a_obj)
			{
				if (jarray_clear_func)
					jarray_clear_func(jc_default_domain, a_obj);
			}
			static inline int count(int32_t a_obj)
			{
				return jarray_count_func ? jarray_count_func(jc_default_domain, a_obj) : 0;
			}
			static inline void eraseIndex(int32_t a_arr, int32_t a_index)
			{
				if (jarray_erase_index_func)
					jarray_erase_index_func(jc_default_domain, a_arr, a_index);
			}
			static inline int findInt(int32_t a_arr, int32_t a_value, int32_t a_search_start_index = 0)
			{
				return jarray_find_int_func ? jarray_find_int_func(jc_default_domain, a_arr, a_value, a_search_start_index) : 0;
			}
			static inline int findObj(int32_t a_arr, int32_t a_container, int32_t a_search_start_index = 0)
			{
				return jarray_find_obj_func ? jarray_find_obj_func(jc_default_domain, a_arr, a_container, a_search_start_index) : 0;
			}
			static inline int getInt(int32_t a_arr, int32_t a_index, int32_t a_default = 0)
			{
				return jarray_get_int_func ? jarray_get_int_func(jc_default_domain, a_arr, a_index, a_default) : 0;
			}
			static inline float getFlt(int32_t a_arr, int32_t a_index, float a_default = 0.f)
			{
				return jarray_get_flt_func ? jarray_get_flt_func(jc_default_domain, a_arr, a_index, a_default) : 0;
			}
			static inline int getObj(int32_t a_arr, int32_t a_index, int32_t a_default = 0)
			{
				return jarray_get_obj_func ? jarray_get_obj_func(jc_default_domain, a_arr, a_index, a_default) : 0;
			}
			static inline RE::BSFixedString getStr(int32_t a_arr, int32_t a_index, RE::BSFixedString a_default = "")
			{
				return jarray_get_str_func ? jarray_get_str_func(jc_default_domain, a_arr, a_index, a_default) : "";
			}
			static inline int object()
			{
				return jarray_object_func ? jarray_object_func(jc_default_domain) : 0;
			}
			static inline int valueType(int32_t a_obj, int32_t a_index)
			{
				return jarray_value_type_func ? jarray_value_type_func(jc_default_domain, a_obj, a_index) : 0;
			}
		};

		class JValue
		{
		public:
			static inline int addToPool(int32_t a_obj, RE::BSFixedString a_pool_name)
			{
				return jvalue_add_to_pool_func ? jvalue_add_to_pool_func(jc_default_domain, a_obj, a_pool_name) : 0;
			}
			static inline void cleanPool(RE::BSFixedString a_pool_name)
			{
				if (jvalue_clean_pool_func)
					jvalue_clean_pool_func(jc_default_domain, a_pool_name);
			}
			static inline int deepCopy(int32_t a_obj)
			{
				return jvalue_deep_copy_func ? jvalue_deep_copy_func(jc_default_domain, a_obj) : 0;
			}
			static inline bool isArray(int32_t a_obj)
			{
				return jvalue_is_array_func ? jvalue_is_array_func(jc_default_domain, a_obj) : false;
			}
			static inline bool isFormMap(int32_t a_obj)
			{
				return jvalue_is_form_map_func ? jvalue_is_form_map_func(jc_default_domain, a_obj) : false;
			}
			static inline bool isMap(int32_t a_obj)
			{
				return jvalue_is_map_func ? jvalue_is_map_func(jc_default_domain, a_obj) : false;
			}
			static inline int readFromDirectory(RE::BSFixedString a_directory_path, RE::BSFixedString a_extension = "")
			{
				return jvalue_read_from_directory_func ? jvalue_read_from_directory_func(jc_default_domain, a_directory_path, a_extension) : 0;
			}
			static inline int readFromFile(RE::BSFixedString a_file_path)
			{
				return jvalue_read_from_file_func ? jvalue_read_from_file_func(jc_default_domain, a_file_path) : 0;
			}
			static inline int release(int32_t a_obj)
			{
				return jvalue_release_func ? jvalue_release_func(jc_default_domain, a_obj) : 0;
			}
			static inline void releaseObjectsWithTag(RE::BSFixedString a_tag)
			{
				if (jvalue_release_objects_with_tag_func)
					jvalue_release_objects_with_tag_func(jc_default_domain, a_tag);
			}
			static inline int retain(int32_t a_obj, RE::BSFixedString a_tag = "")
			{
				return jvalue_retain_func ? jvalue_retain_func(jc_default_domain, a_obj, a_tag) : 0;
			}
			static inline int shallowCopy(int32_t a_obj)
			{
				return jvalue_shallow_copy_func ? jvalue_shallow_copy_func(jc_default_domain, a_obj) : 0;
			}
			static inline void writeToFile(int32_t a_obj, RE::BSFixedString a_file_path)
			{
				if(jvalue_write_to_file_func)
					jvalue_write_to_file_func(jc_default_domain, a_obj, a_file_path);
			}
		};
		
		class JDB
		{
		public:
			static inline int solveObj(RE::BSFixedString a_path, int32_t a_default = 0)
			{
				return jdb_solve_obj_func ? jdb_solve_obj_func(jc_default_domain, a_path, a_default) : 0;
			}
			static inline bool solveObjSetter(RE::BSFixedString a_path, int32_t a_obj, bool a_create_missing_keys = false)
			{
				return jdb_solve_obj_setter_func ? jdb_solve_obj_setter_func(jc_default_domain, a_path, a_obj, a_create_missing_keys) : 0;
			}
			static inline void setObj(RE::BSFixedString a_path, int32_t a_obj)
			{
				if (jdb_set_obj_func)
					jdb_set_obj_func(jc_default_domain, a_path, a_obj);
			}
			static inline int32_t root()
			{
				return jdb_root_func ? jdb_root_func(jc_default_domain) : 0;
			}
		};

		
		class JFormDB
		{
		public:
			static inline int getInt(RE::TESForm* a_fKey, RE::BSFixedString a_key)
			{
				return jformdb_get_int_func ? jformdb_get_int_func(jc_default_domain, a_fKey, a_key) : 0;
			}
			static inline int getObj(RE::TESForm* a_fKey, RE::BSFixedString a_key)
			{
				return jformdb_get_obj_func ? jformdb_get_obj_func(jc_default_domain, a_fKey, a_key) : 0;
			}
			static RE::BSFixedString getStr(RE::TESForm* a_fKey, RE::BSFixedString a_key)
			{
				return jformdb_get_str_func ? jformdb_get_str_func(jc_default_domain, a_fKey, a_key) : "";
			}
			static inline int32_t makeEntry(RE::BSFixedString a_storage_name, RE::TESForm* a_fKey)
			{
				return jformdb_make_entry_func ? jformdb_make_entry_func(jc_default_domain, a_storage_name, a_fKey) : 0;
			}
			static inline void setEntry(RE::BSFixedString a_storage_name, RE::TESForm* a_fKey, int32_t a_entry)
			{
				if (jformdb_set_entry_func)
					jformdb_set_entry_func(jc_default_domain, a_storage_name, a_fKey, a_entry);
			}
			static inline void setInt(RE::TESForm* a_fKey, RE::BSFixedString a_key, int32_t a_value)
			{
				if (jformdb_set_int_func)
					jformdb_set_int_func(jc_default_domain, a_fKey, a_key, a_value);
			}
			static inline void setObj(RE::TESForm* a_fKey, RE::BSFixedString a_key, int32_t a_container)
			{
				if (jformdb_set_obj_func)
					jformdb_set_obj_func(jc_default_domain, a_fKey, a_key, a_container);
			}
			static inline void setStr(RE::TESForm* a_fKey, RE::BSFixedString a_key, RE::BSFixedString a_value)
			{
				if (jformdb_set_str_func)
					jformdb_set_str_func(jc_default_domain, a_fKey, a_key, a_value);
			}

		};

		class JAtomic
		{
		public:
			static inline int32_t compareExchangeInt(int32_t a_obj, RE::BSFixedString a_path, int32_t a_desired, int32_t a_expected,
				bool a_create_missing_keys, int32_t a_result_on_error)
			{
				return jatomic_compare_exchange_int_func ? jatomic_compare_exchange_int_func(jc_default_domain, a_obj, a_path, a_desired, a_expected,
					a_create_missing_keys, a_result_on_error) : 0;
			}
			static inline int32_t fetchAddInt(int32_t a_obj, RE::BSFixedString a_path, int32_t a_value, int32_t a_initial_value,
				bool a_create_missing_keys, int32_t a_result_on_error)
			{
				return jatomic_fetch_add_int_func ? jatomic_fetch_add_int_func(jc_default_domain, a_obj, a_path, a_value, a_initial_value,
														a_create_missing_keys, a_result_on_error) : 0;
			}
		};

		class JContainers
		{
		public:
			static inline bool fileExistsAtPath(RE::BSFixedString a_path)
			{
				return jcontainers_file_exists_at_path_func ? jcontainers_file_exists_at_path_func(jc_default_domain, a_path) : false;
			}
		};
	}
}

