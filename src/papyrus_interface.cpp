#include "papyrus_interface.h"
#include "papyrus_constants.h"
#include "papyrus_cache.h"
#include "papyrus_high_level_api.h"
#include "papyrus_logging.h"
#include "papyrus_overlays.h"
#include "papyrus_primary_api.h"
#include "papyrus_query.h"
#include "papyrus_tattoo.h"
#include "papyrus_tattoo_magic.h"
#include "vm_hook.h"
#include "utility.h"

namespace slavetats_ng
{
	namespace papyrus
	{

		float test_float_result(RE::StaticFunctionTag*)
		{
			return 42.f;
		}

		int test_int_result(RE::StaticFunctionTag*)
		{
			return 27;
		}

		bool test_bool_result(RE::StaticFunctionTag*)
		{
			return true;
		}

		RE::BSFixedString test_string_result(RE::StaticFunctionTag*)
		{
			return "Norbert";
		}

		std::vector<std::int32_t> get_last_save_time(RE::StaticFunctionTag*)
		{
			auto system = slavetats_ng::utility::System::GetSingleton();
			return system->get_time_since_last_save();
		}


		bool register_functions(RE::BSScript::IVirtualMachine* vm, bool install_vm_hook)
		{
			if (install_vm_hook)
				slavetats_ng::vm_hook::vm_hook::install(vm);
			constants::papyrus::register_functions(papyrus_class_name, vm);
			cache::papyrus::register_functions(papyrus_class_name, vm);
			high_level_api::papyrus::register_functions(papyrus_class_name, vm);
			logging::papyrus::register_functions(papyrus_class_name, vm);
			overlays::papyrus::register_functions(papyrus_class_name, vm);
			primary_api::papyrus::register_functions(papyrus_class_name, vm);
			query::papyrus::register_functions(papyrus_class_name, vm);
			tattoo::papyrus::register_functions(papyrus_class_name, vm);
			tattoo_magic::papyrus::register_functions(papyrus_class_name, vm);
			vm->RegisterFunction("get_last_save_time", papyrus_class_name, get_last_save_time);
			vm->RegisterFunction("test_float_result", papyrus_class_name, test_float_result);
			vm->RegisterFunction("test_int_result", papyrus_class_name, test_int_result);
			vm->RegisterFunction("test_bool_result", papyrus_class_name, test_bool_result);
			vm->RegisterFunction("test_string_result", papyrus_class_name, test_string_result);
			return true;
		}
	}
}


