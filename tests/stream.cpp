#include "common.hpp"
#include <fpm/ios.hpp>

TEST(stream, wide_char)
{
	std::basic_stringstream<wchar_t> ss(L"-1.25");
	fpm::fixed_16_16 value{};
	ss >> value;

	EXPECT_FALSE(ss.good());
	EXPECT_TRUE(ss.eof());
	EXPECT_EQ(value, fpm::fixed_16_16{-1.25});
}

TEST(stream, unsigned)
{
	using fixed_u_8_8 = fpm::fixed<std::uint16_t, std::uint32_t, 8>;

	using fixed_u_16_16 = fpm::fixed<std::uint32_t, std::uint64_t, 16>;
	using fixed_u_24_8 = fpm::fixed<std::uint32_t, std::uint64_t, 8>;
	using fixed_u_8_24 = fpm::fixed<std::uint32_t, std::uint64_t, 24>;

	std::stringstream ss("-1");

	fixed_u_16_16::base_type valueInt{};
	ss >> valueInt;
	EXPECT_FALSE(ss.good());
	EXPECT_TRUE(ss.eof());

	ss.seekg(0, std::ios::beg);

	fixed_u_16_16 valueFpm{};
	ss >> valueFpm;
	EXPECT_FALSE(ss.good());
	EXPECT_TRUE(ss.eof());

	EXPECT_EQ(valueInt, valueFpm);
}

TEST(stream, hexfloat_no_prefix)
{
	std::stringstream ss("A");

	fpm::fixed_16_16 value{};
	ss >> value;
	EXPECT_FALSE(ss.good());
	EXPECT_FALSE(ss.eof());
	EXPECT_TRUE(ss.fail());

	std::cout << value << std::endl;
	EXPECT_EQ(value, fpm::fixed_16_16{0});
}

TEST(stream, no_integral)
{
	{
		std::stringstream ss(".5");
		double value{};
		ss >> value;

		EXPECT_FALSE(ss.good());
		EXPECT_TRUE(ss.eof());
		EXPECT_EQ(value, 0.5);
	}
	{
		std::stringstream ss(".5");
		fpm::fixed_16_16 value{};
		ss >> value;

		EXPECT_FALSE(ss.good());
		EXPECT_TRUE(ss.eof());
		EXPECT_EQ(value, fpm::fixed_16_16{0.5});
	}
}

TEST(stream, space_prefix)
{
	{
		std::stringstream ss("   -1.5");
		int value{};
		ss >> value;

		EXPECT_TRUE(ss.good());
		EXPECT_FALSE(ss.eof());
		EXPECT_EQ(value, -1);
	}
	{
		std::stringstream ss("   -1.5");
		double value{};
		ss >> value;

		EXPECT_FALSE(ss.good());
		EXPECT_TRUE(ss.eof());
		EXPECT_EQ(value, -1.5);
	}
	{
		std::stringstream ss("   -1.5");
		fpm::fixed_16_16 value{};
		ss >> value;

		EXPECT_FALSE(ss.good());
		EXPECT_TRUE(ss.eof());
		EXPECT_EQ(value, fpm::fixed_16_16{-1.5});
	}
}

TEST(stream, space_inside)
{
	{
		std::stringstream ss("1 . 5");
		int value{};
		ss >> value;

		EXPECT_TRUE(ss.good());
		EXPECT_FALSE(ss.eof());
		EXPECT_EQ(value, 1);
	}
	{
		std::stringstream ss("1 . 5");
		double value{};
		ss >> value;

		EXPECT_TRUE(ss.good());
		EXPECT_FALSE(ss.eof());
		EXPECT_EQ(value, 1);
	}
	{
		std::stringstream ss("1 . 5");
		fpm::fixed_16_16 value{};
		ss >> value;

		EXPECT_TRUE(ss.good());
		EXPECT_FALSE(ss.eof());
		EXPECT_EQ(value, fpm::fixed_16_16{1});
	}
}

TEST(stream, double_negative)
{
	{
		std::stringstream ss("--1.5");
		int value{};
		ss >> value;

		EXPECT_FALSE(ss.good());
		EXPECT_TRUE(ss.fail());
		EXPECT_EQ(value, decltype(value){});
	}
	{
		std::stringstream ss("--1.5");
		double value{};
		ss >> value;

		EXPECT_FALSE(ss.good());
		EXPECT_TRUE(ss.fail());
		EXPECT_EQ(value, decltype(value){});
	}
	{
		std::stringstream ss("--1.5");
		fpm::fixed_16_16 value{};
		ss >> value;

		EXPECT_FALSE(ss.good());
		EXPECT_TRUE(ss.fail());
		EXPECT_EQ(value, decltype(value){});
	}
}