#pragma once

namespace slavetats_ng
{
	namespace config
	{
		struct slot_range_t
		{
			int range_min;  // minimum slot number (inclusive, must be >= 0)
			int range_max;  // maximum slot number (inclusive, -NUM_SLOTS < slot_max < NUM_SLOTS (if negative, range_max := range_max + NUM_SLOTS)
		}; 

		enum class area_name
		{
			body,
			face,
			hands,
			feet
		};

		enum class slot_range_name
		{
			middle,
			bottom,
			top
		};


		class Config : public clib_util::singleton::ISingleton<Config>
		{
		public:
			static const RE::BSFixedString middle_slot_range_name;
			static const RE::BSFixedString bottom_slot_range_name;
			static const RE::BSFixedString top_slot_range_name;

			static const RE::BSFixedString body_area_name;
			static const RE::BSFixedString face_area_name;
			static const RE::BSFixedString hands_area_name;
			static const RE::BSFixedString feet_area_name;


			std::string skee_dll_name;
			std::string blank_texture_name;
			bool use_vmhook;
			std::array<std::array<slot_range_t, 3>, 4> area_slot_ranges;
		
			Config() :
				// defaults
				blank_texture_name("Actors\\Character\\slavetats\\blank.dds"),
				use_vmhook(false),
				area_slot_ranges{
					std::array<slot_range_t, 3>{ // body
						slot_range_t{ 0, -1 },  // middle range = all available slots
						slot_range_t{ 1, 0 },   // bottom range = empty
						slot_range_t{ 1, 0 }    // top range = empty
					},
					std::array<slot_range_t, 3>{ // face
						slot_range_t{ 0, -1 },  // middle range = all available slots
						slot_range_t{ 1, 0 },   // bottom range = empty
						slot_range_t{ 1, 0 }    // top range = empty
					},
					std::array<slot_range_t, 3>{ // hands
						slot_range_t{ 0, -1 },  // middle range = all available slots
						slot_range_t{ 1, 0 },   // bottom range = empty
						slot_range_t{ 1, 0 }    // top range = empty
					},
					std::array<slot_range_t, 3>{ // feet
						slot_range_t{ 0, -1 },  // middle range = all available slots
						slot_range_t{ 1, 0 },   // bottom range = empty
						slot_range_t{ 1, 0 }    // top range = empty
					}
				}
			{}

			slot_range_t get_slot_range(const RE::BSFixedString& a_area, const RE::BSFixedString& a_range)
			{
				area_name area;
				if (a_area == body_area_name)
					area = area_name::body;
				else if (a_area == face_area_name)
					area = area_name::face;
				else if (a_area == hands_area_name)
					area = area_name::hands;
				else
					area = area_name::feet;

				auto& slot_ranges = area_slot_ranges[(int)area];  // should be using magic_enum here, instead of casting to int
				if (a_range == top_slot_range_name)
					return slot_ranges[(int)slot_range_name::top];
				else if (a_range == bottom_slot_range_name)
					return slot_ranges[(int)slot_range_name::bottom];
				else
					return slot_ranges[(int)slot_range_name::middle];
			}

		};
	}
}
