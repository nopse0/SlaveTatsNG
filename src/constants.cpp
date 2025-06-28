#include "../include/nioverride_wrapper.h"

namespace slavetats_ng
{
	RE::BSFixedString VERSION()
	{
		return "2.0.0";
	}

	RE::BSFixedString ROOT()
	{
		return "Data\\Textures\\";
	}

	RE::BSFixedString PREFIX()
	{
		return "Actors\\Character\\slavetats\\";
	}

	int SLOTS(RE::BSFixedString a_area)
	{
		if (a_area == "Body")
			return slavetats_ng::skee_wrapper::NiOverride::GetNumBodyOverlays();
		else if (a_area == "Face")
			return slavetats_ng::skee_wrapper::NiOverride::GetNumFaceOverlays();
		else if (a_area == "Hands")
			return slavetats_ng::skee_wrapper::NiOverride::GetNumHandsOverlays();
		else if (a_area == "Feet")
			return slavetats_ng::skee_wrapper::NiOverride::GetNumFeetOverlays();
		else
			return 0;
	}
}
