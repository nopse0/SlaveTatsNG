#pragma once

namespace slavetats_ng
{
	namespace skee_wrapper
	{
		namespace nioverride_impl
		{
			class NiOverride_functions
			{
			public:
				virtual void              AddNodeOverrideFloat(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index, float a_value, bool) = 0;
				virtual void              AddNodeOverrideInt(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index, int a_value, bool) = 0;
				virtual void              AddNodeOverrideString(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index, const char* a_value, bool) = 0;
				virtual void              AddOverlays(RE::TESObjectREFR* a_ref) = 0;
				virtual void              ApplyNodeOverrides(RE::Actor* a_actor) = 0;
				virtual float             GetNodeOverrideFloat(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index) = 0;
				virtual int               GetNodeOverrideInt(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index) = 0;
				virtual RE::BSFixedString GetNodeOverrideString(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index) = 0;
				virtual bool              HasNodeOverride(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index) = 0;
				virtual bool              HasOverlays(RE::TESObjectREFR* a_ref) = 0;
				virtual void              RemoveNodeOverride(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index) = 0;
				virtual void              RemoveOverlays(RE::TESObjectREFR* a_ref) = 0;
			};
		}
	}
}
