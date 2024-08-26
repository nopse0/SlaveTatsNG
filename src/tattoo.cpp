#include "../include/jcontainers_wrapper.h"
#include "../include/constants.h"
#include "../include/overlays.h"
#include "../include/skse64_native_papyrus.h"
#include "../include/primary_api.h"
#include "../include/query.h"
#include "../include/logging.h"
#include <cstring>
#include "../include/tattoo.h"

using namespace slavetats_ng::skee_wrapper;
using namespace slavetats_ng::jcwrapper;
namespace StringUtil = skse64_native_papyrus;
using std::string;
using std::to_string;

namespace slavetats_ng
{
	fail_t external_slots(RE::Actor* a_target, RE::BSFixedString a_area, int a_matches)
	{
		if (!a_target) {
			logger::info("a_target is null");
			return true;
		}

		RE::TESNPC* npc = a_target->GetActorBase();
		bool isFemale = (bool)(npc->GetSex() == 1);

		RE::BSFixedString prefix = PREFIX();
		RE::BSFixedString suffix = "default.dds";

		int prefix_length = (int)prefix.length();
		int suffix_length = (int)suffix.length();

		int i = SLOTS(a_area);
		while (i > 0) {
			i -= 1;
			RE::BSFixedString nodeName = string(a_area) + " [Ovl " + to_string(i) + "]";
			RE::BSFixedString overlay_path = NiOverride::GetNodeOverrideString(a_target, isFemale, nodeName.c_str(), 9, 0);
			RE::BSFixedString suffixWithSep(string("\\") + suffix.c_str());

			if (overlay_path != "" &&
				StringUtil::SubString(overlay_path, 0, prefix_length) != prefix.c_str() &&
				overlay_path != suffix &&
				StringUtil::SubString(overlay_path, (int)overlay_path.length() - suffix_length - 1) != suffixWithSep)
				{
				JArray::addInt(a_matches, i);
			} else {
				overlay_path = NiOverride::GetNodeOverrideString(a_target, isFemale, nodeName.c_str(), 9, 6);
				if (overlay_path != "" &&
					StringUtil::SubString(overlay_path, 0, prefix_length) != prefix.c_str() &&
					overlay_path != suffix &&
					StringUtil::SubString(overlay_path, (int)overlay_path.length() - suffix_length - 1) != suffixWithSep) {
					JArray::addInt(a_matches, i);
				}
			}
		}
		return false;
	}

	fail_t get_applied_tattoos_by_area(RE::Actor* a_target, int a_on_body, int a_on_face, int a_on_hands, int a_on_feet)
	{
		if (!a_target) {
			logger::info("a_target is null");
			return true;
		}

		int applied = JFormDB::getObj(a_target, ".SlaveTats.applied");
		//logger::info("get_applied_tattoos_by_area, applied={}", applied);
		//_log_jcontainer(applied, "  ");
		if (applied == 0) {
			return false;
		}

		int i = JArray::count(applied);
		while (i > 0) {
			i -= 1;

			int entry = JArray::getObj(applied, i);
			RE::BSFixedString area = JMap::getStr(entry, "area");

			if (area == "Body")
				JArray::addObj(a_on_body, entry);
			else if (area == "Face")
				JArray::addObj(a_on_face, entry);
			else if (area == "Hands")
				JArray::addObj(a_on_hands, entry);
			else if (area == "Feet")
				JArray::addObj(a_on_feet, entry);
			else {
				logger::error("Applied tattoo {} has unknown area {}", JMap::getStr(entry, "name").c_str(), area.c_str());
			}
		}

		return false;
	}

	int get_applied_tattoo_in_slot(RE::Actor* a_target, RE::BSFixedString a_area, int a_slot)
	{
		if (!a_target) {
			logger::info("a_target is null");
			return 0;
		}

		int a_template = JValue::addToPool(JMap::object(), "SlaveTats-get_applied_tattoo_in_slot");

		JMap::setStr(a_template, "area", a_area);
		JMap::setInt(a_template, "slot", a_slot);

		int matches = JValue::addToPool(JArray::object(), "SlaveTats-get_applied_tattoo_in_slot");

		if (query_applied_tattoos(a_target, a_template, matches))
		{
			JValue::cleanPool("SlaveTats-get_applied_tattoo_in_slot");
			return 0;
		}

		if (JArray::count(matches) == 0) {
			JValue::cleanPool("SlaveTats-get_applied_tattoo_in_slot");
			return 0;
		}

		int tattoo = JArray::getObj(matches, 0);

		JValue::cleanPool("SlaveTats-get_applied_tattoo_in_slot");
		return tattoo;
	}

	int _available_slot(RE::Actor* a_target, RE::BSFixedString a_area)
	{
		if (!a_target) {
			logger::info("a_target is null");
			return -1;
		}

		int external = JValue::addToPool(JArray::object(), "SlaveTats-_available_slot");

		if (external_slots(a_target, a_area, external)) {
			return -1;
		}

		int total = SLOTS(a_area);
		int i = 0;
		while (i < total) {
			if (JArray::findInt(external, i) == -1) {
				if (get_applied_tattoo_in_slot(a_target, a_area, i) == 0) {
					JValue::cleanPool("SlaveTats-_available_slot");
					return i;
				}
			}
			i += 1;
		}

		JValue::cleanPool("SlaveTats-_available_slot");
		return -1;
	}

	fail_t _remove_tattoos(RE::Actor* a_target, int a_template, bool a_ignore_lock, bool a_silent) {
		if (!a_target) {
			logger::info("a_target is null");
			return true;
		}

		int applied = JFormDB::getObj(a_target, ".SlaveTats.applied");
		if (applied == 0)
			return false;
		
		bool failed = false;

		int i = JArray::count(applied);
		while (i > 0) {
			i -= 1;

			int entry = JArray::getObj(applied, i);
			if (tattoo_matches(a_template, entry)) {
				if (JMap::getInt(entry, "locked") > 0 && !a_ignore_lock) {
					// TODO notify
					failed = true;
				} else {
					JArray::eraseIndex(applied, i);
					JFormDB::setInt(a_target, ".SlaveTats.updated", 1);
				}
			}
		}

		return failed;
	}

	fail_t remove_tattoos(RE::Actor* a_target, int a_template, bool a_ignore_lock, bool a_silent)
	{
		if (!a_target) {
			logger::info("a_target is null");
			return true;
		}

		log_tattoo("Asked to remove matching tattoos ", a_template);

		if (upgrade_tattoos(a_target)) {
			return true;
		}

		return _remove_tattoos(a_target, a_template, a_ignore_lock, a_silent);
	}

	fail_t remove_tattoo_from_slot(RE::Actor* a_target, RE::BSFixedString a_area, int a_slot, bool a_ignore_lock,
		bool a_silent) 
	{
		if (!a_target) {
			logger::info("a_target is null");
			return true;
		}

		int a_template = JValue::addToPool(JMap::object(), "SlaveTats-remove_tattoo_from_slot");

		JMap::setStr(a_template, "area", a_area);
		JMap::setInt(a_template, "slot", a_slot);

		if (_remove_tattoos(a_target, a_template, a_ignore_lock, a_silent)) {
			JValue::cleanPool("SlaveTats-remove_tattoo_from_slot");
			return true;
		}

		JValue::cleanPool("SlaveTats-remove_tattoo_from_slot");
		return false;
	}

	fail_t query_applied_tattoos_with_attribute(RE::Actor* a_target, RE::BSFixedString a_attrib, int a_matches,
		RE::BSFixedString a_except_area, int a_except_slot)
	{
		if (!a_target) {
			logger::info("a_target is null");
			return true;
		}

		int a_template = JValue::addToPool(JMap::object(), "SlaveTats-query_available_tattoos_with_attribute");
		JMap::setStr(a_template, a_attrib, "ANY");
		bool result = query_applied_tattoos(a_target, a_template, a_matches, a_except_area, a_except_slot);

		JValue::cleanPool("SlaveTats-query_available_tattoos_with_attribute");
		return result;
	}

	bool has_applied_tattoos_with_attribute(RE::Actor* a_target, RE::BSFixedString a_attrib, RE::BSFixedString a_except_area,
		int a_except_slot) {
		if (!a_target) {
			logger::info("a_target is null");
			return false;
		}

		int matches = JValue::addToPool(JArray::object(), "SlaveTats-has_applied_tattoos_with_attribute");
		if (query_applied_tattoos_with_attribute(a_target, a_attrib, matches, a_except_area, a_except_slot)) {
			// Log query failed
		}
		
		bool result = JArray::count(matches);
		// if (result) {
		//  Log first matching tattoo	
		//}

		JValue::cleanPool("SlaveTats-has_applied_tattoos_with_attribute"); 
		return (bool)result;
	}

	int _add_and_get_tattoo(RE::Actor* a_target, int a_tattoo, int a_slot, bool a_ignore_lock, bool a_silent)
	{
		if (!a_target) {
			logger::info("a_target is null");
			return 0;
		}

		RE::BSFixedString area = JMap::getStr(a_tattoo, "area");
		RE::BSFixedString texture = JMap::getStr(a_tattoo, "texture");

		if (a_slot == -1 && JMap::hasKey(a_tattoo, "slot")) {
			a_slot = JMap::getInt(a_tattoo, "slot");
		}

		if (a_slot == -1) {
			a_slot = _available_slot(a_target, area);
		}
		if (a_slot == -1) {
			return 0;
		}

		if (remove_tattoo_from_slot(a_target, area, a_slot, a_ignore_lock, a_silent)) {
			return 0;
		}

		if (texture == "") {
			return a_tattoo;
		}

		if (JMap::getInt(a_tattoo, "in_bsa") == 0) {
			if (!JContainers::fileExistsAtPath(string(ROOT()) + string(PREFIX()) + texture.c_str())) {
			 	return 0;
			}
		}

		RE::BSFixedString exclusion = JMap::getStr(a_tattoo, "excluded_by");
		if (exclusion != "") {
			if (has_applied_tattoos_with_attribute(a_target, exclusion)) {
				return 0;
			}
		}

		RE::BSFixedString requirement = JMap::getStr(a_tattoo, "requires");
		if (requirement != "") {
			if (!has_applied_tattoos_with_attribute(a_target, requirement)) {
				return 0;
			}
		}

		int applied = JFormDB::getObj(a_target, ".SlaveTats.applied");
		if (applied == 0) {
			applied = JValue::addToPool(JArray::object(), "SlaveTats-_add_and_get_tattoo");
			JFormDB::setObj(a_target, ".SlaveTats.applied", applied);
		}

		int apply_tattoo = JValue::addToPool(JValue::shallowCopy(a_tattoo), "SlaveTats-_add_and_get_tattoo");
		JMap::setInt(apply_tattoo, "slot", a_slot);
		JArray::addObj(applied, apply_tattoo);
		_log_jcontainer(applied, "  ");

		JFormDB::setInt(a_target, ".SlaveTats.updated", 1);

		JValue::cleanPool("SlaveTats-_add_and_get_tattoo");

		return apply_tattoo;
	}

	int add_and_get_tattoo(RE::Actor* a_target, int a_tattoo, int a_slot, bool a_ignore_lock,
		bool a_silent, bool a_try_upgrade)
	{
		if (!a_target) {
			logger::info("a_target is null");
			return 0;
		}

		log_tattoo("Asked to add a tattoo", a_tattoo);
		if (a_try_upgrade && upgrade_tattoos(a_target)) {
			return 0;
		}

		return _add_and_get_tattoo(a_target, a_tattoo, a_slot, a_ignore_lock, a_silent);
	}

	fail_t add_tattoo(RE::Actor* a_target, int a_tattoo, int a_slot, bool a_ignore_lock, bool a_silent)
	{
		if (!a_target) {
			logger::info("a_target is null");
			return true;
		}

		if (add_and_get_tattoo(a_target, a_tattoo, a_slot, a_ignore_lock, a_silent) == 0) {
			return true;
		}
		return false;
	}

}
