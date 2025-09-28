#include "papyrus_tattoo_magic.h"
#include "tattoo_magic.h"

namespace slavetats_ng
{

	namespace tattoo_magic
	{
		namespace papyrus
		{
			namespace ng = slavetats_ng;

			fail_t activate_tattoo_magic(RE::StaticFunctionTag*, RE::Actor* a_target, int a_tattoo, bool a_deactivate_first = false)
			{
				return ng::activate_tattoo_magic(a_target, a_tattoo, a_deactivate_first);
			}

			fail_t deactivate_tattoo_magic(RE::StaticFunctionTag*, RE::Actor* a_target, int a_tattoo)
			{
				return ng::deactivate_tattoo_magic(a_target, a_tattoo);
			}

			fail_t deactivate_all_tattoo_magic(RE::StaticFunctionTag*, RE::Actor* a_target)
			{
				return ng::deactivate_all_tattoo_magic(a_target);
			}


			void register_functions(const char* clazz, RE::BSScript::IVirtualMachine* vm)
			{
				vm->RegisterFunction("activate_tattoo_magic", clazz, activate_tattoo_magic);
				vm->RegisterFunction("deactivate_tattoo_magic", clazz, deactivate_tattoo_magic);
				vm->RegisterFunction("deactivate_all_tattoo_magic", clazz, deactivate_all_tattoo_magic);
			}

		}

	}

}
