#pragma once

namespace slavetats_ng
{
	fail_t simple_add_tattoo(RE::Actor* a_target, RE::BSFixedString a_section, RE::BSFixedString a_name, int a_color,
		bool a_last = true, bool a_silent = false, float a_alpha = 1.0f);

	fail_t simple_remove_tattoo(RE::Actor* a_target, RE::BSFixedString a_section, RE::BSFixedString a_name,
		bool a_last = true, bool a_silent = false);
}
