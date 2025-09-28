#include "SlaveTatsNG_Interface.h"

#include "high_level_api.h"
#include "logging.h"
#include "overlays.h"
#include "primary_api.h"
#include "query.h"
#include "tattoo.h"
#include "cache.h"

namespace slavetats
{
	Addresses addresses_instance = {
		Addresses::version,
		slavetats_ng::simple_add_tattoo,
		slavetats_ng::simple_remove_tattoo,
		slavetats_ng::synchronize_tattoos,
		slavetats_ng::log_tattoo,

		// implementation, use at your own risk
		slavetats_ng::tattoo_matches,
		slavetats_ng::_append,
		slavetats_ng::_extend_matching,
		slavetats_ng::query_available_tattoos,
		slavetats_ng::query_applied_tattoos,
		slavetats_ng::query_applied_tattoos_with_attribute,
		slavetats_ng::has_applied_tattoos_with_attribute,
		slavetats_ng::remove_tattoos,
		slavetats_ng::remove_tattoo_from_slot,
		slavetats_ng::get_applied_tattoo_in_slot,
		slavetats_ng::get_applied_tattoos_by_area,
		slavetats_ng::external_slots,
		slavetats_ng::add_tattoo,
		slavetats_ng::add_and_get_tattoo,
		slavetats_ng::get_form,
		slavetats_ng::_log_jcontainer,

		// newly added
		slavetats_ng::compile_cache
	};
}
