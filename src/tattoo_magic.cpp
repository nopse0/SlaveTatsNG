#include "../include/jcontainers_wrapper.h"
#include "../include/tattoo_magic.h"

using namespace slavetats_ng::jcwrapper;


namespace slavetats_ng
{
	fail_t activate_tattoo_magic(RE::Actor* a_target, int a_tattoo, bool a_deactivate_first)
	{
		bool magic = false;

		RE::BSFixedString tattoo_event = JMap::getStr(a_tattoo, "event");
		if (tattoo_event != "") {
			magic = true;
			int evt;

			if (a_deactivate_first) {

			}
		}






		return false;
	}

	fail_t deactivate_tattoo_magic(RE::Actor* a_target, int a_tattoo)
	{
		// TODO
		return false;
	}

	fail_t deactivate_all_tattoo_magic(RE::Actor* a_target)
	{
		// TODO
		return false;
	}

}
