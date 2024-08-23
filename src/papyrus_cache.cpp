#include "../include/cache.h"
#include "../include/papyrus_cache.h"

namespace slavetats_ng
{

	namespace cache
	{
		namespace papyrus
		{
			namespace ng = slavetats_ng;

			void _append(RE::StaticFunctionTag*, int32_t a_dest, int32_t a_val)
			{
				ng::_append(a_dest, a_val);
			}
			void _cache_tattoo(RE::StaticFunctionTag*, int32_t a_cache, int32_t a_tattoo)
			{
				ng::_cache_tattoo(a_cache, a_tattoo);
			}
			int compile_cache(RE::StaticFunctionTag*)
			{
				return ng::compile_cache();
			}
			int acquire_cache(RE::StaticFunctionTag*)
			{
				return ng::acquire_cache();
			}

			void register_functions(const char* clazz, RE::BSScript::IVirtualMachine* vm)
			{
				vm->RegisterFunction("_append", clazz, _append);
				vm->RegisterFunction("_cache_tattoo", clazz, _cache_tattoo);
				vm->RegisterFunction("compile_cache", clazz, compile_cache);
				vm->RegisterFunction("acquire_cache", clazz, acquire_cache);
			}

		}

	}

}
