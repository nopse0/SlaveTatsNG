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
				fail_t      result = false;
				result = ng::simple_add_tattoo(a_target, a_section.c_str(), a_name.c_str(), a_color, a_last, a_silent, a_alpha);
				logger::info("result is {}", result);		
				return result;
			}

			fail_t complex_add_tattoo(RE::StaticFunctionTag*, RE::Actor* a_target, RE::BSFixedString a_section, RE::BSFixedString a_name, int a_color,
				bool a_last = true, bool a_silent = false, float a_alpha = 1.0f, int a_emissive_color = 0, bool a_gloss = false, RE::BSFixedString a_bump_map = "",
				RE::BSFixedString a_glow_map = "", float a_emissive_mult = 1.0f)
			{
				fail_t result = false;
				std::thread t1
				{
					[&] {
						result = ng::complex_add_tattoo(a_target, a_section.c_str(), a_name.c_str(), a_color, a_last, a_silent, a_alpha, a_emissive_color, a_gloss, a_bump_map,
							a_glow_map, a_emissive_mult);
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
						result = ng::simple_remove_tattoo(a_target, a_section.c_str(), a_name.c_str(), a_last, a_silent);
					}
				};
				t1.join();
				return result;
			}			

			void register_functions(const char* clazz, RE::BSScript::IVirtualMachine* vm)
			{
				vm->RegisterFunction("simple_add_tattoo", clazz, simple_add_tattoo);
				vm->RegisterFunction("complex_add_tattoo", clazz, complex_add_tattoo);
				vm->RegisterFunction("simple_remove_tattoo", clazz, simple_remove_tattoo);
			}

		}
	}
}
