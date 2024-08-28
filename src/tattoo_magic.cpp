#include "../include/jcontainers_wrapper.h"
#include "../include/tattoo_magic.h"

using namespace slavetats_ng::jcwrapper;


namespace slavetats_ng
{
	fail_t activate_tattoo_magic([[maybe_unused]] RE::Actor* a_target, [[maybe_unused]] int a_tattoo, [[maybe_unused]] bool a_deactivate_first)
	{
		// Not supported
		return false;
	}

	fail_t deactivate_tattoo_magic([[maybe_unused]] RE::Actor* a_target, [[maybe_unused]] int a_tattoo)
	{
		// Not supported
		return false;
	}

	fail_t deactivate_all_tattoo_magic([[maybe_unused]] RE::Actor* a_target)
	{
		// Not supported
		return false;
	}

}
