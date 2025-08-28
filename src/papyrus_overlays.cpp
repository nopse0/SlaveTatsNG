#include "../include/overlays.h"
#include "../include/papyrus_overlays.h"
#include <future>

namespace slavetats_ng
{

	namespace overlays
	{
		namespace papyrus
		{
			namespace ng = slavetats_ng;

			fail_t clear_overlay(RE::StaticFunctionTag*, RE::Actor* a_target, bool a_is_female, RE::BSFixedString a_area, int a_slot)
			{
				return ng::clear_overlay(a_target, a_is_female, a_area, a_slot);
			}

			fail_t apply_overlay(RE::StaticFunctionTag*, RE::Actor* a_target, bool a_is_female, RE::BSFixedString a_area, int a_slot, RE::BSFixedString a_path, int a_color,
				int a_glow, bool a_gloss, RE::BSFixedString a_bump = "", float a_alpha = 1.0f)
			{
				return ng::apply_overlay(a_target, a_is_female, a_area, a_slot, a_path, a_color, a_glow, a_gloss, a_bump, a_alpha);
			}

			fail_t apply_overlay_ex(RE::Actor* a_target, bool a_is_female, RE::BSFixedString a_area, int a_slot, RE::BSFixedString a_diffuse_map, int a_diffuse_color,
				int a_emissive_color, float a_glossiness, RE::BSFixedString a_bump_map, float a_alpha, float a_specular_strength, RE::BSFixedString a_glow_map, float a_emissive_mult)
			{
				return ng::apply_overlay_ex(a_target, a_is_female, a_area, a_slot, a_diffuse_map, a_diffuse_color, a_emissive_color, a_glossiness, a_bump_map, a_alpha, a_specular_strength,
					a_glow_map, a_emissive_mult);
			}

			fail_t upgrade_tattoos(RE::StaticFunctionTag*, RE::Actor* a_target)
			{
				return ng::upgrade_tattoos(a_target);
			}

			fail_t synchronize_tattoos(RE::StaticFunctionTag*, RE::Actor* a_target, bool a_silent = false)
			{
				fail_t      result = false;
				// std::thread t1{
				//	[&] {
						logger::info("in papyrus synchronize_tattoos, a_target = {}", (void*)a_target);
						result = ng::synchronize_tattoos(a_target, a_silent);
						logger::info("result is {}", result);
				//	}
				//};
				//t1.join();
				return result;
			}

			void register_functions(const char* clazz, RE::BSScript::IVirtualMachine* vm)
			{
				vm->RegisterFunction("clear_overlay", clazz, clear_overlay);
				vm->RegisterFunction("apply_overlay", clazz, apply_overlay);
				vm->RegisterFunction("apply_overlay_ex", clazz, apply_overlay_ex);
				vm->RegisterFunction("upgrade_tattoos", clazz, upgrade_tattoos);
				vm->RegisterFunction("synchronize_tattoos", clazz, synchronize_tattoos);
			}

		}

	}

}
