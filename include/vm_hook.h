#pragma once

namespace slavetats_ng
{

	namespace vm_hook
	{
		class vm_hook
		{
		public:
			static void install(RE::BSScript::IVirtualMachine* a_vm);

			static bool bind_native_function_hook(RE::BSScript::IVirtualMachine* self, RE::BSScript::IFunction* a_fn);
		
			typedef bool(__thiscall* bind_native_function_t)(RE::BSScript::IVirtualMachine*, RE::BSScript::IFunction*);
			static bind_native_function_t bind_native_function;
		};



	}


}
