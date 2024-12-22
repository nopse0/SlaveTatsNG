ScriptName NiNodeOverrideLock

bool Function lock(Actor target, int maxTries, float retryDelay) global
    int i = 0
    While i < maxTries
        i += 1
        bool lockFail = tryLock(target)
        If !lockFail
            return false   ; no error
        EndIf
        Utility.Wait(retryDelay)
    EndWhile
    Debug.Trace("[NiNodeOverrideLock] lock failed, maxTries = " + maxTries + ", retryDelay = " + retryDelay)
    return true ; error
EndFunction

bool Function tryLock(Actor target) global

    int entry = JFormDB.makeEntry("NiNodeOverrideLock", target)
    If entry == 0
        Debug.Trace("[NiNodeOverrideLock] tryLock failed, JContainers error: could not make NiNodeOverrideLock storage")
        return true
    EndIf

    ; This is a bit stupid, but compareExchangeInt cannot be used to initialize new keys, so we are using fetchAddInt in case the key NiNodeOverrideLock.lock doesn't exist yet
    int lastValue = JAtomic.fetchAddInt(entry, ".lock", 0, 0, true, -1)
    If lastValue == -1
        Debug.Trace("[NiNodeOverrideLock] tryLock failed, JContainers error: could not create initial NiNodeOverrideLock.lock key")
        return true
    EndIf 

    lastValue = JAtomic.compareExchangeInt(entry, ".lock", 1, 0, false, -1)
    return lastValue != 0

EndFunction

bool Function unlock(Actor target) global

    int entry = JFormDB.makeEntry("NiNodeOverrideLock", target)
    If entry == 0
        Debug.Trace("[NiNodeOverrideLock] unlock failed, JContainers error: could not make NiNodeOverrideLock storage")
        return true
    EndIf

    ; This is a bit stupid, but compareExchangeInt cannot be used to initialize new keys, so we are using fetchAddInt in case the key NiNodeOverrideLock.lock doesn't exist yet
    int lastValue = JAtomic.fetchAddInt(entry, ".lock", 0, 0, true, -1)
    If lastValue == -1
        Debug.Trace("[NiNodeOverrideLock] unock failed, JContainers error: could not create initial NiNodeOverrideLock.lock key")
        return true
    EndIf

    lastValue = JAtomic.compareExchangeInt(entry, ".lock", 0, 1, false, -1)
    return lastValue != 1

EndFunction

