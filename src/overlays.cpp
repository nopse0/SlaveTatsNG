#include "../include/jcontainers_wrapper.h"
#include "../include/constants.h"
#include "../include/overlays.h"
#include "../include/skse64_native_papyrus.h"
#include "../include/primary_api.h"
#include "../include/query.h"
#include "../include/tattoo.h"
#include "../include/tattoo_magic.h"
#include "../include/overlays.h"
#include "../include/logging.h"


using namespace slavetats_ng::skee_wrapper;
using namespace slavetats_ng::jcwrapper;
namespace StringUtil = skse64_native_papyrus;
using std::string;
using std::to_string;

namespace slavetats_ng
{
	fail_t clear_overlay(RE::Actor* a_target, bool a_is_female, RE::BSFixedString a_area, int a_slot)
	{
		RE::BSFixedString nodeName = string(a_area) + " [ovl" + to_string(a_slot) + "]";
		// RE::BSFixedString blankPrefix = string(PREFIX()) + "blank.dds";
		RE::BSFixedString blankPrefix = "actors\\character\\overlays\\default.dds";

		NiOverride::AddNodeOverrideString(a_target, a_is_female, nodeName.c_str(), 9, 0, blankPrefix.c_str(), true);
		
		bool hasBumpOverride = NiOverride::HasNodeOverride(a_target, a_is_female, nodeName.c_str(), 9, 1);
		if (hasBumpOverride)
			NiOverride::AddNodeOverrideString(a_target, a_is_female, nodeName.c_str(), 9, 1, blankPrefix.c_str(), true);

		NiOverride::ApplyNodeOverrides(a_target);

		if (hasBumpOverride)
			NiOverride::RemoveNodeOverride(a_target, a_is_female, nodeName.c_str(), 9, 1);

		NiOverride::RemoveNodeOverride(a_target, a_is_female, nodeName.c_str(), 9, 0);
	
		NiOverride::RemoveNodeOverride(a_target, a_is_female, nodeName.c_str(), 7, -1);
		
		NiOverride::RemoveNodeOverride(a_target, a_is_female, nodeName.c_str(), 0, -1);
		
		NiOverride::RemoveNodeOverride(a_target, a_is_female, nodeName.c_str(), 1, -1);
		
		NiOverride::RemoveNodeOverride(a_target, a_is_female, nodeName.c_str(), 8, -1);
		
		NiOverride::RemoveNodeOverride(a_target, a_is_female, nodeName.c_str(), 2, -1);
		
		NiOverride::RemoveNodeOverride(a_target, a_is_female, nodeName.c_str(), 3, -1);

		logger::info("Cleared {}", nodeName.c_str());

		return false;
	}

	fail_t apply_overlay(RE::Actor* a_target, bool a_is_female, RE::BSFixedString a_area, int a_slot, RE::BSFixedString a_path, int a_color,
		int a_glow, bool a_gloss, RE::BSFixedString a_bump, float a_alpha)
	{
		RE::BSFixedString nodeName = string(a_area) + " [Ovl" + to_string(a_slot) + "]";
		NiOverride::AddNodeOverrideString(a_target, a_is_female, nodeName.c_str(), 9, 0, a_path.c_str(), true);
		// Utility.Wait(0.01)
		if (!a_bump.empty()) {
			NiOverride::AddNodeOverrideString(a_target, a_is_female, nodeName.c_str(), 9, 1, a_bump.c_str(), true);
			// Utility.Wait(0.01)
		}
		NiOverride::AddNodeOverrideInt(a_target, a_is_female, nodeName.c_str(), 7, -1, a_color, true);
		// Utility.Wait(0.01)
		NiOverride::AddNodeOverrideInt(a_target, a_is_female, nodeName.c_str(), 0, -1, a_glow, true);
		// Utility.Wait(0.01)
		NiOverride::AddNodeOverrideFloat(a_target, a_is_female, nodeName.c_str(), 1, -1, 1.0, true);
		// Utility.Wait(0.01)
		NiOverride::AddNodeOverrideFloat(a_target, a_is_female, nodeName.c_str(), 8, -1, a_alpha, true);
		// Utility.Wait(0.01)
		if (a_gloss) {
			NiOverride::AddNodeOverrideFloat(a_target, a_is_female, nodeName.c_str(), 2, -1, 5.0, true);
			// Utility.Wait(0.01)
			NiOverride::AddNodeOverrideFloat(a_target, a_is_female, nodeName.c_str(), 3, -1, 5.0, true);
			// Utility.Wait(0.01)
		} else {
			NiOverride::AddNodeOverrideFloat(a_target, a_is_female, nodeName.c_str(), 2, -1, 0.0, true);
			// Utility.Wait(0.01)
			NiOverride::AddNodeOverrideFloat(a_target, a_is_female, nodeName.c_str(), 3, -1, 0.0, true);
			// Utility.Wait(0.01)		
		}

		NiOverride::ApplyNodeOverrides(a_target);

		logger::info("Applied {} = {}:{}:{}:{}", nodeName.c_str(), a_path.c_str(), a_color, a_glow, a_gloss);

		return false;
	}

	fail_t upgrade_tattoos(RE::Actor* a_target) 
	{
		if (!a_target) {
			return true;
		}

		RE::BSFixedString actor_version = JFormDB::getStr(a_target, ".SlaveTats.version");
		RE::BSFixedString code_version = VERSION();

		if (actor_version == code_version)
			return false;

		RE::BSFixedString path;
		int    i;
		int    a_template;
		int    matches;
		int    entry;

		RE::BSFixedString prefix = PREFIX();
		int    prefix_len = (int)prefix.length();

		if (actor_version == "") {
			JFormDB::setObj(a_target, ".SlaveTats.applied", JArray::object());
			actor_version = "1.0.0";

			bool isFemale = a_target->GetActorBase()->GetSex() == 1;

			a_template = JValue::addToPool(JMap::object(), "SlaveTats-upgrade_tattoos");
			matches = JValue::addToPool(JArray::object(), "SlaveTats-upgrade_tattoos");

			RE::BSFixedString area = "Body"; 
			i = SLOTS(area);
			while (i > 0) {
				i -= 1;

				RE::BSFixedString nodeName = string(area) + " [Ovl" + to_string(i) + "]";
				path = NiOverride::GetNodeOverrideString(a_target, isFemale, nodeName.c_str(), 9, 0);
				if (StringUtil::SubString(path, 0, prefix_len) == prefix.c_str()) {
					JMap::setStr(a_template, "texture", RE::BSFixedString("*" + string(path).substr(prefix_len)));
					JArray::clear(matches);
					query_available_tattoos(a_template, matches);
					if (JArray::count(matches)) {
						entry = JArray::getObj(matches, 0);
						JMap::setInt(entry, "color", NiOverride::GetNodeOverrideInt(a_target, isFemale, nodeName.c_str(), 7, -1));
						JMap::setInt(entry, "glow", NiOverride::GetNodeOverrideInt(a_target, isFemale, nodeName.c_str(), 0, -1));
						if (NiOverride::GetNodeOverrideFloat(a_target, isFemale, nodeName.c_str(), 2, -1) > 0.0) {
							JMap::setInt(entry, "gloss", 1);
						}
						_add_and_get_tattoo(a_target, entry, i, true, false);
					} else {
						// Log no matching entry found
					}
				}
			}
			// Why no color, glow and gloss for Face, Hands, Feet ??? Is this a bug ? TODO  
			area = "Face";
			i = SLOTS(area);
			while (i > 0) {
				i -= 1;

				RE::BSFixedString nodeName = string(area) + " [Ovl" + to_string(i) + "]";
				path = NiOverride::GetNodeOverrideString(a_target, isFemale, nodeName.c_str(), 9, 0);
				if (StringUtil::SubString(path, 0, prefix_len) == prefix.c_str()) {
					JMap::setStr(a_template, "texture", RE::BSFixedString("*" + string(path).substr(prefix_len)));
					JArray::clear(matches);
					query_available_tattoos(a_template, matches);
					if (JArray::count(matches)) {
						entry = JArray::getObj(matches, 0);
						_add_and_get_tattoo(a_target, entry, i, true, false);
					} else {
						// Log no matching entry found
					}
				}
			}
			area = "Hands";
			i = SLOTS(area);
			while (i > 0) {
				i -= 1;

				RE::BSFixedString nodeName = string(area) + " [Ovl" + to_string(i) + "]";
				path = NiOverride::GetNodeOverrideString(a_target, isFemale, nodeName.c_str(), 9, 0);
				if (StringUtil::SubString(path, 0, prefix_len) == prefix.c_str()) {
					JMap::setStr(a_template, "texture", RE::BSFixedString("*" + string(path).substr(prefix_len)));
					JArray::clear(matches);
					query_available_tattoos(a_template, matches);
					if (JArray::count(matches)) {
						entry = JArray::getObj(matches, 0);
						_add_and_get_tattoo(a_target, entry, i, true, false);
					} else {
						// Log no matching entry found
					}
				}
			}
			area = "Feet";
			i = SLOTS(area);
			while (i > 0) {
				i -= 1;

				RE::BSFixedString nodeName = string(area) + " [Ovl" + to_string(i) + "]";
				path = NiOverride::GetNodeOverrideString(a_target, isFemale, nodeName.c_str(), 9, 0);
				if (StringUtil::SubString(path, 0, prefix_len) == prefix.c_str()) {
					JMap::setStr(a_template, "texture", RE::BSFixedString("*" + string(path).substr(prefix_len)));
					JArray::clear(matches);
					query_available_tattoos(a_template, matches);
					if (JArray::count(matches)) {
						entry = JArray::getObj(matches, 0);
						_add_and_get_tattoo(a_target, entry, i, true, false);
					} else {
						// Log no matching entry found
					}
				}
			}

			JFormDB::setStr(a_target, ".SlaveTats.version", actor_version);
			JFormDB::setInt(a_target, ".SlaveTats.updated", 1);
		}

		JValue::cleanPool("SlaveTats-upgrade_tattoos");
		return false;
	}

	fail_t synchronize_tattoos(RE::Actor* a_target, bool a_silent)
	{
		int i;
		int idx;
		int entry;
		RE::BSFixedString area;
		int    slot;
		RE::BSFixedString path;
		int    color;
		int    glow;
		bool   gloss;
		RE::BSFixedString bump;
		float  alpha;

		RE::TESNPC* actor_base = a_target->GetActorBase();
		RE::BSFixedString actor_name = actor_base->GetName();
		bool        isFemale = actor_base->GetSex() == 1;
		logger::info("SlaveTats: Beginning synchronization for {}", actor_name.c_str());

		if (!NiOverride::HasOverlays(a_target)) {
			NiOverride::AddOverlays(a_target);
			// TODO delay ?
			if (!NiOverride::HasOverlays(a_target)) {
				logger::error("AddOverlays failed");
				return true;
			}
		}

		if (upgrade_tattoos(a_target)) {
			logger::error("upgrade_tattoos failed");
			return true;
		}

		if (JFormDB::getInt(a_target, ".SlaveTats.updated") == 0) {
			logger::info("According to JFormDB, nothing ´has changed. Cancelling synchronization.");
			return false;
		}

		// TODO notification, disable player controls
		// if (!a_silent) {
		//
		//}

		RE::BSFixedString prefix = PREFIX();

		int on_body = JValue::addToPool(JArray::object(), "SlaveTats-synchronize_tattoos");
		int on_face = JValue::addToPool(JArray::object(), "SlaveTats-synchronize_tattoos");
		int on_hands = JValue::addToPool(JArray::object(), "SlaveTats-synchronize_tattoos");
		int on_feet = JValue::addToPool(JArray::object(), "SlaveTats-synchronize_tattoos");

		int external_on_body = JValue::addToPool(JArray::object(), "SlaveTats-synchronize_tattoos");
		int external_on_face = JValue::addToPool(JArray::object(), "SlaveTats-synchronize_tattoos");
		int external_on_hands = JValue::addToPool(JArray::object(), "SlaveTats-synchronize_tattoos");
		int external_on_feet = JValue::addToPool(JArray::object(), "SlaveTats-synchronize_tattoos");

		int applied = JFormDB::getObj(a_target, ".SlaveTats.applied");
		bool loop = true;

		while (loop) {
			loop = false;

			i = JArray::count(applied);
			while (i > 0) {
				i -= 1;

				if (find_required_tattoo(applied, JArray::getObj(applied, i)) < 0) {
					remove_tattoos(a_target, JArray::getObj(applied, i), true, a_silent);
					loop = true;
				}
			}
		}

		if (get_applied_tattoos_by_area(a_target, on_body, on_face, on_hands, on_feet)) {
			if (!a_silent) {
				// TODO Enable player controls
			}
			JValue::cleanPool("SlaveTats-synchronize_tattoos");
			return true;
		}
		
		if (external_slots(a_target, "Body", external_on_body)) {
			if (!a_silent) {
				// TODO Enable player controls
			}
			JValue::cleanPool("SlaveTats-synchronize_tattoos");
			return true;
		}

		if (external_slots(a_target, "Face", external_on_face)) {
			if (!a_silent) {
				// TODO Enable player controls
			}
			JValue::cleanPool("SlaveTats-synchronize_tattoos");
			return true;
		}

		if (external_slots(a_target, "Hands", external_on_hands)) {
			if (!a_silent) {
				// TODO Enable player controls
			}
			JValue::cleanPool("SlaveTats-synchronize_tattoos");
			return true;
		}

		if (external_slots(a_target, "Feet", external_on_feet)) {
			if (!a_silent) {
				// TODO Enable player controls
			}
			JValue::cleanPool("SlaveTats-synchronize_tattoos");
			return true;
		}

		int on_body_count = JArray::count(on_body);
		int on_face_count = JArray::count(on_face);
		int on_hands_count = JArray::count(on_hands);
		int on_feet_count = JArray::count(on_feet);

		int external_on_body_count = JArray::count(external_on_body);
		int external_on_face_count = JArray::count(external_on_face);
		int external_on_hands_count = JArray::count(external_on_hands);
		int external_on_feet_count = JArray::count(external_on_feet);

		if (on_body_count + on_face_count + on_hands_count + on_feet_count == 0) {
			deactivate_all_tattoo_magic(a_target);

			i = SLOTS("Body");
			while (i > 0) {
				i -= 1;

				if (JArray::findInt(external_on_body, i) == -1) {
					clear_overlay(a_target, isFemale, "Body", i);
				}
			}

			i = SLOTS("Face");
			while (i > 0) {
				i -= 1;

				if (JArray::findInt(external_on_face, i) == -1) {
					clear_overlay(a_target, isFemale, "Face", i);
				}
			}

			i = SLOTS("Hands");
			while (i > 0) {
				i -= 1;

				if (JArray::findInt(external_on_hands, i) == -1) {
					clear_overlay(a_target, isFemale, "Hands", i);
				}
			}

			i = SLOTS("Feet");
			while (i > 0) {
				i -= 1;

				if (JArray::findInt(external_on_feet, i) == -1) {
					clear_overlay(a_target, isFemale, "Feet", i);
				}
			}
		
			if (external_on_body_count + external_on_face_count + external_on_hands_count + external_on_feet_count == 0) {
				NiOverride::RemoveOverlays(a_target);
				// TODO Utility.Wait(0.01)

				// TODO test if GetIsPlayerOwner works
				if (NiOverride::HasOverlays(a_target) && !actor_base->GetIsPlayerOwner()) {
					logger::error("NPC overlay uninstallation failed");
					if (!a_silent) {
						// TODO Enable player controls
					}
					JValue::cleanPool("SlaveTats-synchronize_tattoos");
					return true;
				}
			}
		
			JFormDB::setEntry("SlaveTats", a_target, 0);

			logger::info("SlaveTats is done with {}", actor_name.c_str());

			if (!a_silent) {
				// TODO Enable player controls
			}
			JValue::cleanPool("SlaveTats-synchronize_tattoos");
			return false;
		}

		int empty_body_slots = JValue::addToPool(JArray::object(), "SlaveTats-synchronize_tattoos");
		int empty_face_slots = JValue::addToPool(JArray::object(), "SlaveTats-synchronize_tattoos");
		int empty_hands_slots = JValue::addToPool(JArray::object(), "SlaveTats-synchronize_tattoos");
		int empty_feet_slots = JValue::addToPool(JArray::object(), "SlaveTats-synchronize_tattoos");

		i = SLOTS("Body");
		while (i > 0) {
			i -= 1;
			JArray::addInt(empty_body_slots, i);
		}

		i = SLOTS("Face");
		while (i > 0) {
			i -= 1;
			JArray::addInt(empty_face_slots, i);
		}

		i = SLOTS("Hands");
		while (i > 0) {
			i -= 1;
			JArray::addInt(empty_hands_slots, i);
		}

		i = SLOTS("Feet");
		while (i > 0) {
			i -= 1;
			JArray::addInt(empty_feet_slots, i);
		}

		int to_deactivate = JValue::addToPool(JArray::object(), "SlaveTats-synchronize_tattoos");
		int to_activate = JValue::addToPool(JArray::object(), "SlaveTats-synchronize_tattoos");

		int activated = JFormDB::getObj(a_target, ".SlaveTats.activated");
		if (activated) {
			JArray::addFromArray(to_deactivate, activated);
		}

		i = on_body_count;
		while (i > 0) {
			i -= 1;

			entry = JArray::getObj(on_body, i);
			if (is_tattoo(entry)) {
				slot = JMap::getInt(entry, "slot");
				path = string(prefix) + string(JMap::getStr(entry, "texture"));
				color = JMap::getInt(entry, "color");
				glow = JMap::getInt(entry, "glow");
				gloss = (bool)JMap::getInt(entry, "gloss");
				bump = JMap::getStr(entry, "bump");
				alpha = 1.0f - JMap::getFlt(entry, "invertedAlpha");
				if (!bump.empty())
					bump = string(prefix) + string(bump);
				if (JArray::findInt(external_on_body, slot) < 0) {
					if (!apply_overlay(a_target, isFemale, "Body", slot, path, color, glow, gloss, bump, alpha)) {
						JArray::addObj(to_activate, entry);
						idx = JArray::findInt(empty_body_slots, slot);
						if (idx >= 0) {
							JArray::eraseIndex(empty_body_slots, idx);
						}
					}
				}
			}
		}

		i = on_face_count;
		while (i > 0) {
			i -= 1;

			entry = JArray::getObj(on_face, i);
			if (is_tattoo(entry)) {
				slot = JMap::getInt(entry, "slot");
				path = string(prefix) + string(JMap::getStr(entry, "texture"));
				color = JMap::getInt(entry, "color");
				glow = JMap::getInt(entry, "glow");
				gloss = (bool)JMap::getInt(entry, "gloss");
				bump = JMap::getStr(entry, "bump");
				alpha = 1.0f - JMap::getFlt(entry, "invertedAlpha");
				if (JArray::findInt(external_on_face, slot) < 0) {
					if (!apply_overlay(a_target, isFemale, "Face", slot, path, color, glow, gloss, bump, alpha)) {
						JArray::addObj(to_activate, entry);
						idx = JArray::findInt(empty_face_slots, slot);
						if (idx >= 0) {
							JArray::eraseIndex(empty_face_slots, idx);
						}
					}
				}
			}
		}

		i = on_hands_count;
		while (i > 0) {
			i -= 1;

			entry = JArray::getObj(on_hands, i);
			if (is_tattoo(entry)) {
				slot = JMap::getInt(entry, "slot");
				path = string(prefix) + string(JMap::getStr(entry, "texture"));
				color = JMap::getInt(entry, "color");
				glow = JMap::getInt(entry, "glow");
				gloss = (bool)JMap::getInt(entry, "gloss");
				bump = JMap::getStr(entry, "bump");
				alpha = 1.0f - JMap::getFlt(entry, "invertedAlpha");
				if (JArray::findInt(external_on_hands, slot) < 0) {
					if (!apply_overlay(a_target, isFemale, "Hands", slot, path, color, glow, gloss, bump, alpha)) {
						JArray::addObj(to_activate, entry);
						idx = JArray::findInt(empty_hands_slots, slot);
						if (idx >= 0) {
							JArray::eraseIndex(empty_hands_slots, idx);
						}
					}
				}
			}
		}

		entry = JArray::getObj(on_feet, i);
		if (is_tattoo(entry)) {
			slot = JMap::getInt(entry, "slot");
			path = string(prefix) + string(JMap::getStr(entry, "texture"));
			color = JMap::getInt(entry, "color");
			glow = JMap::getInt(entry, "glow");
			gloss = (bool)JMap::getInt(entry, "gloss");
			bump = JMap::getStr(entry, "bump");
			alpha = 1.0f - JMap::getFlt(entry, "invertedAlpha");
			if (JArray::findInt(external_on_feet, slot) < 0) {
				if (!apply_overlay(a_target, isFemale, "Feet", slot, path, color, glow, gloss, bump, alpha)) {
					JArray::addObj(to_activate, entry);
					idx = JArray::findInt(empty_feet_slots, slot);
					if (idx >= 0) {
						JArray::eraseIndex(empty_feet_slots, idx);
					}
				}
			}
		}

		i = JArray::count(empty_body_slots);
		while (i > 0) {
			i -= 1;

			slot = JArray::getInt(empty_body_slots, i);
			if (JArray::findInt(external_on_body, slot) < 0) {
				clear_overlay(a_target, isFemale, "Body", slot);
			}
		}

		i = JArray::count(empty_face_slots);
		while (i > 0) {
			i -= 1;

			slot = JArray::getInt(empty_face_slots, i);
			if (JArray::findInt(external_on_face, slot) < 0) {
				clear_overlay(a_target, isFemale, "Face", slot);
			}
		}

		i = JArray::count(empty_hands_slots);
		while (i > 0) {
			i -= 1;

			slot = JArray::getInt(empty_hands_slots, i);
			if (JArray::findInt(external_on_hands, slot) < 0) {
				clear_overlay(a_target, isFemale, "Hands", slot);
			}
		}

		i = JArray::count(empty_feet_slots);
		while (i > 0) {
			i -= 1;

			slot = JArray::getInt(empty_feet_slots, i);
			if (JArray::findInt(external_on_feet, slot) < 0) {
				clear_overlay(a_target, isFemale, "Feet", slot);
			}
		}

		JFormDB::setInt(a_target, ".SlaveTats.updated", 0);

		i = JArray::count(to_deactivate);
		while (i > 0) {
			i -= 1;

			idx = JArray::findObj(to_activate, JArray::getObj(to_deactivate, i));
			if (idx >= 0) {
				JArray::eraseIndex(to_activate, idx);
				JArray::eraseIndex(to_deactivate, i);
			}
		}

		int tattoo;
		int evt;

		i = JArray::count(to_deactivate);
		while (i > 0) {
			i -= 1;

			tattoo = JArray::getObj(to_deactivate, i);

			deactivate_tattoo_magic(a_target, tattoo);

			// TODO send mod event
			/*
			evt = ModEvent.Create("SlaveTats-removed")
			if evt
				ModEvent.PushString(evt, JMap.getStr(tattoo, "section"))
				ModEvent.PushString(evt, JMap.getStr(tattoo, "name"))
				ModEvent.PushForm(evt, target)
				ModEvent.Send(evt)
			endif
			*/
		}

		i = JArray::count(to_activate);
		idx = 0;
		while (idx < i) {
			tattoo = JArray::getObj(to_activate, idx);

			activate_tattoo_magic(a_target, tattoo);

			// TODO send mod event
			/*
			evt = ModEvent.Create("SlaveTats-added")
			if evt
				ModEvent.PushString(evt, JMap.getStr(tattoo, "section"))
				ModEvent.PushString(evt, JMap.getStr(tattoo, "name"))
				ModEvent.PushForm(evt, target)
				ModEvent.Send(evt)
			endif
			*/

			idx += 1;
		}

		logger::info("Synchronization complete.");
		// notify("SlaveTats is done with " + target.GetLeveledActorBase().GetName() + ".", silent)
		if (!a_silent) {
			// TODO Enable player controls
		}

		JValue::cleanPool("SlaveTats-synchronize_tattoos");
		return false;
	}


}
