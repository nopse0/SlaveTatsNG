#pragma once

namespace slavetats_ng
{
	fail_t query_applied_tattoos(RE::Actor* a_target, int a_template, int a_matches,
		RE::BSFixedString a_except_area = "", int a_except_slot = -1);
	fail_t query_available_tattoos(int a_template, int a_matches, int a_applied = 0, RE::BSFixedString a_domain = "default");
}
