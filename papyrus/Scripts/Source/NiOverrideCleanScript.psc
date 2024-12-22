Scriptname NiOverrideCleanScript extends SKI_ConfigBase

Int RemoveAllNiOverridesOID_T

Int RemoveNodeOverrideLockStorageOID_T
Int RemoveSlaveTatsStorageOID_T
Int RemoveSlaveTatsNGStorageOID_T

Int TestLockPlayerOID_T
Int TestUnlockPlayerOID_T
Int TestSynchronizeTattoosPlayerOID_T
Int TestAddTattooOID_T
Int TestRemoveTattooOID_T
Int TestAddExternalOverlay_OID_T

String Page_NiOverride = "NiOverride"
String Page_JContainers = "JContainers"
String Page_Test = "Testing"

Event OnConfigInit()
    ModName = "NiOverrideClean"
    Pages = new String[3]
    Pages[0] = Page_NiOverride
	Pages[1] = Page_JContainers
	Pages[2] = Page_Test
EndEvent

Event OnPageReset(String page)
    if page == Page_NiOverride
        RemoveAllNiOverridesOID_T = AddTextOption("Remove all node overrides", "")
	elseif page == Page_JContainers
		RemoveNodeOverrideLockStorageOID_T = AddTextOption("Remove NiNodeOverrideLock storage", "")
		RemoveSlavetatsStorageOID_T = AddTextOption("Remove SlaveTats storage", "")
		RemoveSlavetatsNGStorageOID_T = AddTextOption("Remove SlaveTatsNG storage", "")
	elseif page == Page_Test
		TestLockPlayerOID_T = AddTextOption("Lock player node overrides", "")
		TestUnlockPlayerOID_T = AddTextOption("Unlock player node overrides", "")
		TestSynchronizeTattoosPlayerOID_T = AddTextOption("SlaveTats synchronize player tattoos", "")
		TestAddTattooOID_T = AddTextOption("SlaveTats add tattoo test", "")
		TestRemoveTattooOID_T = AddTextOption("SlaveTats remove tattoo test", "")
		TestAddExternalOverlay_OID_T = AddTextOption("External overlay test", "")
    endif
EndEvent

Event OnOptionSelect(Int OptionID)
    if CurrentPage == Page_NiOverride 
		if OptionID == RemoveAllNiOverridesOID_T
			RemoveAllNiOverrides()
		endif
	elseif CurrentPage == Page_JContainers
		if OptionID == RemoveNodeOverrideLockStorageOID_T
			RemoveJContainersStorage("NiNodeOverrideLock")
		elseif OptionID == RemoveSlaveTatsStorageOID_T
			RemoveJContainersStorage("SlaveTats")
		elseif OptionID == RemoveSlaveTatsNGStorageOID_T
			RemoveJContainersStorage("SlaveTatsNG")
		endif
	elseif CurrentPage == Page_Test
		if OptionID == TestLockPlayerOID_T
			TestLockPlayer()
		elseif OptionID == TestUnlockPlayerOID_T
			TestUnlockPlayer()
		elseif OptionID == TestSynchronizeTattoosPlayerOID_T
			TestSynchronizeTattoosPlayer()
		elseif OptionID == TestAddTattooOID_T
			TestAddTattoo()
		elseif OptionID == TestRemoveTattooOID_T
			TestRemoveTattoo()
		elseif OptionID == TestAddExternalOverlay_OID_T
			TestAddExternalOverlay()
		endif
    endif
EndEvent

Function RemoveAllNiOverrides()
    NiOverride.RemoveAllOverrides()
	NiOverride.RemoveAllNodeOverrides()
	NiOverride.RemoveAllWeaponBasedOverrides()
	NiOverride.RemoveAllSkinBasedOverrides()
    Debug.MessageBox("All node overrides removed, save game now and restart.")
EndFunction

Function RemoveJContainersStorage(String storageName)
	JDB.setObj("." + storageName, 0)
	Debug.MessageBox("JContainers storage " + storageName + " cleared, save game now and restart.")
EndFunction

Function ApplyOverlay(Actor akTarget, Bool Gender, String Area, String OverlaySlot, String TextureToApply)
	bool lockFailed = NiNodeOverrideLock.lock(Game.GetPlayer(), 10, 0.5)
	if (lockFailed) 
		Debug.MessageBox("Could not get node override lock for player")
		return
	EndIf
	Float Alpha = 1.0
	NiOverride.AddOverlays(akTarget)
	String Node = Area + " [ovl" + OverlaySlot + "]"
	NiOverride.AddNodeOverrideString(akTarget, Gender, Node, 9, 0, TextureToApply, true)
	NiOverride.AddNodeOverrideInt(akTarget, Gender, Node, 7, -1, 0, true);tint color
    NiOverride.AddNodeOverrideInt(akTarget, Gender, Node, 0, -1, 0, true);color
	NiOverride.AddNodeOverrideFloat(akTarget, Gender, Node, 1, -1, 1.0, true)
	NiOverride.AddNodeOverrideFloat(akTarget, Gender, Node, 8, -1, Alpha, true)
	NiOverride.AddNodeOverrideFloat(akTarget, Gender, Node, 2, -1, 0.0, true);gloss
	NiOverride.AddNodeOverrideFloat(akTarget, Gender, Node, 3, -1, 0.0, true);SpecStr
	NiOverride.ApplyNodeOverrides(akTarget)
	Debug.Trace("ApplyOverlay done")

	NiNodeOverrideLock.unlock(Game.GetPlayer())
EndFunction

Function TestLockPlayer()
	bool lockFailed = NiNodeOverrideLock.lock(Game.GetPlayer(), 10, 0.5)
	Debug.MessageBox("Lock player node overrides, error = " + lockFailed)
EndFunction

Function TestUnlockPlayer()
	bool unlockFailed = NiNodeOverrideLock.unlock(Game.GetPlayer())
	Debug.MessageBox("Unlock player node overrides, error = " + unlockFailed)
EndFunction

Function TestSynchronizeTattoosPlayer()
	bool error = SlaveTatsNG.synchronize_tattoos(Game.GetPlayer())
	Debug.MessageBox("SlaveTats synchronize tattoos, error = " + error)
EndFunction

Function TestAddExternalOverlay()
	ApplyOverlay(Game.GetPlayer(), true, "Face", 5, "actors\\character\\norbert\\forehead_slut.dds")
EndFunction

Function TestAddTattoo()
	; bool lockFail = NiNodeOverrideLock.lock(Game.GetPlayer())
	; Debug.Trace("lockFail (1) = " + lockFail)
	; lockFail = NiNodeOverrideLock.lock(Game.GetPlayer())
	; Debug.Trace("lockFail (2) = " + lockFail)

	;bool unlockFail = NiNodeOverrideLock.unlock(Game.GetPlayer())
	;Debug.Trace("unlockFail (1) = " + unlockFail)

	SlaveTatsNG.simple_add_tattoo(Game.GetPlayer(), "Bathing In Skyrim", "mzinDirtFaceFX")

	; bool unlockFail = NiNodeOverrideLock.unlock(Game.GetPlayer())
	; Debug.Trace("unlockFail (1) = " + unlockFail)
	; unlockFail = NiNodeOverrideLock.unlock(Game.GetPlayer())
	; Debug.Trace("unlockFail (2) = " + unlockFail)

    ;Debug.Trace("float: " + SlaveTatsNG.test_float_result())
	;Debug.Trace("int: " + SlaveTatsNG.test_int_result())
	;Debug.Trace("bool: " + SlaveTatsNG.test_bool_result())
	;Debug.Trace("string " + SlaveTatsNG.test_string_result())
	; Debug.MessageBox("float: ")
EndFunction

Function TestRemoveTattoo()
	SlaveTatsNG.simple_remove_tattoo(Game.GetPlayer(), "Bathing In Skyrim", "mzinDirtFaceFX")
EndFunction

