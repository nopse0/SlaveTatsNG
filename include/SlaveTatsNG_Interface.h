#pragma once

//#include <cstdint>
//#include "RE/Skyrim.h"

// Stupid name I chose, collides with combaseapi.h (or so)
#ifdef interface
#	undef interface
#endif

namespace slavetats
{
	typedef bool fail_t;

	namespace interface
	{
		enum MessageType
		{
			None,
			Interface,
		};

		struct Addresses
		{
			enum
			{
				// This header is for interface version one
				version = 1,
			};

			uint32_t current_version;

			static const Addresses* from_void(void* iface)
			{
				return ((Addresses*)iface)->current_version == version ? (Addresses*)iface : nullptr;
			}

			// public api
			fail_t (*simple_add_tattoo)(RE::Actor* target, RE::BSFixedString section, RE::BSFixedString name, int color, bool last, bool silent, float alpha);
			fail_t (*simple_remove_tattoo)(RE::Actor* target, RE::BSFixedString section, RE::BSFixedString name, bool last, bool silent);
			fail_t (*synchronize_tattoos)(RE::Actor* target, bool silent);
			void (*log_tattoo)(RE::BSFixedString message, int tattoo);

			// implementation, use at your own risk
			bool (*tattoo_matches)(int a_template, int tattoo, bool include_configurable);
			void (*_append)(int dest, int val);
			void (*_extend_matching)(int dest, int src, int a_template, int applied, RE::BSFixedString domain);
			fail_t (*query_available_tattoos)(int a_template, int matches, int applied, RE::BSFixedString domain);
			fail_t (*query_applied_tattoos)(RE::Actor* target, int a_template, int matches, RE::BSFixedString except_area, int except_slot);
			fail_t (*query_applied_tattoos_with_attribute)(RE::Actor* target, RE::BSFixedString attrib, int matches, RE::BSFixedString except_area, int except_slot);
			bool (*has_applied_tattoos_with_attribute)(RE::Actor* target, RE::BSFixedString attrib, RE::BSFixedString except_area, int except_slot);
			fail_t (*remove_tattoos)(RE::Actor* target, int a_template, bool ignore_lock, bool silent);
			fail_t (*remove_tattoo_from_slot)(RE::Actor* target, RE::BSFixedString area, int slot, bool ignore_lock, bool silent);
			int (*get_applied_tattoo_in_slot)(RE::Actor* target, RE::BSFixedString area, int slot);
			fail_t (*get_applied_tattoos_by_area)(RE::Actor* target, int on_body, int on_face, int on_hands, int on_feet);
			fail_t (*external_slots)(RE::Actor* target, RE::BSFixedString area, int matches);
			fail_t (*add_tattoo)(RE::Actor* target, int tattoo, int slot, bool ignore_lock, bool silent);
			int (*add_and_get_tattoo)(RE::Actor* target, int tattoo, int slot, bool ignore_lock, bool silent, bool try_upgrade);
			RE::TESForm* (*get_form)(int tattoo, RE::BSFixedString plugin_field, RE::BSFixedString formid_field, RE::TESForm* a_default);
			void (*_log_jcontainer)(int jc, RE::BSFixedString indent);

			// Added a new function to the address table, so strictly this isn't version one anymore, but (hopefully) it is compatible to version one (no padding for the first element
			// of a struct, and function pointers are just 64 bit integers (I hope)).
			int (*compile_cache)();
		};

		// SINGLETON CODE IS COPIED FROM CLIB_UTIL
		//
		// singleton base class
		// adapted from https://github.com/Qudix/QUI-SKSE/blob/main/src/c%2B%2B/General/Singleton.hpp

		class address_holder
		{
		public:
			// Initialize this before using it!
			const Addresses* iface = nullptr;
			static address_holder* get()
			{
				static address_holder _singleton;
				return std::addressof(_singleton);
			}

			address_holder() = default;
			~address_holder() = default;
			address_holder(const address_holder&) = delete;
			address_holder(address_holder&&) = delete;
			address_holder& operator=(const address_holder&) = delete;
			address_holder& operator=(address_holder&&) = delete;
		};
	}

	using namespace slavetats::interface;

	inline bool simple_add_tattoo(RE::Actor* target, RE::BSFixedString section, RE::BSFixedString name, int color = 0, bool last = true, bool silent = false, float alpha = 1.0)
	{
		return address_holder::get()->iface->simple_add_tattoo(target, section, name, color, last, silent, alpha);
	}
	inline bool simple_remove_tattoo(RE::Actor* target, RE::BSFixedString section, RE::BSFixedString name, bool last = true, bool silent = false)
	{
		return address_holder::get()->iface->simple_remove_tattoo(target, section, name, last, silent);
	}
	inline bool synchronize_tattoos(RE::Actor* target, bool silent = false)
	{
		return address_holder::get()->iface->synchronize_tattoos(target, silent);
	}
	inline void log_tattoo(RE::BSFixedString message, int tattoo)
	{
		return address_holder::get()->iface->log_tattoo(message, tattoo);
	}
	inline bool tattoo_matches(int a_template, int tattoo, bool include_configurable = false)
	{
		return address_holder::get()->iface->tattoo_matches(a_template, tattoo, include_configurable);
	}
	inline void _append(int dest, int val)
	{
		address_holder::get()->iface->_append(dest, val);
	}
	inline void _extend_matching(int dest, int src, int a_template, int applied = 0, RE::BSFixedString domain = "default")
	{
		address_holder::get()->iface->_extend_matching(dest, src, a_template, applied, domain);
	}
	inline bool query_available_tattoos(int a_template, int matches, int applied = 0, RE::BSFixedString domain = "default")
	{
		return address_holder::get()->iface->query_available_tattoos(a_template, matches, applied, domain);
	}
	inline bool query_applied_tattoos(RE::Actor* target, int a_template, int matches, RE::BSFixedString except_area = "", int except_slot = -1)
	{
		return address_holder::get()->iface->query_applied_tattoos(target, a_template, matches, except_area, except_slot);
	}
	inline bool query_applied_tattoos_with_attribute(RE::Actor* target, RE::BSFixedString attrib, int matches, RE::BSFixedString except_area = "", int except_slot = -1)
	{
		return address_holder::get()->iface->query_applied_tattoos_with_attribute(target, attrib, matches, except_area, except_slot);
	}
	inline bool has_applied_tattoos_with_attribute(RE::Actor* target, RE::BSFixedString attrib, RE::BSFixedString except_area = "", int except_slot = -1)
	{
		return address_holder::get()->iface->has_applied_tattoos_with_attribute(target, attrib, except_area, except_slot);
	}
	inline bool remove_tattoos(RE::Actor* target, int a_template, bool ignore_lock = false, bool silent = false)
	{
		return address_holder::get()->iface->remove_tattoos(target, a_template, ignore_lock, silent);
	}
	inline bool remove_tattoo_from_slot(RE::Actor* target, RE::BSFixedString area, int slot, bool ignore_lock = false, bool silent = false)
	{
		return address_holder::get()->iface->remove_tattoo_from_slot(target, area, slot, ignore_lock, silent);
	}
	inline int get_applied_tattoo_in_slot(RE::Actor* target, RE::BSFixedString area, int slot)
	{
		return address_holder::get()->iface->get_applied_tattoo_in_slot(target, area, slot);
	}
	inline bool get_applied_tattoos_by_area(RE::Actor* target, int on_body, int on_face, int on_hands, int on_feet)
	{
		return address_holder::get()->iface->get_applied_tattoos_by_area(target, on_body, on_face, on_hands, on_feet);
	}
	inline bool external_slots(RE::Actor* target, RE::BSFixedString area, int matches)
	{
		return address_holder::get()->iface->external_slots(target, area, matches);
	}
	inline bool add_tattoo(RE::Actor* target, int tattoo, int slot = -1, bool ignore_lock = false, bool silent = false)
	{
		return address_holder::get()->iface->add_tattoo(target, tattoo, slot, ignore_lock, silent);
	}
	inline int add_and_get_tattoo(RE::Actor* target, int tattoo, int slot = -1, bool ignore_lock = false, bool silent = false,
		bool try_upgrade = true)
	{
		return address_holder::get()->iface->add_and_get_tattoo(target, tattoo, slot, ignore_lock, silent, try_upgrade);
	}
	inline RE::TESForm* get_form(int tattoo, RE::BSFixedString plugin_field, RE::BSFixedString formid_field, RE::TESForm* a_default = nullptr)
	{
		return address_holder::get()->iface->get_form(tattoo, plugin_field, formid_field, a_default);
	}
	inline void _log_jcontainer(int jc, RE::BSFixedString indent)
	{
		address_holder::get()->iface->_log_jcontainer(jc, indent);
	}
	inline void compile_cache()
	{
		address_holder::get()->iface->compile_cache();
	}
}
