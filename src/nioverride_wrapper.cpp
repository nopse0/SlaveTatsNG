#include "skee-modders-resource-v0-4-19-16/SKEE_IPluginInterface.h"
#include "../include/nioverride_impl.h"
#include "../include/nioverride_wrapper.h"
#include "../include/nioverride_impl_old.h"
#include "../include/nioverride_impl_current.h"

namespace slavetats_ng
{
	namespace skee_wrapper
	{
		void NiOverride::Init()
		{
			auto iMap = get_interface_map();
			if (!iMap) {
				logger::error("skee interface map not found ");
			} else {
				auto overrideInterface = get_override_interface(iMap);
				auto foundInterfaceVersion = overrideInterface->GetVersion();
				logger::info("Found NiOverride interface with version: {}", foundInterfaceVersion);
				auto minimumSupportedVersion = skee::IOverrideInterface::kCurrentPluginVersion;
				logger::info("Supported minimum interface version is: {}", (uint32_t)minimumSupportedVersion);
				if (foundInterfaceVersion >= (uint32_t)minimumSupportedVersion) {
					logger::info("Found interface is supported, using interface");
					_funcs = nioverride_impl::nioverride_impl_current::current_binding::singleton();
				} else {
					logger::info("Found interface not supported, using legacy address tables");
					_funcs = nioverride_impl::nioverride_impl_old::legacy_binding::singleton();
				}
			}

			CSimpleIniA skeeConfig;
			SI_Error    rc = skeeConfig.LoadFile(SKEE_CONFIG_PATH);

			logger::info("Loaded {}", SKEE_CONFIG_PATH);

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
