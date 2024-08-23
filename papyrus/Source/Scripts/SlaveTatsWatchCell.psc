Scriptname SlaveTatsWatchCell extends ActiveMagicEffect

Actor property player auto
ObjectReference property monitor auto
SlaveTatsOnload property st_extra auto

event OnEffectStart(Actor akTarget, Actor akCaster)
;    if st_extra.is_initialized()
;        Debug.Trace("SlaveTatsExtra: Cell changed")
;        st_extra.apply_per_cell_customizations()
;    endif
;
;    Utility.Wait(0.25)
;    monitor.MoveTo(player)
endevent
    