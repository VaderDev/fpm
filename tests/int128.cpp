#include "common.hpp"

#if defined(FPM_INT128)
// Already defined
#elif defined(__SIZEOF_INT128__)
namespace fpm
{
    using int128_t = __int128_t;
#   define FPM_INT128 ::fpm::int128_t
}
#elif defined(_WIN32) && defined(_MSC_VER)
#include "__MSVC_Int128.hpp"
namespace fpm
{
    using int128_t = std::_Signed128;
#   define FPM_INT128 ::fpm::int128_t
}
#else
#warning 128-bit numbers not supported.
#endif

#ifdef FPM_INT128
namespace fpm
{
    static_assert(sizeof(FPM_INT128) > sizeof(std::int64_t));
    static_assert(std::numeric_limits<FPM_INT128>::is_signed);

    using fixed_56_8  = fixed<std::int64_t, FPM_INT128, 8>;
    using fixed_48_16 = fixed<std::int64_t, FPM_INT128, 16>;
    using fixed_32_32 = fixed<std::int64_t, FPM_INT128, 32>;
    using fixed_16_48 = fixed<std::int64_t, FPM_INT128, 48>;
    using fixed_8_56  = fixed<std::int64_t, FPM_INT128, 56>;
}

TEST(int128, construct)
{
    fpm::fixed_32_32 x{};
}

#endif
