#include "common.hpp"

#if defined(FPM_INT128)


TEST(int128, construct)
{
    fpm::fixed_56_8 x0{};
    fpm::fixed_48_16 x1{};
    fpm::fixed_32_32 x2{};
    fpm::fixed_16_48 x3{};
    fpm::fixed_8_56 x4{};
}

#endif
