namespace slavetats_ng
{
	namespace skee_wrapper
	{

		namespace nioverride_impl
		{
			namespace nioverride_impl_old
			{
				class legacy_binding : public NiOverride_functions
				{
				public:
					virtual void AddNodeOverrideFloat(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index, float a_value, bool a_persist) override
					{
						_AddNodeOverrideFloat(&_staticfunctag, a_ref, a_female, a_node, a_key, a_index, a_value, a_persist);
					}
					virtual void AddNodeOverrideInt(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index, int a_value, bool a_persist) override
					{
						_AddNodeOverrideInt(&_staticfunctag, a_ref, a_female, a_node, a_key, a_index, a_value, a_persist);
					}

					virtual void AddNodeOverrideString(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index, const char* a_value, bool a_persist) override
					{
						_AddNodeOverrideString(&_staticfunctag, a_ref, a_female, a_node, a_key, a_index, a_value, a_persist);
					}

					virtual void AddOverlays(RE::TESObjectREFR* a_ref) override
					{
						_AddOverlays(&_staticfunctag, a_ref);
					}

					virtual void ApplyNodeOverrides(RE::Actor* a_actor) override
					{
						_ApplyNodeOverrides(&_staticfunctag, a_actor);
					}

					virtual float GetNodeOverrideFloat(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index) override
					{
						return _GetNodeOverrideFloat(&_staticfunctag, a_ref, a_female, a_node, a_key, a_index);
					}

					virtual int GetNodeOverrideInt(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index) override
					{
						return _GetNodeOverrideInt(&_staticfunctag, a_ref, a_female, a_node, a_key, a_index);
					}

					virtual RE::BSFixedString GetNodeOverrideString(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index) override
					{
						return _GetNodeOverrideString(&_staticfunctag, a_ref, a_female, a_node, a_key, a_index);
					}

					virtual bool HasNodeOverride(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index) override
					{
						return _HasNodeOverride(&_staticfunctag, a_ref, a_female, a_node, a_key, a_index);
					}

					virtual bool HasOverlays(RE::TESObjectREFR* a_ref) override
					{
						return _HasOverlays(&_staticfunctag, a_ref);
					}

					virtual void RemoveNodeOverride(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index) override
					{
						_RemoveNodeOverride(&_staticfunctag, a_ref, a_female, a_node, a_key, a_index);
					}

					virtual void RemoveOverlays(RE::TESObjectREFR* a_ref) override
					{
						_RemoveOverlays(&_staticfunctag, a_ref);
					}

					static inline NiOverride_functions* singleton()
					{
						static legacy_binding _instance;

						static std::atomic_bool _initialized;
						static std::latch       _latch(1);

						if (!_initialized.exchange(true)) {
							HMODULE skeeBaseAddr = GetModuleHandleA("skee64.dll");
							auto&   skeeOffsets = _offsets640;

							const auto skyrimVer = REL::Module::get().version();

							if (skyrimVer.major() == 1 && skyrimVer.minor() == 6 && skyrimVer.patch() == 640) {
								logger::info("Using NIOverride addresses for Skyrim 1.6.640");
							} else if (skyrimVer.major() == 1 && skyrimVer.minor() == 5 && skyrimVer.patch() == 97) {
								logger::info("Using NIOverride addresses for Skyrim 1.5.97");
								skeeOffsets = _offsets97;
							} else if (skyrimVer.major() == 1 && skyrimVer.minor() == 6 && skyrimVer.patch() == 659) {
								logger::info("Using NIOverride addresses for Skyrim 1.6.659");
								skeeOffsets = _offsets659;
							}

							auto addr = (char*)skeeBaseAddr + skeeOffsets[0];
							_instance._GetNodeOverrideInt = (_GetNodeOverrideInt_t)addr;
							addr = (char*)skeeBaseAddr + skeeOffsets[1];
							_instance._GetNodeOverrideFloat = (_GetNodeOverrideFloat_t)addr;
							addr = (char*)skeeBaseAddr + skeeOffsets[2];
							_instance._GetNodeOverrideString = (_GetNodeOverrideString_t)addr;
							addr = (char*)skeeBaseAddr + skeeOffsets[3];
							_instance._AddNodeOverrideInt = (_AddNodeOverrideInt_t)addr;
							addr = (char*)skeeBaseAddr + skeeOffsets[4];
							_instance._AddNodeOverrideFloat = (_AddNodeOverrideFloat_t)addr;
							addr = (char*)skeeBaseAddr + skeeOffsets[5];
							_instance._AddNodeOverrideString = (_AddNodeOverrideString_t)addr;
							addr = (char*)skeeBaseAddr + skeeOffsets[6];
							_instance._HasNodeOverride = (_HasNodeOverride_t)addr;
							addr = (char*)skeeBaseAddr + skeeOffsets[7];
							_instance._RemoveNodeOverride = (_RemoveNodeOverride_t)addr;
							addr = (char*)skeeBaseAddr + skeeOffsets[8];
							_instance._ApplyNodeOverrides = (_ApplyNodeOverrides_t)addr;
							addr = (char*)skeeBaseAddr + skeeOffsets[9];
							_instance._AddOverlays = (_AddOverlays_t)addr;
							addr = (char*)skeeBaseAddr + skeeOffsets[10];
							_instance._HasOverlays = (_HasOverlays_t)addr;
							addr = (char*)skeeBaseAddr + skeeOffsets[11];
							_instance._RemoveOverlays = (_RemoveOverlays_t)addr;

							_latch.count_down();
						}

						_latch.wait();

						return &_instance;
					}

					typedef void              (*_AddNodeOverrideFloat_t)(RE::StaticFunctionTag*, RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index, float a_value, bool);
					typedef void              (*_AddNodeOverrideInt_t)(RE::StaticFunctionTag*, RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index, int a_value, bool);
					typedef void              (*_AddNodeOverrideString_t)(RE::StaticFunctionTag*, RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index, const char* a_value, bool);
					typedef void              (*_AddOverlays_t)(RE::StaticFunctionTag*, RE::TESObjectREFR* a_ref);
					typedef void              (*_ApplyNodeOverrides_t)(RE::StaticFunctionTag*, RE::Actor* a_actor);
					typedef float             (*_GetNodeOverrideFloat_t)(RE::StaticFunctionTag*, RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index);
					typedef int               (*_GetNodeOverrideInt_t)(RE::StaticFunctionTag*, RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index);
					typedef RE::BSFixedString (*_GetNodeOverrideString_t)(RE::StaticFunctionTag*, RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index);
					typedef bool              (*_HasNodeOverride_t)(RE::StaticFunctionTag*, RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index);
					typedef bool              (*_HasOverlays_t)(RE::StaticFunctionTag*, RE::TESObjectREFR* a_ref);
					typedef void              (*_RemoveNodeOverride_t)(RE::StaticFunctionTag*, RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index);
					typedef void              (*_RemoveOverlays_t)(RE::StaticFunctionTag*, RE::TESObjectREFR* a_ref);

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

					static inline std::array<int, 12> _offsets97{
						0xBE160,
						0xBE090,
						0xBE2F0,
						0xBD9E0,
						0xBD780,
						0xBDC30,
						0x99D80,
						0x9A1D0,
						0x99D30,
						0x99760,
						0x99780,
						0x997A0
					};

					static inline std::array<int, 12> _offsets640{
						0xCA230,
						0xCA160,
						0xCA3C0,
						0xC9AD0,
						0xC9860,
						0xC9D20,
						0xA5940,
						0xA5CA0,
						0xA5930,
						0xA5350,
						0xA53D0,
						0xA53F0
					};

					static inline std::array<int, 12> _offsets659{
						0xCA390,
						0xCA2C0,
						0xCA520,
						0xC9C30,
						0xC99C0,
						0xC9E80,
						0xA5AA0,
						0xA5E00,
						0xA5A90,
						0xA54B0,
						0xA5530,
						0xA5550
					};

					RE::StaticFunctionTag _staticfunctag;
				};

			}
		}

	}

}
