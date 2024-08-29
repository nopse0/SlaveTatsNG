scriptname SlaveTats hidden
import NiOverride
import NetImmerse

string function VERSION() global
    return SlaveTatsNG.VERSION()
endfunction

string function ROOT() global
    return SlaveTatsNG.ROOT()
endfunction

string function PREFIX() global
    return SlaveTatsNG.PREFIX()
endfunction

int function SLOTS(string area) global
    return SlaveTatsNG.SLOTS(area)
endfunction

bool function simple_add_tattoo(Actor target, string section, string name, int color = 0, bool last = true, bool silent = false, float alpha = 1.0) global
	return SlaveTatsNG.simple_add_tattoo(target, section, name, color, last, silent, alpha)
endfunction

bool function simple_remove_tattoo(Actor target, string section, string name, bool last = true, bool silent = false) global
	return SlaveTatsNG.simple_remove_tattoo(target, section, name, last, silent)
endfunction

bool function tattoo_matches(int template, int tattoo, bool include_configurable = false) global
    return SlaveTatsNG.tattoo_matches(template, tattoo, include_configurable)
endfunction

bool function is_tattoo(int tattoo) global
    return SlaveTatsNG.is_tattoo(tattoo)
endfunction

int function find_tattoo(int array, int template) global
    return SlaveTatsNG.find_tattoo(array, template)
endfunction

int function find_excluding_tattoo(int applied, int tattoo) global
    return SlaveTatsNG.find_excluding_tattoo(applied, tattoo)
endfunction

int function find_required_tattoo(int applied, int tattoo) global
    return SlaveTatsNG.find_required_tattoo(applied, tattoo)
endfunction

bool function has_required_plugin(int tattoo) global
    return SlaveTatsNG.has_required_plugin(tattoo)
endfunction

function _cache_tattoo(int cache, int tattoo) global
    SlaveTatsNG._cache_tattoo(cache, tattoo)
endfunction

int function compile_cache() global
    return SlaveTatsNG.compile_cache()
endfunction

int function acquire_cache() global
    return SlaveTatsNG.acquire_cache()
endfunction

function release_cache() global
    JDB.solveObjSetter(".SlaveTatsNG.cache", 0)
endfunction

function _append(int dest, int val) global
    SlaveTatsNG._append(dest, val)
endfunction

function _extend(int dest, int src) global
    int i = 0
    int max = JArray.count(src)
    while i < max
        _append(dest, JArray.getObj(src, i))
        i = i + 1
    endwhile
endfunction

function _extend_matching(int dest, int src, int template, int applied = 0, string domain = "default") global
    SlaveTatsNG._extend_matching(dest, src, template, applied, domain)
endfunction

bool function query_available_tattoos(int template, int matches, int applied = 0, string domain = "default") global
    return SlaveTatsNG.query_available_tattoos(template, matches, applied, domain)
endfunction

bool function query_applied_tattoos(Actor target, int template, int matches, string except_area = "", int except_slot = -1) global
    return SlaveTatsNG.query_applied_tattoos(target, template, matches, except_area, except_slot)
 endfunction

bool function query_applied_tattoos_with_attribute(Actor target, string attrib, int matches, string except_area = "", int except_slot = -1) global
    return SlaveTatsNG.query_applied_tattoos_with_attribute(target, attrib, matches, except_area, except_slot)
 endfunction

bool function has_applied_tattoos_with_attribute(Actor target, string attrib, string except_area = "", int except_slot = -1) global
    return SlaveTatsNG.has_applied_tattoos_with_attribute(target, attrib, except_area, except_slot)
endfunction

function notify(string mesg, bool silent = false) global
    if silent
        Debug.Trace("SlaveTats: (Silenced) " + mesg)
    else
        Debug.Notification(mesg)
    endif
endfunction

bool function remove_tattoos(Actor target, int template, bool ignore_lock = False, bool silent = False) global
    return SlaveTatsNG.remove_tattoos(target, template, ignore_lock, silent)
 endfunction

bool function _remove_tattoos(Actor target, int template, bool ignore_lock = False, bool silent = False) global
    return SlaveTatsNG._remove_tattoos(target, template, ignore_lock, silent)
endfunction

bool function remove_tattoo_from_slot(Actor target, string area, int slot, bool ignore_lock = False, bool silent = False) global
    return SlaveTatsNG.remove_tattoo_from_slot(target, area, slot, ignore_lock, silent)
endfunction

int function get_applied_tattoo_in_slot(Actor target, string area, int slot) global
    return SlaveTatsNG.get_applied_tattoo_in_slot(target, area, slot)
endfunction

bool function get_applied_tattoos_by_area(Actor target, int on_body, int on_face, int on_hands, int on_feet) global
    return SlaveTatsNG.get_applied_tattoos_by_area(target, on_body, on_face, on_hands, on_feet)
endfunction

bool function external_slots(Actor target, string area, int matches) global
    return SlaveTatsNG.external_slots(target, area, matches)
endfunction

int function _available_slot(Actor target, string area) global
    return SlaveTatsNG._available_slot(target, area)
endfunction

bool function add_tattoo(Actor target, int tattoo, int slot = -1, bool ignore_lock = False, bool silent = False) global
    return SlaveTatsNG.add_tattoo(target, tattoo, slot, ignore_lock, silent)
endfunction

int function add_and_get_tattoo(Actor target, int tattoo, int slot = -1, bool ignore_lock = False, bool silent = False, bool try_upgrade = True) global
    return SlaveTatsNG.add_and_get_tattoo(target, tattoo, slot, ignore_lock, silent, try_upgrade)
endfunction

int function _add_and_get_tattoo(Actor target, int tattoo, int slot = -1, bool ignore_lock = False, bool silent = False) global
    return SlaveTatsNG._add_and_get_tattoo(target, tattoo, slot, ignore_lock, silent)
endfunction

Form function get_form(int tattoo, string plugin_field, string formid_field, Form default = None) global
    return SlaveTatsNG.get_form(tattoo, plugin_field, formid_field, default)
endfunction

bool function activate_tattoo_magic(Actor target, int tattoo, bool deactivate_first = false) global
    return SlaveTatsNG.activate_tattoo_magic(target, tattoo, deactivate_first)
endfunction

bool function deactivate_tattoo_magic(Actor target, int tattoo) global
    return SlaveTatsNG.deactivate_tattoo_magic(target, tattoo)
endfunction

; Deactivates the magic from all applied tattoos.
bool function deactivate_all_tattoo_magic(Actor target) global
    return SlaveTatsNG.deactivate_all_tattoo_magic(target)
endfunction

bool function refresh_tattoo_magic(Actor target, int template) global
    int matches = JValue.addToPool(JArray.object(), "SlaveTats-refresh_tattoo_magic")
    if query_applied_tattoos(target, template, matches)
        JValue.cleanPool("SlaveTats-refresh_tattoo_magic")
        return true
    endif

    int i = JArray.count(matches)
    while i > 0
        i -= 1

        activate_tattoo_magic(target, JArray.getObj(matches, i), true)
    endwhile

    JValue.cleanPool("SlaveTats-refresh_tattoo_magic")

    return false
endfunction

bool function upgrade_tattoos(Actor target) global
    return SlaveTatsNG.upgrade_tattoos(target)
endfunction

bool function clear_overlay(Actor target, bool isFemale, string area, int slot) global
    return SlaveTatsNG.clear_overlay(target, isFemale, area, slot)
endfunction

bool function apply_overlay(Actor target, bool isFemale, string area, int slot, string path, int color, int glow, bool gloss, string bump = "", float alpha = 1.0) global
    return SlaveTatsNG.apply_overlay(target, isFemale, area, slot, path, color, glow, gloss, bump, alpha)
endfunction

function mark_actor(Actor target) global
    JFormDB.setInt(target, ".SlaveTats.updated", 1)
endfunction

bool function synchronize_tattoos(Actor target, bool silent = false) global
    return SlaveTatsNG.synchronize_tattoos(target, silent)
endfunction

function _log_jcontainer(int jc, string indent) global
    SlaveTatsNG._log_jcontainer(jc, indent)
endfunction

; Dumps a tattoo to the log, with as much detail as is feasible
function log_tattoo(string msg, int tattoo) global
    SlaveTatsNG.log_tattoo(msg, tattoo)
endfunction
