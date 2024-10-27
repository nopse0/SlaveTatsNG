#pragma once

namespace slavetats_ng
{
	namespace mod_events
	{
		class mod_events : public clib_util::singleton::ISingleton<mod_events>
		{
		private:
			uint16_t _cache_size;
			uint16_t _cache_pos;
			int32_t _cache;

		public:
			inline mod_events() :
				_cache_size(0), _cache_pos(0), _cache(0) {}
		public:
			void init(uint16_t a_cache_size);
			int32_t create();
			void send(int32_t a_handle, RE::BSFixedString a_event_name);
		};
	}

}
