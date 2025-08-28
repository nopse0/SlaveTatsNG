#pragma once

namespace slavetats_ng
{
	fail_t clear_overlay(RE::Actor* a_target, bool a_is_female, RE::BSFixedString a_area, int a_slot);
	fail_t apply_overlay(RE::Actor* a_target, bool a_is_female, RE::BSFixedString a_area, int a_slot, RE::BSFixedString a_path, int a_color,
		int a_glow, bool a_gloss, RE::BSFixedString a_bump, float a_alpha);
	fail_t apply_overlay_ex(RE::Actor* a_target, bool a_is_female, RE::BSFixedString a_area, int a_slot, RE::BSFixedString a_diffuse_map, int a_diffuse_color,
		int a_emissive_color, float a_glossiness, RE::BSFixedString a_bump_map, float a_alpha, float a_specular_strength, RE::BSFixedString a_glow_map, float a_emissive_mult);
	fail_t upgrade_tattoos(RE::Actor* a_target);
	fail_t synchronize_tattoos(RE::Actor* a_target, bool a_silent = false);
}
