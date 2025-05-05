#pragma once

/*
#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfenv>
#include <cfloat>
#include <cinttypes>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <cuchar>
#include <cwchar>
#include <cwctype>

#include <algorithm>
#include <any>
#include <array>
#include <atomic>
#include <barrier>
#include <bit>
#include <bitset>
#include <charconv>
#include <chrono>
#include <compare>
#include <complex>
#include <concepts>
#include <condition_variable>
#include <deque>
#include <exception>
#include <execution>
#include <filesystem>
#include <format>
#include <forward_list>
#include <fstream>
#include <functional>
#include <future>
#include <initializer_list>
#include <iomanip>
#include <iosfwd>
#include <ios>
#include <iostream>
#include <istream>
#include <iterator>
#include <latch>
#include <limits>
#include <locale>
#include <map>
#include <memory>
#include <memory_resource>
#include <mutex>
#include <new>
#include <numbers>
#include <numeric>
#include <optional>
#include <ostream>
#include <queue>
#include <random>
#include <ranges>
#include <regex>
#include <ratio>
#include <scoped_allocator>
#include <semaphore>
#include <set>
#include <shared_mutex>
#include <source_location>
#include <span>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <string_view>
#include <syncstream>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <typeinfo>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <valarray>
#include <variant>
#include <vector>
#include <version>
*/
#include <latch>

#include <RE/Skyrim.h>
#include <SKSE/SKSE.h>
// #include <REL/Relocation.h>

// #include <ShlObj_core.h>
// #include <Windows.h>
// #include <Psapi.h>
#undef cdecl // Workaround for Clang 14 CMake configure error.

#include <gsl/gsl_util>

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/msvc_sink.h>

#include <CLibUtil/distribution.hpp>
#include <CLibUtil/hash.hpp>
#include <CLibUtil/numeric.hpp>
#include <CLibUtil/rng.hpp>
#include <CLibUtil/string.hpp>
#include <ClibUtil/simpleINI.hpp>
#include <ClibUtil/singleton.hpp>
#include <ClibUtil/editorID.hpp>
#include <fmt/format.h>

template <>
struct fmt::formatter<RE::BSFixedString>
{
	// Presentation format: 'f' - fixed, 'e' - exponential.
	char presentation = 'f';

	// Parses format specifications of the form ['f' | 'e'].
	constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator
	{
		auto it = ctx.begin(), end = ctx.end();
		if (it != end && (*it == 'f'))
			presentation = *it++;

		// Check if reached the end of the range:
		if (it != end && *it != '}')
			throw_format_error("invalid format");

		// Return an iterator past the end of the parsed range:
		return it;
	}
	// Formats the point p using the parsed format specification (presentation)
	// stored in this formatter.
	auto format(const RE::BSFixedString& v, format_context& ctx) const -> format_context::iterator
	{
		// ctx.out() is an output iterator to write to.
		return fmt::format_to(ctx.out(), "{}", v.data());
	}
};

// Compatible declarations with other sample projects.
#define DLLEXPORT __declspec(dllexport)

using namespace std::literals;
using namespace REL::literals;

namespace logger = SKSE::log;

namespace util {
    using SKSE::stl::report_and_fail;
}

namespace slavetats_ng
{
	typedef bool fail_t;
}
