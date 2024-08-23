#pragma once

namespace slavetats_ng
{
	bool tattoo_matches(int a_template, int a_tattoo, bool a_include_configurable = false);
	int  find_tattoo(int array, int a_template);
	int  find_excluding_tattoo(int a_applied, int a_tattoo);
	int  find_required_tattoo(int a_applied, int a_tattoo);
	RE::TESForm* get_form(int a_tattoo, RE::BSFixedString a_plugin_field, RE::BSFixedString a_formid_field, RE::TESForm* a_default = nullptr);
	bool has_required_plugin(int a_tattoo);
	void _extend_matching(int a_dest, int a_src, int a_template, int a_applied = 0, RE::BSFixedString a_domain = "default");
	fail_t is_tattoo(int tattoo);
}
