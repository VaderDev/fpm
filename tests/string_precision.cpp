#include "common.hpp"
#include <fpm/ios.hpp>

template<typename T = fpm::fixed_16_16>
void test_fpm(const double initial)
{
	const T original{initial};

	std::stringstream ss;
	ss << std::setprecision(T::fraction_bits) << std::fixed << original;

	T result{};
	ss >> result;

	if(result != original)
	{
		EXPECT_EQ(result, original);
		std::cout << std::setprecision(T::fraction_bits) << std::fixed;
		std::cout << "initial: " << initial << std::endl;
		std::cout << "ss: " << ss.str() << std::endl;
		std::cout << "original: " << original << " (" << original.raw_value() << ")" << std::endl;
		std::cout << "result: " << result << " (" << result.raw_value() << ")" << std::endl;
		std::cout << "fpm diff: " << (original - result) << " (" << (original - result).raw_value() << ")" << std::endl;
		std::cout << "double diff: " << (static_cast<double>(original) - static_cast<double>(result)) << std::endl;
		std::cout << std::endl;
	}
}
TEST(string_precision, range_089_fixed_8_8)
{
	//using F = fpm::fixed_8_8;
	using F = fpm::fixed<int16_t, int32_t, 8>;
	F v0{0.9};
	F v1{0.89};
	while(static_cast<double>(v1) < 0.89)
	{
		v1 = F::from_raw_value(v1.raw_value() + 1);
	}

	std::cout << "v0: " << v0 << std::endl;
	std::cout << "v1: " << v1 << std::endl;
	std::cout << "diff: " << (v0 - v1) << std::endl;

	{
		std::stringstream ss("0.898438");
		F result{};
		ss >> result;
		std::cout  << ss.str()<< " -> " << result << std::endl;
	}
	{
		std::stringstream ss("0.890625");
		F result{};
		ss >> result;
		std::cout << ss.str() << " -> " << result << std::endl;
	}
}
TEST(string_precision, fixed_8_8)
{
	test_fpm<fpm::fixed_8_8>(0.9);
	test_fpm<fpm::fixed_8_8>(1.1);
	test_fpm<fpm::fixed_8_8>(1.3);
}
TEST(string_precision, fixed_8_8_false)
{
	test_fpm<fpm::fixed<int16_t, int32_t, 8, false>>(0.9);
	test_fpm<fpm::fixed<int16_t, int32_t, 8, false>>(1.1);
	test_fpm<fpm::fixed<int16_t, int32_t, 8, false>>(1.3);
}
TEST(string_precision, fixed_16_16)
{
	test_fpm<fpm::fixed_16_16>(0.9);
	test_fpm<fpm::fixed_16_16>(1.1);
	test_fpm<fpm::fixed_16_16>(1.3);
}
TEST(string_precision, fixed_16_16_false)
{
	test_fpm<fpm::fixed<int32_t, int64_t, 16, false>>(0.9);
	test_fpm<fpm::fixed<int32_t, int64_t, 16, false>>(1.1);
	test_fpm<fpm::fixed<int32_t, int64_t, 16, false>>(1.3);
}
TEST(string_precision, fixed_8_24)
{
	test_fpm<fpm::fixed_8_24>(0.9);
	test_fpm<fpm::fixed_8_24>(1.1);
	test_fpm<fpm::fixed_8_24>(1.3);
}
TEST(string_precision, fixed_8_24_false)
{
	test_fpm<fpm::fixed<int32_t, int64_t, 24, false>>(0.9);
	test_fpm<fpm::fixed<int32_t, int64_t, 24, false>>(1.1);
	test_fpm<fpm::fixed<int32_t, int64_t, 24, false>>(1.3);
}
