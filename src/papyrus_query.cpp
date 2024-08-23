#include "../include/query.h"
#include "../include/papyrus_query.h"

namespace slavetats_ng
{

	namespace query
	{
		namespace papyrus
		{
			namespace ng = slavetats_ng;

			bool tattoo_matches(RE::StaticFunctionTag*, int a_template, int a_tattoo, bool a_include_configurable)
			{
				return ng::tattoo_matches(a_template, a_tattoo, a_include_configurable);
			}

			int find_tattoo(RE::StaticFunctionTag*, int array, int a_template)
			{
				return ng::find_tattoo(array, a_template);
			}
			
			int find_excluding_tattoo(RE::StaticFunctionTag*, int a_applied, int a_tattoo)
			{
				return ng::find_excluding_tattoo(a_applied, a_tattoo);
			}

			int find_required_tattoo(RE::StaticFunctionTag*, int a_applied, int a_tattoo)
			{
				return ng::find_required_tattoo(a_applied, a_tattoo);
			}

			RE::TESForm* get_form(RE::StaticFunctionTag*, int a_tattoo, RE::BSFixedString a_plugin_field, RE::BSFixedString a_formid_field, RE::TESForm* a_default = nullptr)
			{
				return ng::get_form(a_tattoo, a_plugin_field, a_formid_field, a_default);
			}

			bool has_required_plugin(RE::StaticFunctionTag*, int a_tattoo)
			{
				return ng::has_required_plugin(a_tattoo);
			}
			
			void _extend_matching(RE::StaticFunctionTag*, int a_dest, int a_src, int a_template, int a_applied = 0, RE::BSFixedString a_domain = "default")
			{
				ng::_extend_matching(a_dest, a_src, a_template, a_applied, a_domain);
			}

			fail_t is_tattoo(RE::StaticFunctionTag*, int tattoo)
			{
				return ng::is_tattoo(tattoo);
			}


			void register_functions(const char* clazz, RE::BSScript::IVirtualMachine* vm)
			{
				vm->RegisterFunction("tattoo_matches", clazz, tattoo_matches);
				vm->RegisterFunction("find_tattoo", clazz, find_tattoo);
				vm->RegisterFunction("find_excluding_tattoo", clazz, find_excluding_tattoo);
				vm->RegisterFunction("find_required_tattoo", clazz, find_required_tattoo);
				vm->RegisterFunction("get_form", clazz, get_form);
				vm->RegisterFunction("has_required_plugin", clazz, has_required_plugin);
				vm->RegisterFunction("_extend_matching", clazz, _extend_matching);
				vm->RegisterFunction("is_tattoo", clazz, is_tattoo);
			}

		}

	}

}
