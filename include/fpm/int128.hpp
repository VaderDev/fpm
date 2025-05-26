#pragma once

#include <cstdint>
#include <limits>


// -------------------------------------------------------------------------------------------------

#if defined(FPM_INT128)
// Already defined
#elif defined(__SIZEOF_INT128__)
namespace fpm {
using int128_t = __int128_t;
using uint128_t = __uint128_t;
#define FPM_INT128 true
} // namespace fpm
#elif defined(_MSC_VER)
#include "__msvc_int128.hpp"
namespace fpm {
using int128_t = std::_Signed128;
using uint128_t = std::_Unsigned128;
#define FPM_INT128 true
} // namespace fpm
#else
#warning 128-bit numbers not supported.
#endif

namespace fpm { // ---------------------------------------------------------------------------------

#ifdef FPM_INT128
static_assert(sizeof(int128_t) == 16);
static_assert(sizeof(uint128_t) == 16);
static_assert(std::numeric_limits<int128_t>::is_signed);
static_assert(!std::numeric_limits<uint128_t>::is_signed);
#endif

} // namespace fpm ---------------------------------------------------------------------------------

