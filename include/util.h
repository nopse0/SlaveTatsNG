#pragma once

namespace slavetats_ng
{
	namespace util
	{
		// Copied from powerofthree's PapyrusExtender (https://github.com/powerof3/PapyrusExtenderSSE/blob/master/include/Papyrus/Functions/Strings.h)
		inline RE::BSFixedString IntToString(std::uint32_t a_int, bool a_hex)
		{
			if (a_hex) {
				return std::format("0x{:X}", a_int);
			}
			return std::to_string(a_int);
		}

	}


}
