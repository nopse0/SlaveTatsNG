#pragma once

namespace slavetats_ng
{
	namespace utility
	{

		class System : public clib_util::singleton::ISingleton<System>
		{
			SYSTEMTIME _last_save_time;

		public:
			System();

			void set_last_save_time();
			std::vector<std::int32_t> get_last_save_time();
			std::vector<std::int32_t> get_time_since_last_save();

			static std::string md5_hash(const std::string& a_filename);
		};
	}
}
