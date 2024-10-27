#include "mod_events.h"
#include "jcontainers_wrapper.h"
#include "util.h"

using namespace slavetats_ng::jcwrapper;

namespace slavetats_ng
{
	namespace mod_events
	{
		void mod_events::init(uint16_t a_cache_size) {
			if (a_cache_size < 100)		
				_cache_size = 100;
			else
				_cache_size = a_cache_size;
			
			_cache = JDB::solveObjSetter(".SlaveTatsNG.mod_event_cache", JArray::objectWithSize(_cache_size), true);
		}
	
		int32_t mod_events::create() {
			int32_t event = JMap::object();
			JArray::setObj(_cache, _cache_pos, event);
			_cache_pos++;
			if (_cache_pos >= _cache_size)
				_cache_pos = 0;
			return event;
		}

		void mod_events::send(int32_t a_handle, RE::BSFixedString a_event_name)
		{
			// this doesn't work
			//   std::bit_cast<float>(a_handle)
			auto event = SKSE::ModCallbackEvent{ a_event_name, slavetats_ng::util::IntToString(a_handle, false), 0, nullptr };
			auto eventSource = SKSE::GetModCallbackEventSource();
			eventSource->SendEvent(&event);
			logger::info("mod event sent: {}", a_handle);
		}
	}

}
