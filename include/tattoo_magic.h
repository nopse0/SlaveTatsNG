#pragma once

namespace slavetats_ng
{
	fail_t activate_tattoo_magic(RE::Actor* a_target, int a_tattoo, bool a_deactivate_first = false);
	fail_t deactivate_tattoo_magic(RE::Actor* a_target, int a_tattoo);
	fail_t deactivate_all_tattoo_magic(RE::Actor* a_target);
}
