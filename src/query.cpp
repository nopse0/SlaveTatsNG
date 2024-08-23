#include "../include/jcontainers_wrapper.h"
#include "../include/cache.h"
#include "../include/query.h"
#include "../include/skse64_native_papyrus.h"
#include "../include/logging.h"


using namespace slavetats_ng::jcwrapper;
using std::string;
namespace StringUtil = skse64_native_papyrus;

namespace slavetats_ng
{
	

	bool tattoo_matches(int a_template, int a_tattoo, bool a_include_configurable)
	{
		if (a_template == 0)
			return true;

		if (a_tattoo == 0)
			return false;

		int tkeys = JValue::addToPool(JMap::allKeys(a_template), "SlaveTats-tattoo_matches");
		RE::BSFixedString tkey;

		int ival1, ival2;
		float fval1, fval2;
		RE::BSFixedString sval1, sval2;
		int    wildcard;

		int i = JMap::count(a_template);
		while (i > 0) {
			i -= 1;

			tkey = JArray::getStr(tkeys, i);

			if (a_include_configurable || (tkey != "color" && tkey != "glow" && tkey != "gloss")) {
				sval1 = JMap::getStr(a_template, tkey);

				wildcard = StringUtil::Find(sval1, "*");

				// debug
				// logger::info("a_template:");
				// _log_jcontainer(a_template, "  ");
				// logger::info("a_tattoo:");
				// _log_jcontainer(a_tattoo, "  ");

				if (!(sval1 == "ANY" && JMap::hasKey(a_tattoo, tkey))) {
					ival1 = JMap::getInt(a_template, tkey);
					fval1 = JMap::getFlt(a_template, tkey);

					ival2 = JMap::getInt(a_tattoo, tkey);
					fval2 = JMap::getFlt(a_tattoo, tkey);
					sval2 = JMap::getStr(a_tattoo, tkey);

					if (ival1 != ival2 || fval1 != fval2 || sval1 != sval2) {
						if (wildcard >= 0) {
							int sval1_len = StringUtil::GetLength(sval1);
							int sval2_len = StringUtil::GetLength(sval2);

							if (sval2_len < sval1_len - 1) {
								JValue::cleanPool("SlaveTats-tattoo_matches");
								return false;
							}

							if (wildcard > 0) {
								if (StringUtil::SubString(sval2, 0, wildcard) != StringUtil::SubString(sval1, 0, wildcard)) {
									JValue::cleanPool("SlaveTats-tattoo_matches");
									return false;
								}
							}

							if (wildcard < sval1_len - 1) {
								RE::BSFixedString suffix = StringUtil::SubString(sval2, wildcard + 1);
								if (StringUtil::SubString(sval2, sval2_len - StringUtil::GetLength(suffix)) != suffix) {
									JValue::cleanPool("SlaveTats-tattoo_matches");
									return false;
								}
							}
						} else {
							JValue::cleanPool("SlaveTats-tattoo_matches");
							return false;
						}
					}
				}
			}
		}
		JValue::cleanPool("SlaveTats-tattoo_matches");
		return true;
	}

	int find_tattoo(int array, int a_template)
	{
		int len = JArray::count(array);
		int i = 0;
		while (i < len) {
			if (tattoo_matches(a_template, JArray::getObj(array, i)))
				return i;
			i += 1;
		}
		return -1;
	}

	int find_excluding_tattoo(int a_applied, int a_tattoo) {
		RE::BSFixedString attribute = JMap::getStr(a_tattoo, "excluded_by");
		if (attribute == "")
			return -1;

		int a_template = JValue::addToPool(JMap::object(), "SlaveTats-find_excluding_tattoo");
		JMap::setStr(a_template, attribute, "ANY");
		int result = find_tattoo(a_applied, a_template);

		JValue::cleanPool("SlaveTats-find_excluding_tattoo");

		return result;
	}

	int find_required_tattoo(int a_applied, int a_tattoo)
	{
		RE::BSFixedString attribute = JMap::getStr(a_tattoo, "requires");
		if (attribute == "")
			return 0;

		int a_template = JValue::addToPool(JMap::object(), "SlaveTats-find_required_tattoo");
		JMap::setStr(a_template, attribute, "ANY");
		int result = find_tattoo(a_applied, a_template);

		JValue::cleanPool("SlaveTats-find_required_tattoo");

		return result;
	}

	RE::TESForm* get_form(int a_tattoo, RE::BSFixedString a_plugin_field, RE::BSFixedString a_formid_field, RE::TESForm* a_default)
	{
		int plugins = JMap::getObj(a_tattoo, a_plugin_field);
		int formids = JMap::getObj(a_tattoo, a_formid_field);

		RE::BSFixedString plugin;
		int    formid;
		RE::TESForm* result;

		if (plugins == 0 && formids == 0) {
			plugin = JMap::getStr(a_tattoo, a_plugin_field);
			formid = JMap::getInt(a_tattoo, a_formid_field);
			if (plugin == "" || formid == 0)
				return a_default;
			result = RE::TESDataHandler::GetSingleton()->LookupForm(formid, plugin);
			if (result)
				return result;
			return a_default;
		}

		if (plugins == 0 || formids == 0) {
			return a_default;
		}

		if (!(JValue::isArray(plugins) && JValue::isArray(formids))) {
			return a_default;
		}

		if (JArray::count(plugins) != JArray::count(formids)) {
			return a_default;
		}

		int i = 0;
		int max = JArray::count(plugins);
		while (i < max) {
			plugin = JArray::getStr(plugins, i);
			formid = JArray::getInt(formids, i);
			result = RE::TESDataHandler::GetSingleton()->LookupForm(formid, plugin);
			if (result)
				return result;
			i += 1;
		}
		return a_default;
	}

	bool has_required_plugin(int a_tattoo) 
	{
		if (JMap::getStr(a_tattoo, "requires_plugin") == "" || JMap::getObj(a_tattoo, "requires_plugin") == 0)
			return true;
		return get_form(a_tattoo, "requires_plugin", "requires_formid") != nullptr;
	}

	void _extend_matching(int a_dest, int a_src, int a_template, int a_applied, RE::BSFixedString a_domain)
	{
		int i = 0;
		int max = JArray::count(a_src);
		while (i < max) {
			int tat = JArray::getObj(a_src, i);
			RE::BSFixedString tatDomain = JMap::getStr(tat, "domain", "default");
			if (a_domain == tatDomain) {
				if (a_applied == 0 ||
					(find_excluding_tattoo(a_applied, tat) < 0 && find_required_tattoo(a_applied, tat) >= 0)) {
					if (has_required_plugin(tat)) {
						if (tattoo_matches(a_template, tat))
							_append(a_dest, tat);
					}
				}
			}
			i += 1;
		}
	}


	bool is_tattoo(int tattoo)
	{
		if (tattoo == 0)
			return false;

		if (!JValue::isMap(tattoo))
			return false;

		if (JMap::getStr(tattoo, "name") == "")
			return false;

		if (JMap::getStr(tattoo, "section") == "")
			return false;

		RE::BSFixedString area = JMap::getStr(tattoo, "area");
		if ((area != "Body") && (area != "Face") && (area != "Hands") && (area != "Feet"))
			return false;

		if (JMap::getStr(tattoo, "texture") == "")
			return false;

		return true;
	}

}
