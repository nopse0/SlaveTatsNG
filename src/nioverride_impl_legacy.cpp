#include "nioverride_impl.h"
#include "nioverride_impl_legacy.h"
#include "config.h"
#include "skee_addresses.h"
#include "utility.h"

namespace slavetats_ng
{
	namespace skee_wrapper
	{
		namespace nioverride_impl
		{

			namespace nioverride_legacy
			{
				RaceMenuAddressTables::RaceMenuAddressTables()
				{
				}

				void RaceMenuAddressTables::init()
				{
					using slavetats_ng::skee_offsets::offset_tables_t, slavetats_ng::skee_offsets::offset_table;
					offset_tables_t offset_tables;
					slavetats_ng::skee_offsets::load_offset_tables(offset_tables);

					auto        config = slavetats_ng::config::Config::GetSingleton();
					std::string dll_name = config->skee_dll_name;
					if (dll_name.empty()) {
						std::string default_dll_name;
						if (GetModuleHandleA("skee64.dll") != NULL)
							default_dll_name = "skee64.dll";
						else if (GetModuleHandleA("skeevr.dll") != NULL)
							default_dll_name = "skee64.dll";
						else {
							logger::info("skee dll name undefined");
							abort();
						}
						dll_name = default_dll_name;
					}

					HMODULE base_module = GetModuleHandleA(dll_name.c_str());
					if (!base_module) {
						logger::info("Module {} is not loaded", dll_name);
						abort();
					}
					char* base_addr = (char*)base_module;

					auto hash = slavetats_ng::utility::System::md5_hash("data/skse/plugins/" + dll_name);
					logger::info("{} md5 hash = {}", dll_name, hash);
					if (hash.empty()) {
						logger::info("Unable to calculate hash for dll {}", dll_name);
						abort();
					}

					auto table_it = offset_tables.find(hash);
					if (table_it == offset_tables.end()) {
						logger::info("Found no skee offset table for dll with hash {}", hash);
						abort();
					}

					const offset_table& table = table_it->second;

					_GetNodeOverrideFloat = (_GetNodeOverrideFloat_t)(base_addr + table.offset_GetNodeOverrideFloat);
					_GetNodeOverrideInt = (_GetNodeOverrideInt_t)(base_addr + table.offset_GetNodeOverrideInt);
					_GetNodeOverrideString = (_GetNodeOverrideString_t)(base_addr + table.offset_GetNodeOverrideString);
					_AddNodeOverrideFloat = (_AddNodeOverrideFloat_t)(base_addr + table.offset_AddNodeOverrideFloat);
					_AddNodeOverrideInt = (_AddNodeOverrideInt_t)(base_addr + table.offset_AddNodeOverrideInt);
					_AddNodeOverrideString = (_AddNodeOverrideString_t)(base_addr + table.offset_AddNodeOverrideString);
					_HasNodeOverride = (_HasNodeOverride_t)(base_addr + table.offset_HasNodeOverride);
					_RemoveNodeOverride = (_RemoveNodeOverride_t)(base_addr + table.offset_RemoveNodeOverride);
					_ApplyNodeOverrides = (_ApplyNodeOverrides_t)(base_addr + table.offset_ApplyNodeOverrides);
					_AddOverlays = (_AddOverlays_t)(base_addr + table.offset_AddOverlays);
					_HasOverlays = (_HasOverlays_t)(base_addr + table.offset_HasOverlays);
					_RemoveOverlays = (_RemoveOverlays_t)(base_addr + table.offset_RemoveOverlays);

					logger::info("skee dll: {}, md5 {}, comment from offset table: {}", dll_name, hash, table.comment);
				}
			}
		}
	}
}
