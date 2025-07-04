#pragma once

namespace slavetats_ng
{
	namespace skee_offsets
	{
		struct offset_table
		{
			std::string comment;
			int         offset_GetNodeOverrideInt;
			int         offset_GetNodeOverrideFloat;
			int         offset_GetNodeOverrideString;
			int         offset_AddNodeOverrideInt;
			int         offset_AddNodeOverrideFloat;
			int         offset_AddNodeOverrideString;
			int         offset_HasNodeOverride;
			int         offset_RemoveNodeOverride;
			int         offset_ApplyNodeOverrides;
			int         offset_AddOverlays;
			int         offset_HasOverlays;
			int         offset_RemoveOverlays;
		};

		using offset_tables_t = std::map<std::string, offset_table>;

		// On I/O errors or Json deserialization errors, this function will throw an exception and terminate Skyrim.
		// Install CrashLoggerSSE, the generated crash log will show what went wrong, e.g. the Json parse error (inclusive line and column number).
		void load_offset_tables(offset_tables_t& a_tables);

	}
}
