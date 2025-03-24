#include "../include/jcontainers_wrapper.h"
#include "../include/tattoo_magic.h"
#include "query.h"
#include "logging.h"

using namespace slavetats_ng::jcwrapper;

/* Papyrus version

bool function activate_tattoo_magic(Actor target, int tattoo, bool deactivate_first = false) global
    bool magic = false

    string tattoo_event = JMap.getStr(tattoo, "event")
    if tattoo_event != ""
        magic = true
        int evt

        if deactivate_first
            evt = ModEvent.Create(tattoo_event)
            if evt
                ModEvent.PushString(evt, "cleared")
                ModEvent.PushForm(evt, target)
                ModEvent.Send(evt)
                Debug.Trace("SlaveTats: Sent ModEvent " + tattoo_event + "(\"cleared\", " + target.GetLeveledActorBase().GetName() + ")")
            endif
        endif

        evt = ModEvent.Create(tattoo_event)
        if evt
            ModEvent.PushString(evt, "applied")
            ModEvent.PushForm(evt, target)
            ModEvent.Send(evt)
            Debug.Trace("SlaveTats: Sent ModEvent " + tattoo_event + "(\"applied\", " + target.GetLeveledActorBase().GetName() + ")")
        endif
    endif

    Spell spell_ = get_form(tattoo, "spell_plugin", "spell_formid") as Spell
    if spell_ != none
        magic = true

        Debug.Trace("SlaveTats: Tattoo spell = " + spell_.GetName())

        ObjectReference source = get_form(tattoo, "spell_source_plugin", "spell_source_formid", target) as ObjectReference

        if deactivate_first
            Debug.Trace("SlaveTats: Dispelling " + spell_.GetName())
            target.DispelSpell(spell_)
            Utility.Wait(0.25)
        endif

        Debug.Trace("SlaveTats: Casting " + spell_.GetName())
        spell_.Cast(source, target)
    endif

    if magic
        int activated = JFormDB.getObj(target, ".SlaveTats.activated")
        if activated == 0
            activated = JValue.addToPool(JArray.object(), "SlaveTats-activate_tattoo_magic") ; I would love for this to be a JSet, but no such beast exists
            JFormDB.setObj(target, ".SlaveTats.activated", activated)
        endif
        if JArray.findObj(activated, tattoo) < 0
            JArray.addObj(activated, tattoo)
        endif
    endif

    JValue.cleanPool("SlaveTats-activate_tattoo_magic")
    return false
endfunction

*/

namespace slavetats_ng
{	
	static void dispelEffects(RE::MagicItem* a_spell, RE::MagicTarget* a_target)
	{
		if (a_target && a_target->HasMagicEffect(a_spell->effects[0]->baseEffect)) {
			auto activeEffects = a_target->GetActiveEffectList();
			for (const auto& effect : *activeEffects) {
				if (effect->spell == a_spell)
					effect->Dispel(true);
			}
		}
	}

	fail_t activate_tattoo_magic([[maybe_unused]] RE::Actor* a_target, [[maybe_unused]] int a_tattoo, [[maybe_unused]] bool a_deactivate_first)
	{
		if (!a_target)
			return true;

		RE::TESForm* spellForm = get_form(a_tattoo, "spell_plugin", "spell_formid");
		if (!spellForm) {
			// logger::info("activate_tattoo_magic: get_form failed, tattoo dump follows");
			// log_tattoo("activate_tattoo_magic", a_tattoo);
			return true;
		}
		auto spell = spellForm->As<RE::MagicItem>();
		if (!spell) {
			logger::info("activate_tattoo_magic: Form is not a Spell");
			return true;
		}
		auto sourceForm = get_form(a_tattoo, "spell_source_plugin", "spell_source_formid", a_target);
		auto sourceActor = sourceForm->As<RE::Actor>();
		if (!sourceActor) {
			sourceActor = a_target;
		}
		const auto caster = sourceActor->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant);
		if (!caster) {
			logger::info("activate_tattoo_magic: could not get caster actor");
			return true;
		}

		if (a_deactivate_first) {
			auto target = a_target->GetMagicTarget();
			dispelEffects(spell, target);
		}

		// Magnitude override parameter = 0, is this ok ?
		caster->CastSpellImmediate(spell, true, a_target, 1.f, false, 0.f, sourceActor);

		// Update JContainers
		int activated = JFormDB::getObj(a_target, ".SlaveTats.activated");
		if (activated == 0) {
			activated = JValue::addToPool(JArray::object(), "SlaveTats-activate_tattoo_magic"); // I would love for this to be a JSet, but no such beast exists
			JFormDB::setObj(a_target, ".SlaveTats.activated", activated);
		}
		if (JArray::findObj(activated, a_tattoo) < 0)
			JArray::addObj(activated, a_tattoo);      

		return false;
	}

	fail_t deactivate_tattoo_magic([[maybe_unused]] RE::Actor* a_target, [[maybe_unused]] int a_tattoo)
	{
		if (!a_target)
			return true;

		RE::TESForm* spellForm = get_form(a_tattoo, "spell_plugin", "spell_formid");
		if (!spellForm) {
			// logger::info("deactivate_tattoo_magic: get_form failed, tattoo dump follows");
			// log_tattoo("deactivate_tattoo_magic", a_tattoo);
			return true;
		}
		auto spell = spellForm->As<RE::MagicItem>();
		if (!spell) {
			logger::info("deactivate_tattoo_magic: Form is not a Spell");
			return true;
		}	
		auto target = a_target->GetMagicTarget();
		dispelEffects(spell, target);

		// Update JContainers
		int activated = JFormDB::getObj(a_target, ".SlaveTats.activated");
		if (activated != 0) {
			// This will only work if the passed in tattoo is actually the same object.That should be;
			// okay, since presumably it came from query_applied_tattoos.If that's a bad assumption ;
			// this will need to use find_tattoo() instead
			int tattoo_index = JArray::findObj(activated, a_tattoo);
			if (tattoo_index >= 0)
				JArray::eraseIndex(activated, tattoo_index);
		}

		return false;
	}
	
	fail_t deactivate_all_tattoo_magic([[maybe_unused]] RE::Actor* a_target)
	{
		int activated = JFormDB::getObj(a_target, ".SlaveTats.activated");
		if (activated == 0)
			return false;

		int i = JArray::count(activated);
		while (i > 0)
		{
			i -= 1;
			deactivate_tattoo_magic(a_target, JArray::getObj(activated, i));
		}
		return false;
	}

}
