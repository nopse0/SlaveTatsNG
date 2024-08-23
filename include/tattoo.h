#pragma once

namespace slavetats_ng
{
	fail_t external_slots(RE::Actor* a_target, RE::BSFixedString a_area, int a_matches);
	fail_t get_applied_tattoos_by_area(RE::Actor* a_target, int a_on_body, int a_on_face, int a_on_hands, int a_on_feet);
	int get_applied_tattoo_in_slot(RE::Actor* a_target, RE::BSFixedString a_area, int a_slot);
	int _available_slot(RE::Actor* a_target, RE::BSFixedString a_area);
	fail_t _remove_tattoos(RE::Actor* a_target, int a_template, bool a_ignore_lock = false, bool a_silent = false);
	fail_t remove_tattoos(RE::Actor* a_target, int a_template, bool a_ignore_lock = false,
		bool a_silent = false);
	fail_t remove_tattoo_from_slot(RE::Actor* a_target, RE::BSFixedString a_area, int a_slot, bool a_ignore_lock = false,
		bool a_silent = false);
	fail_t query_applied_tattoos_with_attribute(RE::Actor* a_target, RE::BSFixedString a_attrib, int a_matches,
		RE::BSFixedString a_except_area = "", int a_except_slot = -1);
	bool has_applied_tattoos_with_attribute(RE::Actor* a_target, RE::BSFixedString a_attrib, RE::BSFixedString a_except_area = "",
		int a_except_slot = -1);
	int _add_and_get_tattoo(RE::Actor* a_target, int a_tattoo, int a_slot = -1, bool a_ignore_lock = false,
		bool a_silent = false);
	int add_and_get_tattoo(RE::Actor* a_target, int a_tattoo, int a_slot = -1, bool a_ignore_lock = false,
		bool a_silent = false, bool a_try_upgrade = true);
	fail_t add_tattoo(RE::Actor* a_target, int a_tattoo, int a_slot = -1, bool a_ignore_lock = false,
		bool a_silent = false);
}
