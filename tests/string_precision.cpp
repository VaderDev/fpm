#include "common.hpp"
#include <fpm/ios.hpp>

template<typename T = fpm::fixed_16_16>
void test_fpm()
{
	std::cout << std::setprecision(T::fraction_bits) << std::fixed;

	const T original{0.9};
	std::cout << "original: " << original << " (" << original.raw_value() << ")" << std::endl;

	std::stringstream ss;
	ss << std::setprecision(T::fraction_bits) << std::fixed << original;

	T result;
	ss >> result;
	std::cout << "result: " << result << " (" << result.raw_value() << ")" << std::endl;

	std::cout << "fpm diff: " << (original - result) << " (" << (original - result).raw_value() << ")" << std::endl;
	std::cout << "double diff: " << (static_cast<double>(original) - static_cast<double>(result)) << std::endl;
	EXPECT_EQ(result, original);
}
TEST(string_precision, fixed_8_8)
{
	test_fpm<fpm::fixed_8_8>();
}
TEST(string_precision, fixed_8_8_false)
{
	test_fpm<fpm::fixed<int16_t, int32_t, 8, false>>();
}
TEST(string_precision, fixed_16_16)
{
	test_fpm<fpm::fixed_16_16>();
}
TEST(string_precision, fixed_16_16_false)
{
	test_fpm<fpm::fixed<int32_t, int64_t, 16, false>>();
}
TEST(string_precision, fixed_8_24)
{
	test_fpm<fpm::fixed_8_24>();
}
TEST(string_precision, fixed_8_24_false)
{
	test_fpm<fpm::fixed<int32_t, int64_t, 24, false>>();
}
