#pragma once

namespace slavetats_ng
{
	fail_t clear_overlay(RE::Actor* a_target, bool a_is_female, RE::BSFixedString a_area, int a_slot);
	fail_t apply_overlay(RE::Actor* a_target, bool a_is_female, RE::BSFixedString a_area, int a_slot, RE::BSFixedString a_diffuse_map, int a_diffuse_color,
		int a_emissive_color, bool a_gloss, RE::BSFixedString a_bump_map = "", float a_alpha = 1.0f);
	fail_t complex_apply_overlay(RE::Actor* a_target, bool a_is_female, RE::BSFixedString a_area, int a_slot, RE::BSFixedString a_diffuse_map, int a_diffuse_color,
		int a_emissive_color, bool a_gloss, RE::BSFixedString a_bump_map = "", float a_alpha = 1.0f, RE::BSFixedString a_glow_map = "", float a_emissive_mult = 1.0f);
	fail_t upgrade_tattoos(RE::Actor* a_target);
	fail_t synchronize_tattoos(RE::Actor* a_target, bool a_silent = false);
}
