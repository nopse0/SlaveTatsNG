#pragma once

#include "skee-modders-resource-v0-4-19-16/SKEE_IPluginInterface.h"



#include "../include/nioverride_impl.h"
namespace slavetats_ng
{
	namespace skee_wrapper
	{
		static inline skee::IInterfaceMap* get_interface_map()
		{
			skee::InterfaceExchangeMessage msg;
			auto                           sender = skee::InterfaceExchangeMessage::kMessage_ExchangeInterface;
			auto                           intfc = SKSE::GetMessagingInterface();
			intfc->Dispatch(sender, (void*)&msg, sizeof(skee::InterfaceExchangeMessage*), "SKEE");
			return msg.interfaceMap ? msg.interfaceMap : nullptr;
		}

		static inline skee::IOverlayInterface* get_overlay_interface(skee::IInterfaceMap* a_map)
		{
			auto intfc = a_map->QueryInterface("Overlay");
			return static_cast<skee::IOverlayInterface*>(intfc);
		}

		static inline skee::IOverrideInterface* get_override_interface(skee::IInterfaceMap* a_map)
		{
			auto intfc = a_map->QueryInterface("Override");
			return static_cast<skee::IOverrideInterface*>(intfc);
		}






		class NiOverride
		{
		private:


			static inline nioverride_impl::NiOverride_functions* _funcs = nullptr;
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
				return _funcs->GetNodeOverrideInt(a_ref, a_female, a_node, a_key, a_index);
			}

			static inline float GetNodeOverrideFloat(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index)
			{
				return _funcs->GetNodeOverrideFloat(a_ref, a_female, a_node, a_key, a_index);
			}

			static inline RE::BSFixedString GetNodeOverrideString(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index)
			{
				return _funcs->GetNodeOverrideString(a_ref, a_female, a_node, a_key, a_index);
			}

			static inline void AddNodeOverrideInt(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index, int a_value, bool a_persist)
			{
				_funcs->AddNodeOverrideInt(a_ref, a_female, a_node, a_key, a_index, a_value, a_persist);
			}

			static inline void AddNodeOverrideFloat(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index, float a_value, bool a_persist)
			{
				_funcs->AddNodeOverrideFloat(a_ref, a_female, a_node, a_key, a_index, a_value, a_persist);
			}

			static inline void AddNodeOverrideString(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index, const char* a_value, bool a_persist)
			{
				_funcs->AddNodeOverrideString(a_ref, a_female, a_node, a_key, a_index, a_value, a_persist);
			}

			static inline bool HasNodeOverride(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index)
			{
				return _funcs->HasNodeOverride(a_ref, a_female, a_node, a_key, a_index);
			}

			static inline void RemoveNodeOverride(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index)
			{
				_funcs->RemoveNodeOverride(a_ref, a_female, a_node, a_key, a_index);
			}

			// ------------------ Overlay functions -------------------------------------------------------------------------------------------

			static inline void AddOverlays(RE::TESObjectREFR* a_ref)
			{
				_funcs->AddOverlays(a_ref);
			}

			static inline void ApplyNodeOverrides(RE::Actor* a_actor)
			{
				_funcs->ApplyNodeOverrides(a_actor);
			}

			static inline bool HasOverlays(RE::TESObjectREFR* a_ref)
			{
				return _funcs->HasOverlays(a_ref);
			}

			static inline void RemoveOverlays(RE::TESObjectREFR* a_ref)
			{
				return _funcs->RemoveOverlays(a_ref);
			}

			// ------------------ Initialization ---------------------------------------------------------------------

			static void Init();
			
		};
	}
}
