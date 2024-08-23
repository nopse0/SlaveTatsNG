#include "../include/constants.h"
#include "../include/papyrus_constants.h"

namespace slavetats_ng
{
	namespace constants
	{
		namespace papyrus
		{
			namespace ng = slavetats_ng;

			RE::BSFixedString VERSION(RE::StaticFunctionTag*)
			{
				return ng::VERSION();
			}

			RE::BSFixedString ROOT(RE::StaticFunctionTag*)
			{
				return ng::ROOT();
			}

			RE::BSFixedString PREFIX(RE::StaticFunctionTag*)
			{
				return ng::PREFIX();
			}

			int32_t SLOTS(RE::StaticFunctionTag*, RE::BSFixedString a_area)
			{
				return ng::SLOTS(a_area);
			}

			void register_functions(const char* clazz, RE::BSScript::IVirtualMachine* vm)
			{
				vm->RegisterFunction("VERSION", clazz, VERSION);
				vm->RegisterFunction("ROOT", clazz, ROOT);
				vm->RegisterFunction("PREFIX", clazz, PREFIX);
				vm->RegisterFunction("SLOTS", clazz, SLOTS);
			}

		}

	}

}
