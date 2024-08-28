Scriptname NiOverrideCleanScript extends SKI_ConfigBase
Int RemoveAllNiOverridesOID_T
Int AddTattooOID_T
Int RemoveTattooOID_T
String ClearJFormDB_OID_T
String Page_PurgeOverrides = "Purge Overrides"
String Page_SlaveTatsNG = "SlaveTatsNG"
Event OnConfigInit()
    ModName = "NiOverrideClean"
    Pages = new String[2]
    Pages[0] = Page_PurgeOverrides
	Pages[1] = Page_SlaveTatsNG
EndEvent
Event OnPageReset(String page)
    if page == Page_PurgeOverrides
        RemoveAllNiOverridesOID_T = AddTextOption("Remove all NiOverride's", "")
	elseif page == Page_SlaveTatsNG
		AddTattooOID_T = AddTextOption("Add Tattoo", "")
		RemoveTattooOID_T = AddTextOption("Remove Tattoo", "")
		ClearJFormDB_OID_T = AddTextOption("Clear .SlaveTats JFormDB", "")
    endif
EndEvent
Event OnOptionSelect(Int OptionID)
    if CurrentPage == Page_PurgeOverrides 
		if OptionID == RemoveAllNiOverridesOID_T
			RemoveAllNiOverrides()
		endif
	elseif CurrentPage == Page_SlaveTatsNG
		if OptionID == AddTattooOID_T
			AddTattoo()
		elseif OptionID == RemoveTattooOID_T
			RemoveTattoo()
		elseif OptionID == ClearJFormDB_OID_T
			ClearJFormDB()
		endif

    endif
EndEvent
Function ClearJFormDB()
	JDB.setObj(".SlaveTats", 0)
	Debug.MessageBox(".SlaveTats JFormDB cleared, save game now and restart.")
EndFunction
Function AddTattoo()
	SlaveTatsNG.simple_add_tattoo(Game.GetPlayer(), "Bathing In Skyrim", "mzinDirtFaceFX")
    ;Debug.Trace("float: " + SlaveTatsNG.test_float_result())
	;Debug.Trace("int: " + SlaveTatsNG.test_int_result())
	;Debug.Trace("bool: " + SlaveTatsNG.test_bool_result())
	;Debug.Trace("string " + SlaveTatsNG.test_string_result())
	; Debug.MessageBox("float: ")
EndFunction
Function RemoveTattoo()
	SlaveTatsNG.simple_remove_tattoo(Game.GetPlayer(), "Bathing In Skyrim", "mzinDirtFaceFX")
EndFunction
Function RemoveAllNiOverrides()
    NiOverride.RemoveAllOverrides()
	NiOverride.RemoveAllNodeOverrides()
	NiOverride.RemoveAllWeaponBasedOverrides()
	NiOverride.RemoveAllSkinBasedOverrides()
    Debug.MessageBox("NiOverrides purged, save game now and restart.")
EndFunction
