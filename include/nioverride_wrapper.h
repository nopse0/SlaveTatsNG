#pragma once

#include "skee-modders-resource-v0-4-19-16/SKEE_IPluginInterface.h"

namespace slavetats_ng
{
	namespace skee_wrapper
	{

		class SetVariant : public skee::IOverrideInterface::SetVariant
		{
		public:
			SetVariant(const char* a_value)
			{
				_type = Type::String;
				_intValue = 0;
				_fltValue = 0;
				_strValue = a_value;
				_bValue = false;
				_tsValue = nullptr;
			}
			SetVariant(int a_value)
			{
				_type = Type::Int;
				_intValue = a_value;
				_fltValue = 0;
				_strValue = nullptr;
				_bValue = false;
				_tsValue = nullptr;
			}
			SetVariant(float a_value)
			{
				_type = Type::Float;
				_intValue = 0;
				_fltValue = a_value;
				_strValue = nullptr;
				_bValue = false;
				_tsValue = nullptr;
			}
			SetVariant(bool a_value)
			{
				_type = Type::Bool;
				_intValue = 0;
				_fltValue = 0;
				_strValue = nullptr;
				_bValue = a_value;
				_tsValue = nullptr;
			}
			SetVariant(RE::BGSTextureSet* a_value)
			{
				_type = Type::TextureSet;
				_intValue = 0;
				_fltValue = 0;
				_strValue = nullptr;
				_bValue = false;
				_tsValue = a_value;
			}

			inline Type               GetType() override { return _type; }
			inline int32_t            Int() override { return _intValue; }
			inline float              Float() override { return _fltValue; }
			inline const char*        String() override { return _strValue; }
			inline bool               Bool() override { return _bValue; }
			inline RE::BGSTextureSet* TextureSet() override { return _tsValue; }

		private:
			Type               _type;
			int32_t            _intValue;
			float              _fltValue;
			const char*        _strValue;
			bool               _bValue;
			RE::BGSTextureSet* _tsValue;
		};

		class GetVariant : public skee::IOverrideInterface::GetVariant
		{
		public:
			inline void Int(const int32_t i) { intValue = i; }
			inline void Float(const float f) { fltValue = f; }
			inline void String(const char* str) { strValue = str; }
			inline void Bool(const bool b) { bValue = b; }
			inline void TextureSet(const RE::BGSTextureSet*) {}

			int32_t     intValue;
			float       fltValue;
			const char* strValue;
			bool        bValue;
		};

		static const char* SKEE_CONFIG_PATH = "Data/SKSE/Plugins/skee64.ini";

		class NiOverride
		{
		private:
			static inline skee::IInterfaceMap* getInterfaceMap()
			{
				skee::InterfaceExchangeMessage msg;
				auto                           sender = skee::InterfaceExchangeMessage::kMessage_ExchangeInterface;
				auto                           intfc = SKSE::GetMessagingInterface();
				intfc->Dispatch(sender, (void*)&msg, sizeof(skee::InterfaceExchangeMessage*), "SKEE");
				return msg.interfaceMap ? msg.interfaceMap : nullptr;
			}

			static inline skee::IOverlayInterface* getOverlayInterface(skee::IInterfaceMap* a_map)
			{
				auto intfc = a_map->QueryInterface("Overlay");
				return static_cast<skee::IOverlayInterface*>(intfc);
			}

			static inline skee::IOverrideInterface* getOverrideInterface(skee::IInterfaceMap* a_map)
			{
				auto intfc = a_map->QueryInterface("Override");
				return static_cast<skee::IOverrideInterface*>(intfc);
			}

			static inline skee::IOverrideInterface* _overrideInterface = nullptr;
			static inline skee::IOverlayInterface*  _overlayInterface = nullptr;
			static inline int                       _numBodyOvls = 0;
			static inline int                       _numFaceOvls = 0;
			static inline int                       _numHandsOvls = 0;
			static inline int                       _numFeetOvls = 0;

		public:
			static inline int GetNumBodyOverlays()
			{
				return _numBodyOvls;
			}

			static inline int GetNumFaceOverlays()
			{
				return _numFaceOvls;
			}

			static inline int GetNumHandsOverlays()
			{
				return _numHandsOvls;
			}

			static inline int GetNumFeetOverlays()
			{
				return _numFeetOvls;
			}

			// ------------------------------ Override functions -----------------------------------------------------------------------

			static inline int GetNodeOverrideInt(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index)
			{
				//logger::info("Start");
				GetVariant var;
				if (_overrideInterface->GetNodeOverride(a_ref, a_female, a_node, (uint16_t)a_key, (uint8_t)a_index, var)) {
					//logger::info("Stop");
					return var.intValue;
				} else {
					//logger::info("Stop");
					return 0;
				}
			}

			static inline float GetNodeOverrideFloat(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index)
			{
				//logger::info("Start");
				GetVariant var;
				if (_overrideInterface->GetNodeOverride(a_ref, a_female, a_node, (uint16_t)a_key, (uint8_t)a_index, var)) {
					//logger::info("Stop");
					return var.fltValue;
				} else {
					//logger::info("Stop");
					return 0.f;
				}
			}

			static inline RE::BSFixedString GetNodeOverrideString(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index)
			{
				//logger::info("Start");
				GetVariant var;
				if (_overrideInterface->GetNodeOverride(a_ref, a_female, a_node, (uint16_t)a_key, (uint8_t)a_index, var)) {
					//logger::info("Stop");
					return var.strValue;
				} else {
					//logger::info("Stop");
					return "";
				}
			}

			static inline void AddNodeOverrideInt(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index, int a_value, bool)
			{
				//logger::info("Start");
				SetVariant var(a_value);
				_overrideInterface->AddNodeOverride(a_ref, a_female, a_node, (uint16_t)a_key, (uint8_t)a_index, var);
				//logger::info("Stop");
			}

			static inline void AddNodeOverrideFloat(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index, float a_value, bool)
			{
				//logger::info("Start");
				SetVariant var(a_value);
				_overrideInterface->AddNodeOverride(a_ref, a_female, a_node, (uint16_t)a_key, (uint8_t)a_index, var);
				//logger::info("Stop");
			}

			static inline void AddNodeOverrideString(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index, const char* a_value, bool)
			{
				//logger::info("Start");
				SetVariant var(a_value);
				_overrideInterface->AddNodeOverride(a_ref, a_female, a_node, (uint16_t)a_key, (uint8_t)a_index, var);
				//logger::info("Stop");
			}

			static inline bool HasNodeOverride(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index)
			{
				//logger::info("Start");
				auto ret = _overrideInterface->HasNodeOverride(a_ref, a_female, a_node, (uint16_t)a_key, (uint8_t)a_index);
				//logger::info("Stop");
				return ret;
			}

			static inline void RemoveNodeOverride(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index)
			{
				//logger::info("Start");
				_overrideInterface->RemoveNodeOverride(a_ref, a_female, a_node, (uint16_t)a_key, (uint8_t)a_index);
				//logger::info("Stop");
			}

			// ------------------ Overlay functions -------------------------------------------------------------------------------------------

			static inline void AddOverlays(RE::TESObjectREFR* a_ref)
			{
				//logger::info("Start");
				_overlayInterface->AddOverlays(a_ref);
				//logger::info("Stop");
			}

			static inline void ApplyNodeOverrides(RE::Actor* a_actor)
			{
				//logger::info("Start");
				_overrideInterface->SetNodeProperties(a_actor, false);
				//logger::info("Stop");
			}

			static inline bool HasOverlays(RE::TESObjectREFR* a_ref)
			{
				//logger::info("Start");
				auto ret = _overlayInterface->HasOverlays(a_ref);
				//logger::info("Stop");
				return ret;
			}

			static inline void RemoveOverlays(RE::TESObjectREFR* a_ref)
			{
				//logger::info("Start");
				_overlayInterface->RemoveOverlays(a_ref);
				//logger::info("Stop");
			}

			// ------------------ Initialization ---------------------------------------------------------------------

			static inline void Init()
			{
				auto iMap = getInterfaceMap();
				if (!iMap) {
					logger::error("skee interface map not found ");
				} else {
					auto overrideInterface = getOverrideInterface(iMap);
					auto overlayInterface = getOverlayInterface(iMap);
					if (overrideInterface->GetVersion() != skee::IOverrideInterface::kCurrentPluginVersion ||
						overlayInterface->GetVersion() != skee::IOverlayInterface::kCurrentPluginVersion) {
						logger::error("skee override or overlay interface too old");
					} else {
						_overrideInterface = overrideInterface;
						_overlayInterface = overlayInterface;
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
		};
	}
}
