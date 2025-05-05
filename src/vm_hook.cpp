#include "vm_hook.h"
#include "VMTHook.h"

namespace slavetats_ng
{

	namespace vm_hook
	{
	
		void vm_hook::install(RE::BSScript::IVirtualMachine* a_vm)
		{
			logger::info("[vm_hook] installing hook");
			bind_native_function = (bind_native_function_t)HookMethod((LPVOID)a_vm, (PVOID)bind_native_function_hook, 24 * sizeof(void*));
		}

		bool vm_hook::bind_native_function_hook([[maybe_unused]] RE::BSScript::IVirtualMachine* self, RE::BSScript::IFunction* a_fn)
		{
			bool result;
			//std::thread t1{
			//	[&] {
					auto addr = (char*)&(*a_fn) + 0x50;
					const auto callback = *reinterpret_cast<std::uintptr_t*>(addr);
					logger::info("[vm_hook] object: {}, name: {}, callback: {}", a_fn->GetObjectTypeName(), a_fn->GetName(), callback);
					result = bind_native_function(self, a_fn);
			//	}
			//};
			//t1.join();
			return result;
		}

		vm_hook::bind_native_function_t vm_hook::bind_native_function = nullptr;
		

	}
}
