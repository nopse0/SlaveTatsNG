#pragma once
#include <semaphore>

namespace slavetats_ng
{
	namespace threading
	{	
		class System : public clib_util::singleton::ISingleton<System>
		{
		public:
			std::mutex main_thread_id_mutex;
			std::condition_variable main_thread_id_cv;
			bool                    main_thread_id_initialized = false;
			std::thread::id         _main_thread_id;

		public:			
			std::thread::id main_thread_id() {
				std::unique_lock lock(main_thread_id_mutex);
				while(!main_thread_id_initialized)
					main_thread_id_cv.wait(lock);
				return _main_thread_id;
			}
		};

		inline std::string thread_id_to_string(std::thread::id a_id)
		{
			std::ostringstream ss;
			ss << a_id;
			return ss.str();
		}
	}
}
