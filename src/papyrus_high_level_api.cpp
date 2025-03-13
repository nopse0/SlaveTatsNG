#include "../include/high_level_api.h"
#include "../include/papyrus_high_level_api.h"

namespace slavetats_ng
{
	namespace high_level_api
	{
		namespace papyrus
		{
			namespace ng = slavetats_ng;

			fail_t simple_add_tattoo(RE::StaticFunctionTag*, RE::Actor* a_target, RE::BSFixedString a_section, RE::BSFixedString a_name, int a_color,
				bool a_last = true, bool a_silent = false, float a_alpha = 1.0f)
			{
				fail_t result = false;
				std::thread t1
				{
					[&] {
						result = ng::simple_add_tattoo(a_target, a_section, a_name, a_color, a_last, a_silent, a_alpha);
						logger::info("result is {}", result);
					}
				};
				t1.join();
				return result;
			}

			fail_t simple_remove_tattoo(RE::StaticFunctionTag*, RE::Actor* a_target, RE::BSFixedString a_section, RE::BSFixedString a_name, bool a_last,
				bool a_silent)
			{
				fail_t result = false;
				std::thread t1{
					[&] {
						result = ng::simple_remove_tattoo(a_target, a_section, a_name, a_last, a_silent);
					}
				};
				t1.join();
				return result;
			}			

			void register_functions(const char* clazz, RE::BSScript::IVirtualMachine* vm)
			{
				vm->RegisterFunction("simple_add_tattoo", clazz, simple_add_tattoo);
				vm->RegisterFunction("simple_remove_tattoo", clazz, simple_remove_tattoo);
			}

		}
	}
}
