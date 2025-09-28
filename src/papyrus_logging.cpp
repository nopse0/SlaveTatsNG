#include "logging.h"
#include "papyrus_logging.h"

namespace slavetats_ng
{

	namespace logging
	{
		namespace papyrus
		{
			namespace ng = slavetats_ng;

			void _log_jcontainer(RE::StaticFunctionTag*, int a_obj, RE::BSFixedString a_indent) 
			{
				ng::_log_jcontainer(a_obj, a_indent);
			}
			void log_tattoo(RE::StaticFunctionTag*, RE::BSFixedString a_msg, int a_tattoo)
			{
				ng::log_tattoo(a_msg, a_tattoo);
			}

			void register_functions(const char* clazz, RE::BSScript::IVirtualMachine* vm)
			{
				vm->RegisterFunction("_log_jcontainer", clazz, _log_jcontainer);
				vm->RegisterFunction("log_tattoo", clazz, log_tattoo);

			}

		}

	}

}
