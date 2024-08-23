#include "../include/jcontainers_wrapper.h"
#include "../include/constants.h"
#include "../include/query.h"
#include "../include/cache.h"

using namespace slavetats_ng::jcwrapper;
using std::string;

namespace slavetats_ng
{
	void _append(int32_t a_dest, int32_t a_val) {
		JArray::addObj(a_dest, JValue::deepCopy(a_val));
	}

	void _cache_tattoo(int32_t a_cache, int32_t a_tattoo)
	{
		RE::BSFixedString domain_name = JMap::getStr(a_tattoo, "domain", "default");
		RE::BSFixedString area_name = JMap::getStr(a_tattoo, "area");
		RE::BSFixedString section_name = JMap::getStr(a_tattoo, "section");

		int domain = JMap::getObj(a_cache, domain_name);
		if (domain == 0) {
			domain = JValue::addToPool(JMap::object(), "SlaveTats-cache_available_tattoos");
			JMap::setObj(a_cache, domain_name, domain);
		}

		int area = JMap::getObj(domain, area_name);
		if (area == 0) {
			area = JValue::addToPool(JMap::object(), "SlaveTats-cache_available_tattoos");
			JMap::setObj(domain, area_name, area);
		}

		int section = JMap::getObj(domain, section_name);
		if (section == 0) {
			section = JValue::addToPool(JArray::object(), "SlaveTats-cache_available_tattoos");
			JMap::setObj(area, section_name, section);
		}

		JArray::addObj(section, a_tattoo);
	}

	int compile_cache()
	{
		int areas = JValue::addToPool(JMap::object(), "SlaveTats-cache_available_tattoos");

		int directory = JValue::addToPool(JValue::readFromDirectory(string(ROOT()) + string(PREFIX()), ".json"), "SlaveTats-cache_available_tattoos");
		if (directory == 0) {
			JValue::cleanPool("SlaveTats-cache_available_tattoos");
			return 0;
		}

		int registries = JValue::addToPool(JMap::allValues(directory), "SlaveTats-cache_available_tattoos");

		int i = JArray::count(registries);
		while (i > 0) {
			i -= 1;
			int entries = JValue::addToPool(JArray::getObj(registries, i), "SlaveTats-cache_available_tattoos");
			if (is_tattoo(entries))
				_cache_tattoo(areas, entries);
			else if (JValue::isArray(entries)) {
				int j = JArray::count(entries);
				while (j > 0) {
					j -= 1;
					int entry = JValue::addToPool(JArray::getObj(entries, j), "SlaveTats-cache_available_tattoos");
					if (is_tattoo(entry))
						_cache_tattoo(areas, entry);
				}
			}
		}

		JDB::solveObjSetter(".SlaveTats.cache", areas, true);
		JValue::writeToFile(areas, "Data/slavetats_cache.json");

		JValue::cleanPool("SlaveTats-cache_available_tattoos");

		return areas;
	}

	int acquire_cache()
	{
		int cache = JDB::solveObj(".SlaveTats.cache");

		if (cache)
			return cache;

		cache = JValue::readFromFile("Data/slavetats_cache.json");

		if (cache) {
			JDB::solveObjSetter(".SlaveTats.cache", cache, true);
			return cache;
		}

		return compile_cache();
	}

}
