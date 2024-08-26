#include "../include/jcontainers_wrapper.h"
#include "../include/cache.h"
#include "../include/query.h"
#include "../include/skse64_native_papyrus.h"
#include "../include/primary_api.h"
#include "../include/logging.h"


using namespace slavetats_ng::jcwrapper;
using std::string;
namespace StringUtil = skse64_native_papyrus;

namespace slavetats_ng
{
	fail_t query_applied_tattoos(RE::Actor* a_target, int a_template, int a_matches,
		RE::BSFixedString a_except_area, int a_except_slot)
	{
		if (!a_target) {
			logger::info("a_target is null");
			return true;
		}

		int applied = JFormDB::getObj(a_target, ".SlaveTats.applied");
		if (applied == 0)
			return false;

		int i = JArray::count(applied);
		while (i > 0) {
			i -= 1;

			int entry = JArray::getObj(applied, i);
			if (tattoo_matches(a_template, entry) &&
				(JMap::getStr(entry, "area") != a_except_area && JMap::getInt(entry, "slot") != a_except_slot)) {
				JArray::addObj(a_matches, entry);
			}
		}

		return false;
	}

	fail_t query_available_tattoos(int a_template, int a_matches, int a_applied, RE::BSFixedString a_domain)
	{
		int cache = acquire_cache();

		RE::BSFixedString area_name = "";
		RE::BSFixedString section_name = "";
		int    dom = 0;
		int    area = 0;
		int    section = 0;

		if (a_domain == "")
			a_domain = "default";

		dom = JMap::getObj(cache, a_domain);
		// logger::info("dom =");
		// _log_jcontainer(dom, "");

		if (a_template) {
			area_name = JMap::getStr(a_template, "area");
			section_name = JMap::getStr(a_template, "section");
			// _log_jcontainer(a_template, "");

			if (area_name != "" && area_name != "ANY" && StringUtil::Find(area_name, "*") < 0) {
				area = JMap::getObj(dom, area_name);
				if (area == 0)
					return false;

				if (section_name != "" && section_name != "ANY" && StringUtil::Find(section_name, "*") < 0) {
					section = JMap::getObj(area, section_name);
					if (section == 0)
						return false;

					_extend_matching(a_matches, section, a_template, a_applied, a_domain);

					return false;
				} else {
					section_name = JMap::nextKey(area);
					while (section_name != "") {
						section = JMap::getObj(area, section_name);

						_extend_matching(a_matches, section, a_template, a_applied, a_domain);

						section_name = JMap::nextKey(area, section_name);
					}
					return false;
				}
			}
		}

		area_name = JMap::nextKey(dom);
		while (area_name != "") {
			area = JMap::getObj(dom, area_name);

			section_name = JMap::nextKey(area);
			while (section_name != "") {
				section = JMap::getObj(area, section_name);

				_extend_matching(a_matches, section, a_template, a_applied, a_domain);

				section_name = JMap::nextKey(area, section_name);
			}

			// logger::info("dom before nextKey:");
			// _log_jcontainer(dom, "");
			area_name = JMap::nextKey(dom, area_name);
		}
		return false;
	}



}
