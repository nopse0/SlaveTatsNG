#pragma once

namespace slavetats_ng
{
	namespace ni_node_override_lock
	{
		fail_t lock(RE::Actor* a_target);
		fail_t unlock(RE::Actor* a_target);
	}
}
