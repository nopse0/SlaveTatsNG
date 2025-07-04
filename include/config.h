#pragma once

namespace slavetats_ng
{
	namespace config
	{
		class Config : public clib_util::singleton::ISingleton<Config>
		{
		public:
			std::string skee_dll_name;
			std::string blank_texture_name;
			bool use_vmhook;
		
			Config() :
				blank_texture_name("Actors\\Character\\slavetats\\blank.dds"),
				use_vmhook(false) {}
		};
	}
}
