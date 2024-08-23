scriptName SlaveTatsNG

; Undefined
; function notify(string mesg, bool silent = false) global
; function release_cache() global
; function _extend(int dest, int src) global
; bool function refresh_tattoo_magic(Actor target, int template) global
; function mark_actor(Actor target) global

; tests
float function test_float_result() global native
int function test_int_result() global native
bool function test_bool_result() global native
string function test_string_result() global native

; defined in constants.cpp
string function VERSION() global native
string function ROOT() global native
string function PREFIX() global native
int function SLOTS(string area) global native

; defined in high_level_api.cpp
bool function simple_add_tattoo(Actor target, string section, string name, int color = 0, bool last = true, bool silent = false, float alpha = 1.0) global native
bool function simple_remove_tattoo(Actor target, string section, string name, bool last = true, bool silent = false) global native

; defined in query.cpp
bool function tattoo_matches(int template, int tattoo, bool include_configurable = false) global native
bool function is_tattoo(int tattoo) global native
int function find_tattoo(int array, int template) global native
int function find_excluding_tattoo(int applied, int tattoo) global native
int function find_required_tattoo(int applied, int tattoo) global native
bool function has_required_plugin(int tattoo) global native
Form function get_form(int tattoo, string plugin_field, string formid_field, Form default = None) global native


; defined in cache.cpp
function _cache_tattoo(int cache, int tattoo) global native
int function compile_cache() global native
int function acquire_cache() global native
function _append(int dest, int val) global native
function _extend_matching(int dest, int src, int template, int applied = 0, string domain = "default") global native


; defined in primary_api.cpp
bool function query_available_tattoos(int template, int matches, int applied = 0, string domain = "default") global native
bool function query_applied_tattoos(Actor target, int template, int matches, string except_area = "", int except_slot = -1) global native

; defined in tattoos.cpp
bool function query_applied_tattoos_with_attribute(Actor target, string attrib, int matches, string except_area = "", int except_slot = -1) global native
bool function has_applied_tattoos_with_attribute(Actor target, string attrib, string except_area = "", int except_slot = -1) global native
bool function remove_tattoos(Actor target, int template, bool ignore_lock = False, bool silent = False) global native
bool function _remove_tattoos(Actor target, int template, bool ignore_lock = False, bool silent = False) global native
bool function remove_tattoo_from_slot(Actor target, string area, int slot, bool ignore_lock = False, bool silent = False) global native
int function get_applied_tattoo_in_slot(Actor target, string area, int slot) global native
bool function get_applied_tattoos_by_area(Actor target, int on_body, int on_face, int on_hands, int on_feet) global native
bool function external_slots(Actor target, string area, int matches) global native
int function _available_slot(Actor target, string area) global native
bool function add_tattoo(Actor target, int tattoo, int slot = -1, bool ignore_lock = False, bool silent = False) global native
int function add_and_get_tattoo(Actor target, int tattoo, int slot = -1, bool ignore_lock = False, bool silent = False, bool try_upgrade = True) global native
int function _add_and_get_tattoo(Actor target, int tattoo, int slot = -1, bool ignore_lock = False, bool silent = False) global native

; defined in tattoo_magic.cpp
bool function activate_tattoo_magic(Actor target, int tattoo, bool deactivate_first = false) global native
bool function deactivate_tattoo_magic(Actor target, int tattoo) global native
bool function deactivate_all_tattoo_magic(Actor target) global native

; defined in overlays.cpp
bool function upgrade_tattoos(Actor target) global native
bool function clear_overlay(Actor target, bool isFemale, string area, int slot) global native
bool function apply_overlay(Actor target, bool isFemale, string area, int slot, string path, int color, int glow, bool gloss, string bump = "", float alpha = 1.0) global native
bool function synchronize_tattoos(Actor target, bool silent = false) global native

; defined in logging.cpp
function _log_jcontainer(int jc, string indent) global native
function log_tattoo(string msg, int tattoo) global native