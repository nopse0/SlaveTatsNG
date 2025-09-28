#include "jcontainers_wrapper.h"

#include "ni_node_override_lock.h"

using namespace slavetats_ng::jcwrapper;

namespace slavetats_ng
{
	namespace ni_node_override_lock
	{
		fail_t lock(RE::Actor* a_target)
		{
			if (!a_target) {
				logger::info("a_target is null");
				return true;
			}

			int entry = JFormDB::makeEntry("NiNodeOverrideLock", a_target);
			if (entry == 0) {
				logger::info("JContainers error: could not make NiNodeOverrideLock storage");
				return true;
			}

			// This is a bit stupid, but compareExchangeInt cannot be used to initialize new keys, so we are using fetchAddInt in case the key 
			// NiNodeOverrideLock.lock doesn't exist yet
			int lastValue = JAtomic::fetchAddInt(entry, ".lock", 0, 0, true, -1);
			if (lastValue == -1) {
				logger::info("JContainers error: could not create initial NiNodeOverrideLock.lock key");
				return true;
			} 

			lastValue = JAtomic::compareExchangeInt(entry, ".lock", 1, 0, true, -1);
			
			logger::info("ni_node_override_lock: lastValue = {}", lastValue);
			return lastValue != 0;
		}

		fail_t unlock(RE::Actor* a_target)
		{
			if (!a_target) {
				logger::info("a_target is null");
				return true;
			}

			int entry = JFormDB::makeEntry("NiNodeOverrideLock", a_target);
			if (entry == 0) {
				logger::info("JContainers error: could not make NiNodeOverrideLock storage");
				return true;
			}

			// This is a bit stupid, but compareExchangeInt cannot be used to initialize new keys, so we are using fetchAddInt in case the key
			// NiNodeOverrideLock.lock doesn't exist yet
			int lastValue = JAtomic::fetchAddInt(entry, ".lock", 0, 0, true, -1);
			if (lastValue == -1) {
				logger::info("JContainers error: could not create initial NiNodeOverrideLock.lock key");
				return true;
			}

			lastValue = JAtomic::compareExchangeInt(entry, ".lock", 0, 1, true, -1);
			logger::info("ni_node_override_unlock: lastValue = {}", lastValue);
			return lastValue != 1;
		}
	}
}
