Scriptname minstaminaratemult  extends Quest 

Perk Property MinStaminaRateMult_Perk Auto
Event OnInit()
	Debug.Trace("MinStaminaRateMult: OnInit called")
	Game.GetPlayer().AddPerk(MinStaminaRateMult_Perk)
	Debug.Trace("MinStaminaRateMult: Perk added.")
EndEvent
