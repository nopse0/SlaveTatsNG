Scriptname ModEventTest_PlayerRefScript extends ReferenceAlias  

Event OnPlayerLoadGame()
	Debug.Trace("OnPlayerLoadGame called.")
	Debug.Trace("Registering mod event handlers.")
	RegisterForModEvent("SlaveTatsNG-added", "OnTattooAdded")
	RegisterForModEvent("SlaveTatsNG-removed", "OnTattooRemoved")
	Debug.Trace("Finished mod event handler registration.")
EndEvent

Event OnTattooAdded(String eventName, String stringArg, Float numberArg, Form formArg)
	Debug.Trace("OnTattooAdded started")
	Int eventId = PO3_SKSEFunctions.StringToInt(stringArg)
	String section = JMap.getStr(eventId, "section")
	String name = JMap.getStr(eventId, "name")
	Form aForm = JMap.getForm(eventId, "form")
	Debug.Trace("OnTattoAdded: eventId = " + eventId + ", eventName = " + eventName + ", section = " + section + ", name = " + name + ", form = " + aForm)
EndEvent

Event OnTattooRemoved(String eventName, String stringArg, Float numberArg, Form formArg)
	Debug.Trace("OnTattooRemoved started.")
	Int eventId = PO3_SKSEFunctions.StringToInt(stringArg)
	String section = JMap.getStr(eventId, "section")
	String name = JMap.getStr(eventId, "name")
	Form aForm = JMap.getForm(eventId, "form")
	Debug.Trace("OnTattoRemoved: eventId = " + eventId + ", eventName = " + eventName + ", section = " + section + ", name = " + name + ", form = " + aForm)
EndEvent
