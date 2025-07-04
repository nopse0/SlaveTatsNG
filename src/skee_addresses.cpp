#include "skee_addresses.h"
#include <nlohmann/json.hpp>

namespace slavetats_ng
{
	namespace skee_offsets
	{
		using json = nlohmann::json;
		
		NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(offset_table,\
			comment,\
			offset_GetNodeOverrideInt,\
			offset_GetNodeOverrideFloat,\
			offset_GetNodeOverrideString,\
			offset_AddNodeOverrideInt,\
			offset_AddNodeOverrideFloat,\
			offset_AddNodeOverrideString,\
			offset_HasNodeOverride,\
			offset_RemoveNodeOverride,\
			offset_ApplyNodeOverrides,\
			offset_AddOverlays,\
			offset_HasOverlays,\
			offset_RemoveOverlays\
		)

		void load_offset_tables(offset_tables_t& a_tables)
		{
			// I/O and Json deserialization can throw
			std::ifstream ifs("data/skse/plugins/SlaveTatsNG/skee_addresses.json");
			json          jf = json::parse(ifs);
			a_tables = jf.template get<offset_tables_t>();
		}
	}

}
