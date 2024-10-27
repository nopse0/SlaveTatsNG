Scriptname MinStaminaRateMult_Effect extends activemagiceffect

Event OnEffectStart(Actor akTarget, Actor akCaster)
	Debug.Trace("MinStaminaRateMult_Effect: Effect started.")
EndEvent

Event OnEffectFinish(Actor akTarget, Actor akCaster)
	Debug.Trace("MinStaminaRateMult_Effect: Effect stopped.")
EndEvent

