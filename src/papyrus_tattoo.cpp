#include "tattoo.h"
#include "papyrus_tattoo.h"

namespace slavetats_ng
{

	namespace tattoo
	{
		namespace papyrus
		{
			namespace ng = slavetats_ng;

			fail_t external_slots(RE::StaticFunctionTag*, RE::Actor* a_target, RE::BSFixedString a_area, int a_matches)
			{
				fail_t result = false;
				// std::thread t1{
				//	[&] {
						result = ng::external_slots(a_target, a_area, a_matches);
						// logger::info("result is {}", result);
				//	}
				// };
				// t1.join();
				return result;
			}
			
			fail_t get_applied_tattoos_by_area(RE::StaticFunctionTag*, RE::Actor* a_target, int a_on_body, int a_on_face, int a_on_hands, int a_on_feet)
			{
				return ng::get_applied_tattoos_by_area(a_target, a_on_body, a_on_face, a_on_hands, a_on_feet);
			}
						
			int get_applied_tattoo_in_slot(RE::StaticFunctionTag*, RE::Actor* a_target, RE::BSFixedString a_area, int a_slot)
			{
				return ng::get_applied_tattoo_in_slot(a_target, a_area, a_slot);
			}
		
			int _available_slot(RE::StaticFunctionTag*, RE::Actor* a_target, RE::BSFixedString a_area)
			{
				return ng::_available_slot(a_target, a_area);
			}
			
			fail_t _remove_tattoos(RE::StaticFunctionTag*, RE::Actor* a_target, int a_template, bool a_ignore_lock = false, bool a_silent = false)
			{
				return ng::_remove_tattoos(a_target, a_template, a_ignore_lock, a_silent);
			}

			fail_t remove_tattoos(RE::StaticFunctionTag*, RE::Actor* a_target, int a_template, bool a_ignore_lock = false,
				bool a_silent = false)
			{
				return ng::remove_tattoos(a_target, a_template, a_ignore_lock, a_silent);
			}

			fail_t remove_tattoo_from_slot(RE::StaticFunctionTag*, RE::Actor* a_target, RE::BSFixedString a_area, int a_slot, bool a_ignore_lock = false,
				bool a_silent = false)
			{
				return ng::remove_tattoo_from_slot(a_target, a_area, a_slot, a_ignore_lock, a_silent);
			}

			fail_t query_applied_tattoos_with_attribute(RE::StaticFunctionTag*, RE::Actor* a_target, RE::BSFixedString a_attrib, int a_matches,
				RE::BSFixedString a_except_area = "", int a_except_slot = -1)
			{
				return ng::query_applied_tattoos_with_attribute(a_target, a_attrib, a_matches, a_except_area, a_except_slot);
			}

			bool has_applied_tattoos_with_attribute(RE::StaticFunctionTag*, RE::Actor* a_target, RE::BSFixedString a_attrib, RE::BSFixedString a_except_area = "",
				  int a_except_slot = -1)
			{
				return ng::has_applied_tattoos_with_attribute(a_target, a_attrib, a_except_area, a_except_slot);
			}

			int _add_and_get_tattoo(RE::StaticFunctionTag*, RE::Actor* a_target, int a_tattoo, int a_slot = -1, bool a_ignore_lock = false,
				   bool a_silent = false)
			{
				return ng::_add_and_get_tattoo(a_target, a_tattoo, a_slot, a_ignore_lock, a_silent);
			}

			int add_and_get_tattoo(RE::StaticFunctionTag*, RE::Actor* a_target, int a_tattoo, int a_slot = -1, bool a_ignore_lock = false,
				   bool a_silent = false, bool a_try_upgrade = true)
			{
				return ng::add_and_get_tattoo(a_target, a_tattoo, a_slot, a_ignore_lock, a_silent, a_try_upgrade);
			}

			fail_t add_tattoo(RE::StaticFunctionTag*, RE::Actor* a_target, int a_tattoo, int a_slot = -1, bool a_ignore_lock = false,
				bool a_silent = false)
			{
				return ng::add_tattoo(a_target, a_tattoo, a_slot, a_ignore_lock, a_silent = false);
			}


			void register_functions(const char* clazz, RE::BSScript::IVirtualMachine* vm)
			{
				vm->RegisterFunction("external_slots", clazz, external_slots);
				vm->RegisterFunction("get_applied_tattoos_by_area", clazz, get_applied_tattoos_by_area);
				vm->RegisterFunction("get_applied_tattoo_in_slot", clazz, get_applied_tattoo_in_slot);
				vm->RegisterFunction("_available_slot", clazz, _available_slot);
				vm->RegisterFunction("_remove_tattoos", clazz, _remove_tattoos);
				vm->RegisterFunction("remove_tattoos", clazz, remove_tattoos);
				vm->RegisterFunction("remove_tattoo_from_slot", clazz, remove_tattoo_from_slot);
				vm->RegisterFunction("query_applied_tattoos_with_attribute", clazz, query_applied_tattoos_with_attribute);
				vm->RegisterFunction("has_applied_tattoos_with_attribute", clazz, has_applied_tattoos_with_attribute);
				vm->RegisterFunction("_add_and_get_tattoo", clazz, _add_and_get_tattoo);
				vm->RegisterFunction("add_and_get_tattoo", clazz, add_and_get_tattoo);
				vm->RegisterFunction("add_tattoo", clazz, add_tattoo);

			}

		}

	}

}
