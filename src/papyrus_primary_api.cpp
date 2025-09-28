#include "primary_api.h"
#include "papyrus_primary_api.h"

namespace slavetats_ng
{

	namespace primary_api
	{
		namespace papyrus
		{
			namespace ng = slavetats_ng;

			fail_t query_applied_tattoos(RE::StaticFunctionTag*, RE::Actor* a_target, int a_template, int a_matches,
				RE::BSFixedString a_except_area = "", int a_except_slot = -1)
			{
				return ng::query_applied_tattoos(a_target, a_template, a_matches, a_except_area, a_except_slot);
			}
			
			fail_t query_available_tattoos(RE::StaticFunctionTag*, int a_template, int a_matches, int a_applied = 0, RE::BSFixedString a_domain = "default")
			{
				return ng::query_available_tattoos(a_template, a_matches, a_applied, a_domain);
			}

			void register_functions(const char* clazz, RE::BSScript::IVirtualMachine* vm)
			{
				vm->RegisterFunction("query_applied_tattoos", clazz, query_applied_tattoos);
				vm->RegisterFunction("query_available_tattoos", clazz, query_available_tattoos);
			}

		}

	}

}
