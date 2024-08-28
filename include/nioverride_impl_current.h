#pragma once

namespace slavetats_ng
{

	namespace skee_wrapper
	{

		namespace nioverride_impl
		{
			namespace nioverride_impl_current
			{
				class variant : public slavetats_ng::skee::IOverrideInterface::SetVariant, public slavetats_ng::skee::IOverrideInterface::GetVariant
				{
				public:
					variant() :
						_type(Type::None) {}
					variant(int32_t a_i) :
						_type(Type::Int), _u{ a_i } {}
					variant(float a_f) :
						_type(Type::Float), _u{ ._flt = a_f } {}
					variant(const char* a_str) :
						_type(Type::String), _u{ ._str = a_str } {}
					variant(bool a_b) :
						_type(Type::Bool), _u{ ._bool = a_b } {}
					variant(const RE::BGSTextureSet* a_texset) :
						_type(Type::TextureSet), _u{ ._texset = a_texset } {}

					virtual Type               GetType() override { return _type; }
					virtual int32_t            Int() override { return _u._int; }
					virtual float              Float() override { return _u._flt; }
					virtual const char*        String() override { return _u._str; }
					virtual bool               Bool() override { return _u._bool; }
					virtual RE::BGSTextureSet* TextureSet() override { return const_cast<RE::BGSTextureSet*>(_u._texset); }

					virtual void Int(const int32_t i) override
					{
						_type = Type::Int;
						_u._int = i;
					}
					virtual void Float(const float f) override
					{
						_type = Type::Float;
						_u._flt = f;
					}
					virtual void String(const char* str) override
					{
						_type = Type::String;
						_u._str = str;
					}
					virtual void Bool(const bool b) override
					{
						_type = Type::Bool;
						_u._bool = b;
					}
					virtual void TextureSet(const RE::BGSTextureSet* textureSet) override
					{
						_type = Type::TextureSet;
						_u._texset = textureSet;
					}

				private:
					Type _type;
					union _u_t
					{
						int32_t                  _int;
						float                    _flt;
						bool                     _bool;
						const char*              _str;
						const RE::BGSTextureSet* _texset;
					} _u;
				};

				class current_binding : public NiOverride_functions
				{
				public:
					static inline skee::IOverrideInterface* _override_interface = nullptr;
					static inline skee::IOverlayInterface*  _overlay_interface = nullptr;

					virtual void AddNodeOverrideFloat(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index, float a_value, [[maybe_unused]] bool a_persist) override
					{
						variant value(a_value);
						_override_interface->AddNodeOverride(a_ref, a_female, a_node, (uint16_t)a_key, (uint8_t)a_index, value);
					}
					virtual void AddNodeOverrideInt(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index, int a_value, [[maybe_unused]] bool a_persist) override
					{
						variant value(a_value);
						_override_interface->AddNodeOverride(a_ref, a_female, a_node, (uint16_t)a_key, (uint8_t)a_index, value);
					}

					virtual void AddNodeOverrideString(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index, const char* a_value, [[maybe_unused]] bool a_persist) override
					{
						variant value(a_value);
						_override_interface->AddNodeOverride(a_ref, a_female, a_node, (uint16_t)a_key, (uint8_t)a_index, value);
					}

					virtual void AddOverlays(RE::TESObjectREFR* a_ref) override
					{
						_overlay_interface->AddOverlays(a_ref);
					}

					virtual void ApplyNodeOverrides(RE::Actor* a_actor) override
					{
						_override_interface->SetNodeProperties(a_actor, false);
					}

					virtual float GetNodeOverrideFloat(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index) override
					{
						variant result;
						if (_override_interface->GetNodeOverride(a_ref, a_female, a_node, (uint16_t)a_key, (uint8_t)a_index, result))
							return result.Float();
						else
							return 0.f;
					}

					virtual int GetNodeOverrideInt(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index) override
					{
						variant result;
						if (_override_interface->GetNodeOverride(a_ref, a_female, a_node, (uint16_t)a_key, (uint8_t)a_index, result))
							return result.Int();
						else
							return 0;
					}

					virtual RE::BSFixedString GetNodeOverrideString(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index) override
					{
						variant result;
						if (_override_interface->GetNodeOverride(a_ref, a_female, a_node, (uint16_t)a_key, (uint8_t)a_index, result))
							return result.String();
						else
							return "";
					}

					virtual bool HasNodeOverride(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index) override
					{
						return _override_interface->HasNodeOverride(a_ref, a_female, a_node, (uint16_t)a_key, (uint8_t)a_index);
					}

					virtual bool HasOverlays(RE::TESObjectREFR* a_ref) override
					{
						return _overlay_interface->HasOverlays(a_ref);
					}

					virtual void RemoveNodeOverride(RE::TESObjectREFR* a_ref, bool a_female, const char* a_node, int a_key, int a_index) override
					{
						_override_interface->RemoveNodeOverride(a_ref, a_female, a_node, (uint16_t)a_key, (uint8_t)a_index);
					}

					virtual void RemoveOverlays(RE::TESObjectREFR* a_ref) override
					{
						_overlay_interface->RemoveOverlays(a_ref);
					}

					static inline NiOverride_functions* singleton()
					{
						static current_binding instance;

						static std::atomic_bool initialized;
						static std::latch       latch(1);

						if (!initialized.exchange(true)) {
							if (auto iMap = skee_wrapper::get_interface_map()) {
								instance._override_interface = skee_wrapper::get_override_interface(iMap);
								instance._overlay_interface = skee_wrapper::get_overlay_interface(iMap);
							}

							latch.count_down();
						}

						latch.wait();

						return &instance;
					}
				};
			}
		}
	}
}
