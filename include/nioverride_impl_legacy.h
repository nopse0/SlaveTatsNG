#pragma once

namespace slavetats_ng
{
	namespace skee_wrapper
	{
		namespace nioverride_impl
		{
			namespace nioverride_legacy
			{
				using slavetats_ng::skee_wrapper::nioverride_impl::NiOverride_functions;

				typedef void (*_AddNodeOverrideFloat_t)(RE::StaticFunctionTag*, RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index, float a_value, bool);
				typedef void (*_AddNodeOverrideInt_t)(RE::StaticFunctionTag*, RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index, int a_value, bool);
				typedef void (*_AddNodeOverrideString_t)(RE::StaticFunctionTag*, RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index, const char* a_value, bool);
				typedef void (*_AddOverlays_t)(RE::StaticFunctionTag*, RE::TESObjectREFR* a_ref);
				typedef void (*_ApplyNodeOverrides_t)(RE::StaticFunctionTag*, RE::Actor* a_actor);
				typedef float (*_GetNodeOverrideFloat_t)(RE::StaticFunctionTag*, RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index);
				typedef int (*_GetNodeOverrideInt_t)(RE::StaticFunctionTag*, RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index);
				typedef RE::BSFixedString (*_GetNodeOverrideString_t)(RE::StaticFunctionTag*, RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index);
				typedef bool (*_HasNodeOverride_t)(RE::StaticFunctionTag*, RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index);
				typedef bool (*_HasOverlays_t)(RE::StaticFunctionTag*, RE::TESObjectREFR* a_ref);
				typedef void (*_RemoveNodeOverride_t)(RE::StaticFunctionTag*, RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index);
				typedef void (*_RemoveOverlays_t)(RE::StaticFunctionTag*, RE::TESObjectREFR* a_ref);

				class RaceMenuAddressTables : public clib_util::singleton::ISingleton<RaceMenuAddressTables>, public NiOverride_functions
				{
				public:
					RaceMenuAddressTables();
					void init();

				private:
					RE::StaticFunctionTag    _static_function_tag;
					_AddNodeOverrideFloat_t  _AddNodeOverrideFloat = nullptr;
					_AddNodeOverrideInt_t    _AddNodeOverrideInt = nullptr;
					_AddNodeOverrideString_t _AddNodeOverrideString = nullptr;
					_AddOverlays_t           _AddOverlays = nullptr;
					_ApplyNodeOverrides_t    _ApplyNodeOverrides = nullptr;
					_GetNodeOverrideFloat_t  _GetNodeOverrideFloat = nullptr;
					_GetNodeOverrideInt_t    _GetNodeOverrideInt = nullptr;
					_GetNodeOverrideString_t _GetNodeOverrideString = nullptr;
					_HasNodeOverride_t       _HasNodeOverride = nullptr;
					_HasOverlays_t           _HasOverlays = nullptr;
					_RemoveNodeOverride_t    _RemoveNodeOverride = nullptr;
					_RemoveOverlays_t        _RemoveOverlays = nullptr;

				public:
					virtual void AddNodeOverrideFloat(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index, float a_value, bool a_persist) override
					{
						_AddNodeOverrideFloat(&_static_function_tag, a_ref, a_female, a_node, a_key, a_index, a_value, a_persist);
					}
					virtual void AddNodeOverrideInt(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index, int a_value, bool a_persist) override
					{
						_AddNodeOverrideInt(&_static_function_tag, a_ref, a_female, a_node, a_key, a_index, a_value, a_persist);
					}

					virtual void AddNodeOverrideString(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index, const char* a_value, bool a_persist) override
					{
						_AddNodeOverrideString(&_static_function_tag, a_ref, a_female, a_node, a_key, a_index, a_value, a_persist);
					}

					virtual void AddOverlays(RE::TESObjectREFR* a_ref) override
					{
						_AddOverlays(&_static_function_tag, a_ref);
					}

					virtual void ApplyNodeOverrides(RE::Actor* a_actor) override
					{
						_ApplyNodeOverrides(&_static_function_tag, a_actor);
					}

					virtual float GetNodeOverrideFloat(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index) override
					{
						return _GetNodeOverrideFloat(&_static_function_tag, a_ref, a_female, a_node, a_key, a_index);
					}

					virtual int GetNodeOverrideInt(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index) override
					{
						return _GetNodeOverrideInt(&_static_function_tag, a_ref, a_female, a_node, a_key, a_index);
					}

					virtual RE::BSFixedString GetNodeOverrideString(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index) override
					{
						return _GetNodeOverrideString(&_static_function_tag, a_ref, a_female, a_node, a_key, a_index);
					}

					virtual bool HasNodeOverride(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index) override
					{
						return _HasNodeOverride(&_static_function_tag, a_ref, a_female, a_node, a_key, a_index);
					}

					virtual bool HasOverlays(RE::TESObjectREFR* a_ref) override
					{
						return _HasOverlays(&_static_function_tag, a_ref);
					}

					virtual void RemoveNodeOverride(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index) override
					{
						_RemoveNodeOverride(&_static_function_tag, a_ref, a_female, a_node, a_key, a_index);
					}

					virtual void RemoveOverlays(RE::TESObjectREFR* a_ref) override
					{
						_RemoveOverlays(&_static_function_tag, a_ref);
					}
				};

			}

		}
	}
}
