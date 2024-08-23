ScriptName SlaveTatsOnLoad extends ReferenceAlias

Quest property extra_quest auto

string FACEGEN = "bUseFaceGenPreprocessedHeads:General"

bool follower_standard = False
bool follower_aft = False
bool follower_eff = False
bool follower_ufo = False

bool in_process = False
Faction current_follower_faction

bool function is_initialized()
    return extra_quest.GetName() == "Initialized"
endfunction

int function _global_extra()
    int db = JDB.root()
    int extra = JMap.getObj(db, "SlaveTatsExtra")
    
    if extra == 0 || !JValue.isMap(extra)
        Debug.Trace("SlaveTatsExtra: Extra wasn't set")
        extra = JValue.retain(JMap.object())
        JMap.setObj(db, "SlaveTatsExtra", extra)
        JValue.release(extra)
        Debug.Trace("SlaveTatsExtra: Extra is now " + extra)
    endif
    
    return extra
endfunction

int function _actor_extra(Actor act)
    int extra = _global_extra()
    int per_actor = JMap.getObj(extra, "per_actor")
    
    if per_actor == 0
        per_actor = JValue.retain(JFormMap.object())
        JMap.setObj(extra, "per_actor", per_actor)
        JValue.release(per_actor)
    endif
    
    int actor_extra = JFormMap.getObj(per_actor, act)
    
    if actor_extra == 0
        actor_extra = JValue.retain(JMap.object())
        JFormMap.setObj(per_actor, act, actor_extra)
        JValue.release(actor_extra)
    endif
    
    return actor_extra
endfunction

function _requires_update_on_load(Actor act)
;    int extra = _global_extra()
;    int update_on_load = JMap.getObj(extra, "update_on_load")
;    
;    if update_on_load == 0
;        Debug.Trace("SlaveTatsExtra: Load wasn't set")
;        update_on_load = JValue.retain(JArray.object())
;        JMap.setObj(extra, "update_on_load", update_on_load)
;        JValue.release(update_on_load) ; JDB has it now
;    endif
;    
;    if JArray.findForm(update_on_load, act) < 0
;        JArray.addForm(update_on_load, act)
;        Debug.Trace("SlaveTatsExtra: Actor registered")
;    endif
;
;    ;Utility.WaitMenuMode(0.5)
endfunction

function _release_follower(Actor act)
;    if follower_standard
;        Debug.Trace("SlaveTatsExtra: Releasing follower (standard)")
;        DialogueFollowerScript dfs = Game.GetFormFromFile(0x750BA, "Skyrim.esm") as DialogueFollowerScript
;        dfs.DismissFollower(-1, 0) ; -1 isn't actually recognized except by AFT, but there's no harm
;    elseif follower_aft
;        Debug.Trace("SlaveTatsExtra: Releasing follower (AFT)")
;        TweakDFScript tdfs = Game.GetFormFromFile(0x750BA, "Skyrim.esm") as TweakDFScript
;        tdfs.DialogueRef = act
;        tdfs.DismissFollower(-1, 0)
;    elseif follower_eff
;        Debug.Trace("SlaveTatsExtra: Releasing follower (EFF)")
;        int evt = ModEvent.Create("XFL_System_Dismiss")
;        if (evt)
;            ModEvent.PushForm(evt, act)
;            ModEvent.PushInt(evt, -1) ; -1 isn't supported, but maybe a future version will. No harm
;            ModEvent.PushInt(evt, 0)
;            ModEvent.Send(evt)
;        endif
;    endif
;    Utility.WaitMenuMode(2)
endfunction

function _acquire_follower(Actor act)
;    if follower_standard
;        Debug.Trace("SlaveTatsExtra: Acquiring follower (standard)")
;        DialogueFollowerScript dfs = Game.GetFormFromFile(0x750BA, "Skyrim.esm") as DialogueFollowerScript
;        dfs.SetFollower(act)    
;    elseif follower_aft
;        Debug.Trace("SlaveTatsExtra: Acquiring follower (AFT)")
;        TweakDFScript tdfs = Game.GetFormFromFile(0x750BA, "Skyrim.esm") as TweakDFScript
;        tdfs.SetFollower(act)
;    elseif follower_eff
;        Debug.Trace("SlaveTatsExtra: Acquiring follower (EFF)")
;        int evt = ModEvent.Create("XFL_System_AddFollower")
;        if (evt)
;            ModEvent.PushForm(evt, act)
;            ModEvent.Send(evt)
;        endif
;    elseif follower_ufo
;        Debug.Notification("UFO is not yet supported, renaming might not work.")
;    else
;        Debug.Notification("This follower mod is not yet supported, renaming might not work.")
;    endif
endfunction

event OnUpdate()
;    Utility.SetINIBool(FACEGEN, true)
endevent

function apply_per_cell_customizations()
;    if in_process
;        return
;    endif
;    
;    in_process = True
;    
;    Debug.Trace("SlaveTatsExtra: Applying per-cell extra customization...")
;    
;    int global_extra = _global_extra()
;    int update_on_load = JMap.getObj(global_extra, "update_on_load")
;    
;    if global_extra == 0
;        Debug.Trace("SlaveTatsExtra: No extra data section. Aborting.")
;        in_process = False
;        return
;    endif
;
;    if update_on_load == 0
;        Debug.Trace("SlaveTatsExtra: No targets. Aborting.")
;        in_process = False
;        return
;    endif
;    
;    Cell player_cell = Game.GetPlayer().GetParentCell()
;    
;    int i = JArray.count(update_on_load)
;    while i > 0
;        i -= 1
;
;        Actor act = JArray.getForm(update_on_load, i) as Actor
;        bool is_follower = act.IsInFaction(current_follower_faction)
;
;        if is_follower || act.GetParentCell() == player_cell
;            bool needs_niupdate = false
;            
;            ActorBase base = act.GetActorBase()
;            ActorBase leveled = act.GetLeveledActorBase()
;            int extra = _actor_extra(act)
;
;            Debug.Trace("SlaveTatsExtra: Updating " + leveled.GetName() + "...")
;
;            ColorForm hair_color = JMap.getForm(extra, "hair_color") as ColorForm
;            if hair_color as bool
;                base.SetHairColor(hair_color)
;                leveled.SetHairColor(hair_color)
;                ;Utility.WaitMenuMode(0.25)
;                needs_niupdate = true
;                Debug.Trace("SlaveTatsExtra: Set hair color to " + hair_color.GetName())
;            endif
;            
;            float weight = JMap.getFlt(extra, "weight", -1)
;            if weight >= 0
;                float neck_delta = (base.GetWeight() / 100) - (weight / 100)
;                base.SetWeight(weight)
;                leveled.SetWeight(weight)
;                act.UpdateWeight(neck_delta)
;                needs_niupdate = true
;                Debug.Trace("SlaveTatsExtra: Set weight to " + weight)
;            endif
;                        
;            if needs_niupdate && !act.IsOnMount()
;                ;TextureSet facetex = leveled.GetFaceTextureSet()
;                Utility.SetINIBool(FACEGEN, false)
;                act.QueueNiNodeUpdate()
;                ;leveled.SetFaceTextureSet(facetex)
;                RegisterForSingleUpdateGameTime(0.025)
;                ;RegisterForSingleUpdate(10)
;            endif
;        endif
;    endwhile
;
;    in_process = False
;    Debug.Trace("SlaveTatsExtra: Per-cell application complete.")
endfunction

function apply_per_load_customizations()
;    Debug.Trace("SlaveTatsExtra: Applying per-load extra customization...")
;    
;    int global_extra = _global_extra()
;    int update_on_load = JMap.getObj(global_extra, "update_on_load")
;    
;    if global_extra == 0
;        Debug.Trace("SlaveTatsExtra: No extra data section. Aborting.")
;        in_process = False
;        return
;    endif
;
;    if update_on_load == 0
;        Debug.Trace("SlaveTatsExtra: No targets. Aborting.")
;        in_process = False
;        return
;    endif
;    
;    int i = JArray.count(update_on_load)
;    while i > 0
;        i -= 1
;
;        Actor act = JArray.getForm(update_on_load, i) as Actor
;        ActorBase base = act.GetActorBase()
;        ActorBase leveled = act.GetLeveledActorBase()
;        int extra = _actor_extra(act)
;
;        Debug.Trace("SlaveTatsExtra: Updating " + leveled.GetName() + "...")
;
;        string name = JMap.getStr(extra, "name")
;        if name != ""
;            bool is_follower = act.IsInFaction(current_follower_faction)
;            if is_follower
;                _release_follower(act)
;            endif
;
;            base.SetName(name)
;            leveled.SetName(name)
;            act.SetName(name)
;            act.SetDisplayName(name)
;            Debug.Trace("SlaveTatsExtra: Set name to " + name)
;
;            if is_follower
;                _acquire_follower(act)
;            endif
;        endif            
;    endwhile
;
;    Debug.Trace("SlaveTatsExtra: Per-load application complete.")
endfunction

function apply_customizations()
;    apply_per_cell_customizations()
;    apply_per_load_customizations()
endfunction

event OnPlayerLoadGame()
    int targets = JDB.solveObj(".SlaveTatsMenu.known_targets")
    int i = JArray.count(targets)
    while i > 0
        i -= 1
        Actor who = JArray.getForm(targets, i) as Actor
        SlaveTats.synchronize_tattoos(who)
    endwhile

;    current_follower_faction = Game.GetFormFromFile(0x5C84E, "Skyrim.esm") as Faction
;    follower_aft = (Game.GetModByName("AmazingFollowerTweaks.esp") != 255)
;    follower_eff = (Game.GetModByName("EFFCore.esm") != 255)
;    follower_ufo = (Game.GetModByName("UFO - Ultimate Follower Overhaul.esp") != 255)
;    follower_standard = !(follower_aft || follower_eff || follower_ufo)
;    Debug.Trace("SlaveTatsExtra: [Follower mods] AFT=" + follower_aft + " EFF=" + follower_eff + " UFO=" + follower_ufo + " standard=" + follower_standard)
;    in_process = false
;    apply_customizations()
    extra_quest.SetName("Initialized")
endevent
