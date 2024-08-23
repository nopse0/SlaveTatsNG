#include "../include/jcontainers_wrapper.h"
#include "../include/primary_api.h"
#include "../include/tattoo.h"
#include "../include/overlays.h"

using namespace slavetats_ng::jcwrapper;
using std::string;

namespace slavetats_ng
{
	fail_t simple_add_tattoo(RE::Actor* a_target, RE::BSFixedString a_section, RE::BSFixedString a_name, int a_color,
		bool a_last, bool a_silent, float a_alpha)
	{
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
