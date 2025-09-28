#include "skee-modders-resource-v0-4-19-16/SKEE_IPluginInterface.h"
#include "nioverride_impl.h"
#include "nioverride_wrapper.h"
#include "nioverride_impl_current.h"
#include "nioverride_impl_legacy.h"

namespace slavetats_ng
{
	namespace skee_wrapper
	{
		void NiOverride::Init()
		{
			logger::info("NiOverride::Init() entered");

			bool useLegacy = true;

			auto iMap = get_interface_map();
			if (iMap) {
				logger::info("SKEE interface map found");
				auto overrideInterface = get_override_interface(iMap);
				auto foundInterfaceVersion = overrideInterface->GetVersion();
				logger::info("NiOverride interface version is: {}", foundInterfaceVersion);
				auto minimumSupportedVersion = skee::IOverrideInterface::kCurrentPluginVersion;
				logger::info("Minimum supported NiOverride interface version is: {}", (uint32_t)minimumSupportedVersion);
				if (foundInterfaceVersion >= (uint32_t)minimumSupportedVersion) {
					logger::info("Found NiOverride interface version is supported, will use interface");
					useLegacy = false;
				} else {
					logger::info("Found NiOverride interface version is not supported, will use legacy address tables");
				}
			} else {
				logger::info("SKEE interface map not found");
			}

			if (useLegacy) {
				logger::info("Using legacy address tables");
				auto legacy = nioverride_impl::nioverride_legacy::RaceMenuAddressTables::GetSingleton();
				legacy->init();
				// _funcs = nioverride_impl::nioverride_impl_old::legacy_binding::singleton();
				_funcs = legacy;
			} else {
				logger::info("Using NiOverride interface");
				_funcs = nioverride_impl::nioverride_impl_current::current_binding::singleton();
			}

			CSimpleIniA skeeConfig;
			const char* skee_config_file = "Data/SKSE/Plugins/skee64.ini";
			if (REL::Module::IsVR())
				skee_config_file = "Data/SKSE/Plugins/skeevr.ini";
			SI_Error rc = skeeConfig.LoadFile(skee_config_file);
			logger::info("Load {}, result = {}", skee_config_file, rc);

			if (rc >= 0) {
				clib_util::ini::get_value(skeeConfig, _numBodyOvls, "Overlays/Body", "iNumOverlays", ";");
				clib_util::ini::get_value(skeeConfig, _numHandsOvls, "Overlays/Hands", "iNumOverlays", ";");
				clib_util::ini::get_value(skeeConfig, _numFeetOvls, "Overlays/Feet", "iNumOverlays", ";");
				clib_util::ini::get_value(skeeConfig, _numFaceOvls, "Overlays/Face", "iNumOverlays", ";");
			}

			logger::info("# Overlay: {} {} {} {}", _numBodyOvls, _numHandsOvls, _numFeetOvls, _numFaceOvls);
		}
	}
}
