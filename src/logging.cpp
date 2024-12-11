#include "../include/jcontainers_wrapper.h"
#include "../include/logging.h"

using namespace slavetats_ng::jcwrapper;
using std::string;

namespace slavetats_ng
{
	namespace
	{
		// Cannot call 'JValue.cleanPool("SlaveTats-_log_jcontainer")' here, because of the recursion
		void _log_jcontainer_internal(int a_obj, RE::BSFixedString a_indent)
		{
			int               max, i, type;
			RE::BSFixedString mkey;

			if (!a_obj)
				return;

			if (JValue::isMap(a_obj)) {
				logger::info("{}{{", a_indent.c_str());
				int keys = JValue::addToPool(JMap::allKeys(a_obj), "SlaveTats-_log_jcontainer");
				max = JArray::count(keys);
				for (i = 0; i < max; i++) {
					mkey = JArray::getStr(keys, i);
					type = JMap::valueType(a_obj, mkey);
					switch (type) {
					case 1:  // None
						logger::info("{}\"{}\": {}", a_indent.c_str(), mkey.c_str(), "None");
						break;
					case 2:  // int
						logger::info("{}\"{}\": {}", a_indent.c_str(), mkey.c_str(), JMap::getInt(a_obj, mkey));
						break;
					case 3:  // float
						logger::info("{}\"{}\": {}", a_indent.c_str(), mkey.c_str(), JMap::getFlt(a_obj, mkey));
						break;
					case 6:  // string
						logger::info("{}\"{}\": {}", a_indent.c_str(), mkey.c_str(), string(JMap::getStr(a_obj, mkey)));
						break;
					case 5:  // nested object
						logger::info("{}\"{}\": {}", a_indent.c_str(), mkey.c_str(), "Nested object");
						_log_jcontainer_internal(JMap::getObj(a_obj, mkey), string(a_indent) + "   ");
						break;
					case 4:  // TESForm*
						// TODO null pointer check, otherwise CTD ?
						logger::info("{}\"{}\": {} {}", a_indent.c_str(), mkey.c_str(), "Form", JMap::getForm(a_obj, mkey)->GetName());
						break;
					default:
						logger::info("{}\"{}\": {}", a_indent.c_str(), mkey.c_str(), "Unknown type");
					}
				}
				logger::info("{}}}", string(a_indent));
			} else if (JValue::isArray(a_obj)) {
				logger::info("{}[", a_indent.c_str());
				max = JArray::count(a_obj);
				for (i = 0; i < max; i++) {
					type = JArray::valueType(a_obj, i);
					switch (type) {
					case 1:  // None
						logger::info("{}{} ", a_indent.c_str(), "None");
						break;
					case 2:  // int
						logger::info("{}{}", a_indent.c_str(), JArray::getInt(a_obj, i));
						break;
					case 3:  // float
						logger::info("{}{}", a_indent.c_str(), JArray::getFlt(a_obj, i));
						break;
					case 6:  // string
						logger::info("{}{}", a_indent.c_str(), string(JArray::getStr(a_obj, i)));
						break;
					case 5:  // nested object
						logger::info("{}{}", a_indent.c_str(), "Nested object");
						_log_jcontainer_internal(JArray::getObj(a_obj, i), string(a_indent) + "   ");
						break;
					case 4:  // TESForm*
						// TODO null pointer check, otherwise CTD ?
						logger::info("{}{} {}", a_indent.c_str(), "Form", JMap::getForm(a_obj, mkey)->GetName());
						break;
					default:
						logger::info("{}{}", a_indent.c_str(), "Unknown type");
					}
				}
				logger::info("{}]", a_indent.c_str());
			} else if (JValue::isFormMap(a_obj)) {
				logger::info("Is a FormMap");
			} else {
				logger::info("Not a Map or Array or FormMap");
			}
		}
	}
	
	void _log_jcontainer(int a_obj, RE::BSFixedString a_indent)
	{
		_log_jcontainer_internal(a_obj, a_indent);
		JValue::cleanPool("SlaveTats-_log_jcontainer");
	}

	void log_tattoo(RE::BSFixedString a_msg, int a_tattoo) 
	{
		logger::info("{} (tattoo = {})", a_msg.c_str(), a_tattoo);
		if (a_tattoo != 0) {
			_log_jcontainer(a_tattoo, "  ");
		} else {
			logger::info("Tattoo is undefined (0)");
		}
	}
}
