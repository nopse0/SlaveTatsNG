#pragma once

namespace slavetats_ng
{
	void _append(int32_t a_dest, int32_t a_val);
	void _cache_tattoo(int32_t a_cache, int32_t a_tattoo);
	int  compile_cache();
	int acquire_cache();
}
