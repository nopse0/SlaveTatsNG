Scriptname ModEventTestQuest_Script extends Quest  

Event OnInit()
	If IsRunning()
		Debug.Trace("ModEventTest: First time initialization.")
	Else
		Debug.Trace("ModEventTest: Initialization when already running.")
	EndIf

EndEvent
