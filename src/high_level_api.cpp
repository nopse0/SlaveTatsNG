#include "../include/jcontainers_wrapper.h"
#include "../include/primary_api.h"
#include "../include/tattoo.h"
#include "../include/overlays.h"
#include "../include/high_level_api.h"

using namespace slavetats_ng::jcwrapper;
using std::string;

namespace slavetats_ng
{
	fail_t simple_add_tattoo(RE::Actor* a_target, RE::BSFixedString a_section, RE::BSFixedString a_name, int a_color, bool a_last, bool a_silent, float a_alpha)
	{
		return complex_add_tattoo(a_target, a_section, a_name, a_color, a_last, a_silent, a_alpha);
	}

	fail_t complex_add_tattoo(RE::Actor* a_target, RE::BSFixedString a_section, RE::BSFixedString a_name, int a_color, bool a_last, bool a_silent,
		float a_alpha, int a_emissive_color, bool a_gloss, RE::BSFixedString a_bump_map, RE::BSFixedString a_glow_map, float a_emissive_mult)
	{
		if (!a_target) {
			logger::info("a_target is null");
			return true;
		}

		// if (a_name == "mzinDirtFaceFX") {
		// 	logger::info("Debugging mzinDirtFaceFX");
		//}

		int a_template = JValue::addToPool(JMap::object(), "SlaveTatsHighLevel");
		int matches = JValue::addToPool(JArray::object(), "SlaveTatsHighLevel");
		int tattoo = 0;

		JMap::setStr(a_template, "section", a_section);
		JMap::setStr(a_template, "name", a_name);

		if (query_available_tattoos(a_template, matches)) {
			JValue::cleanPool("SlaveTatsHighLevel");
			return false;
		}

		tattoo = JValue::addToPool(JArray::getObj(matches, 0), "SlaveTatsHighLevel");
		JMap::setInt(tattoo, "color", a_color);
		JMap::setFlt(tattoo, "invertedAlpha", 1.0f - a_alpha);
		JMap::setInt(tattoo, "glow", a_emissive_color);
		JMap::setInt(tattoo, "gloss", (int)a_gloss);
		if (!a_bump_map.empty())
			JMap::setStr(tattoo, "bump", a_bump_map);
		if (!a_glow_map.empty())
			JMap::setStr(tattoo, "glowMap", a_glow_map);
		JMap::setFlt(tattoo, "emissiveMult", a_emissive_mult);

		JArray::clear(matches);

		if (query_applied_tattoos(a_target, a_template, matches)) {
			JValue::cleanPool("SlaveTatsHighLevel");
			return false;
		}

		if (JArray::count(matches) > 0) {
			JValue::cleanPool("SlaveTatsHighLevel");
			return false;
		}

		if (add_tattoo(a_target, tattoo, -1, false, true)) {
			JValue::cleanPool("SlaveTatsHighLevel");
			return false;
		}

		if (a_last) {
			if (synchronize_tattoos(a_target, a_silent)) {
				JValue::cleanPool("SlaveTatsHighLevel");
				return false;
			}
		}

		JValue::cleanPool("SlaveTatsHighLevel");
		return true;
	}

	fail_t simple_remove_tattoo(RE::Actor* a_target, RE::BSFixedString a_section, RE::BSFixedString a_name,
		bool a_last, bool a_silent)
	{
		if (!a_target) {
			logger::info("a_target is null");
			return true;
		}

		int a_template = JValue::addToPool(JMap::object(), "SlaveTatsHighLevel");
		int matches = JValue::addToPool(JArray::object(), "SlaveTatsHighLevel");
		int tattoo = 0;

		JMap::setStr(a_template, "section", a_section);
		JMap::setStr(a_template, "name", a_name);

		if (query_applied_tattoos(a_target, a_template, matches)) {
			JValue::cleanPool("SlaveTatsHighLevel");
			return false;
		}

		if (JArray::count(matches) == 0) {
			JValue::cleanPool("SlaveTatsHighLevel");
			return false;
		}

		tattoo = JValue::addToPool(JArray::getObj(matches, 0), "SlaveTatsHighLevel");

		if (remove_tattoos(a_target, tattoo, true, true)) {
			JValue::cleanPool("SlaveTatsHighLevel");
			return false;
		}

		if (a_last) {
			if (synchronize_tattoos(a_target, a_silent)) {
				JValue::cleanPool("SlaveTatsHighLevel");
				return false;
			}
		}

		JValue::cleanPool("SlaveTatsHighLevel");
		return true;
	}

}
