#include "common.hpp"
#include <fpm/ios.hpp>

#if __cplusplus >= 202002L
#   include <version>
#   ifdef __cpp_lib_format
#       include <format>

inline void ExpectFormat(const std::string_view format, const fpm::fixed_16_16 valFixed, const double valDouble, const std::string& expectedValue)
{
    const auto resFixed = std::vformat(format, std::make_format_args(valFixed));
    const auto resDouble = std::vformat(format, std::make_format_args(valDouble));
    EXPECT_EQ(resFixed, expectedValue);
    EXPECT_EQ(resDouble, expectedValue);
    EXPECT_EQ(resFixed, resDouble);
}

TEST(formatting, basic)
{
    EXPECT_EQ(std::format("{}",    fpm::fixed_16_16{0}), std::string("0"));
    EXPECT_EQ(std::format("{0}",   fpm::fixed_16_16{0}), std::string("0"));
    EXPECT_EQ(std::format("{:+}",  fpm::fixed_16_16{0}), std::string("+0"));
    EXPECT_EQ(std::format("{0:+}", fpm::fixed_16_16{0}), std::string("+0"));

    EXPECT_EQ(std::format("{}",    fpm::fixed_16_16{1}), std::string("1"));
    EXPECT_EQ(std::format("{0}",   fpm::fixed_16_16{1}), std::string("1"));
    EXPECT_EQ(std::format("{:+}",  fpm::fixed_16_16{1}), std::string("+1"));
    EXPECT_EQ(std::format("{0:+}", fpm::fixed_16_16{1}), std::string("+1"));

    EXPECT_EQ(std::format("{}",   fpm::fixed_16_16{42}), std::string("42"));
    EXPECT_EQ(std::format("{:+}", fpm::fixed_16_16{42}), std::string("+42"));

    EXPECT_EQ(std::format("{}",   fpm::fixed_16_16{123}), std::string("123"));
    EXPECT_EQ(std::format("{:+}", fpm::fixed_16_16{123}), std::string("+123"));

    EXPECT_EQ(std::format("{}",   fpm::fixed_16_16{123.25}), std::string("123.25"));
    EXPECT_EQ(std::format("{:+}", fpm::fixed_16_16{123.25}), std::string("+123.25"));

    EXPECT_EQ(std::format("{}",   fpm::fixed_16_16{123.125}), std::string("123.125"));
    EXPECT_EQ(std::format("{:+}", fpm::fixed_16_16{123.125}), std::string("+123.125"));

    EXPECT_EQ(std::format("{}",   fpm::fixed_16_16{123.0625}), std::string("123.062"));
    EXPECT_EQ(std::format("{:+}", fpm::fixed_16_16{123.0625}), std::string("+123.062"));
}

TEST(formatting, basic_wchar)
{
    EXPECT_EQ(std::format(L"{}",    fpm::fixed_16_16{0}), std::wstring(L"0"));
    EXPECT_EQ(std::format(L"{0}",   fpm::fixed_16_16{0}), std::wstring(L"0"));
    EXPECT_EQ(std::format(L"{:+}",  fpm::fixed_16_16{0}), std::wstring(L"+0"));
    EXPECT_EQ(std::format(L"{0:+}", fpm::fixed_16_16{0}), std::wstring(L"+0"));

    EXPECT_EQ(std::format(L"{}",    fpm::fixed_16_16{1}), std::wstring(L"1"));
    EXPECT_EQ(std::format(L"{0}",   fpm::fixed_16_16{1}), std::wstring(L"1"));
    EXPECT_EQ(std::format(L"{:+}",  fpm::fixed_16_16{1}), std::wstring(L"+1"));
    EXPECT_EQ(std::format(L"{0:+}", fpm::fixed_16_16{1}), std::wstring(L"+1"));

    EXPECT_EQ(std::format(L"{}",   fpm::fixed_16_16{42}), std::wstring(L"42"));
    EXPECT_EQ(std::format(L"{:+}", fpm::fixed_16_16{42}), std::wstring(L"+42"));

    EXPECT_EQ(std::format(L"{}",   fpm::fixed_16_16{123}), std::wstring(L"123"));
    EXPECT_EQ(std::format(L"{:+}", fpm::fixed_16_16{123}), std::wstring(L"+123"));

    EXPECT_EQ(std::format(L"{}",   fpm::fixed_16_16{123.25}), std::wstring(L"123.25"));
    EXPECT_EQ(std::format(L"{:+}", fpm::fixed_16_16{123.25}), std::wstring(L"+123.25"));

    EXPECT_EQ(std::format(L"{}",   fpm::fixed_16_16{123.125}), std::wstring(L"123.125"));
    EXPECT_EQ(std::format(L"{:+}", fpm::fixed_16_16{123.125}), std::wstring(L"+123.125"));

    EXPECT_EQ(std::format(L"{}",   fpm::fixed_16_16{123.0625}), std::wstring(L"123.062"));
    EXPECT_EQ(std::format(L"{:+}", fpm::fixed_16_16{123.0625}), std::wstring(L"+123.062"));
}

TEST(formatting, width)
{
    EXPECT_EQ(std::format("{:0}", fpm::fixed_16_16{0}), std::string("0"));
    EXPECT_EQ(std::format("{:1}", fpm::fixed_16_16{0}), std::string("0"));
    EXPECT_EQ(std::format("{:2}", fpm::fixed_16_16{0}), std::string(" 0"));
    EXPECT_EQ(std::format("{:3}", fpm::fixed_16_16{0}), std::string("  0"));
    EXPECT_EQ(std::format("{:4}", fpm::fixed_16_16{0}), std::string("   0"));
    EXPECT_EQ(std::format("{:5}", fpm::fixed_16_16{0}), std::string("    0"));
    EXPECT_EQ(std::format("{:6}", fpm::fixed_16_16{0}), std::string("     0"));
}

TEST(formatting, fill_and_align)
{
    ExpectFormat("{:6}", fpm::fixed_16_16{  0},   0.0, "     0");
    ExpectFormat("{:6}", fpm::fixed_16_16{  1},   1.0, "     1");
    ExpectFormat("{:6}", fpm::fixed_16_16{ 42},  42.0, "    42");
    ExpectFormat("{:6}", fpm::fixed_16_16{123}, 123.0, "   123");
    ExpectFormat("{:6}", fpm::fixed_16_16{ -1},  -1.0, "    -1");
    ExpectFormat("{:6}", fpm::fixed_16_16{-42}, -42.0, "   -42");

    ExpectFormat("{:*>6}", fpm::fixed_16_16{  0},   0.0, "*****0");
    ExpectFormat("{:*>6}", fpm::fixed_16_16{  1},   1.0, "*****1");
    ExpectFormat("{:*>6}", fpm::fixed_16_16{ 42},  42.0, "****42");
    ExpectFormat("{:*>6}", fpm::fixed_16_16{123}, 123.0, "***123");
    ExpectFormat("{:*>6}", fpm::fixed_16_16{ -1},  -1.0, "****-1");
    ExpectFormat("{:*>6}", fpm::fixed_16_16{-42}, -42.0, "***-42");

    ExpectFormat("{:x>6}", fpm::fixed_16_16{  0},   0.0, "xxxxx0");
    ExpectFormat("{:x>6}", fpm::fixed_16_16{  1},   1.0, "xxxxx1");
    ExpectFormat("{:x>6}", fpm::fixed_16_16{ 42},  42.0, "xxxx42");
    ExpectFormat("{:x>6}", fpm::fixed_16_16{123}, 123.0, "xxx123");
    ExpectFormat("{:x>6}", fpm::fixed_16_16{ -1},  -1.0, "xxxx-1");
    ExpectFormat("{:x>6}", fpm::fixed_16_16{-42}, -42.0, "xxx-42");

    ExpectFormat("{:+>6}", fpm::fixed_16_16{  0},   0.0, "+++++0");
    ExpectFormat("{:+>6}", fpm::fixed_16_16{  1},   1.0, "+++++1");
    ExpectFormat("{:+>6}", fpm::fixed_16_16{ 42},  42.0, "++++42");
    ExpectFormat("{:+>6}", fpm::fixed_16_16{123}, 123.0, "+++123");
    ExpectFormat("{:+>6}", fpm::fixed_16_16{ -1},  -1.0, "++++-1");
    ExpectFormat("{:+>6}", fpm::fixed_16_16{-42}, -42.0, "+++-42");

    ExpectFormat("{:>>6}", fpm::fixed_16_16{  0},   0.0, ">>>>>0");
    ExpectFormat("{:>>6}", fpm::fixed_16_16{  1},   1.0, ">>>>>1");
    ExpectFormat("{:>>6}", fpm::fixed_16_16{ 42},  42.0, ">>>>42");
    ExpectFormat("{:>>6}", fpm::fixed_16_16{123}, 123.0, ">>>123");
    ExpectFormat("{:>>6}", fpm::fixed_16_16{ -1},  -1.0, ">>>>-1");
    ExpectFormat("{:>>6}", fpm::fixed_16_16{-42}, -42.0, ">>>-42");

    ExpectFormat("{:0>6}", fpm::fixed_16_16{  0},   0.0, "000000");
    ExpectFormat("{:0>6}", fpm::fixed_16_16{  1},   1.0, "000001");
    ExpectFormat("{:0>6}", fpm::fixed_16_16{ 42},  42.0, "000042");
    ExpectFormat("{:0>6}", fpm::fixed_16_16{123}, 123.0, "000123");
    ExpectFormat("{:0>6}", fpm::fixed_16_16{ -1},  -1.0, "0000-1");
    ExpectFormat("{:0>6}", fpm::fixed_16_16{-42}, -42.0, "000-42");

    ExpectFormat("{:<6}", fpm::fixed_16_16{  0},   0.0, "0     ");
    ExpectFormat("{:<6}", fpm::fixed_16_16{  1},   1.0, "1     ");
    ExpectFormat("{:<6}", fpm::fixed_16_16{ 42},  42.0, "42    ");
    ExpectFormat("{:<6}", fpm::fixed_16_16{123}, 123.0, "123   ");
    ExpectFormat("{:<6}", fpm::fixed_16_16{ -1},  -1.0, "-1    ");
    ExpectFormat("{:<6}", fpm::fixed_16_16{-42}, -42.0, "-42   ");

    ExpectFormat("{:^6}", fpm::fixed_16_16{  0},   0.0, "  0   ");
    ExpectFormat("{:^6}", fpm::fixed_16_16{  1},   1.0, "  1   ");
    ExpectFormat("{:^6}", fpm::fixed_16_16{ 42},  42.0, "  42  ");
    ExpectFormat("{:^6}", fpm::fixed_16_16{123}, 123.0, " 123  ");
    ExpectFormat("{:^6}", fpm::fixed_16_16{ -1},  -1.0, "  -1  ");
    ExpectFormat("{:^6}", fpm::fixed_16_16{-42}, -42.0, " -42  ");

    ExpectFormat("{:^2}", fpm::fixed_16_16{123}, 123.0, "123");
    ExpectFormat("{:^2}", fpm::fixed_16_16{12345}, 12345.0, "12345");
    ExpectFormat("{:^4}", fpm::fixed_16_16{12345}, 12345.0, "12345");
}

TEST(formatting, sign)
{
    ExpectFormat("{0:},{0:+},{0:-},{0: }", fpm::fixed_16_16{ 1},  1.0, "1,+1,1, 1");
    ExpectFormat("{0:},{0:+},{0:-},{0: }", fpm::fixed_16_16{-1}, -1.0, "-1,-1,-1,-1");
}

TEST(formatting, zero_padding)
{
    ExpectFormat("{:02}", fpm::fixed_16_16{ 1},  1.0, "01");
    ExpectFormat("{:02}", fpm::fixed_16_16{-1}, -1.0, "-1");

    ExpectFormat("{:03}", fpm::fixed_16_16{ 1},  1.0, "001");
    ExpectFormat("{:03}", fpm::fixed_16_16{-1}, -1.0, "-01");

    ExpectFormat("{:04}", fpm::fixed_16_16{ 1},  1.0, "0001");
    ExpectFormat("{:04}", fpm::fixed_16_16{-1}, -1.0, "-001");

    ExpectFormat("{:06}", fpm::fixed_16_16{ 1},  1.0, "000001");
    ExpectFormat("{:06}", fpm::fixed_16_16{-1}, -1.0, "-00001");

    ExpectFormat("{:<02}", fpm::fixed_16_16{ 1},  1.0, "1 ");
    ExpectFormat("{:<02}", fpm::fixed_16_16{-1}, -1.0, "-1");

    ExpectFormat("{:<06}", fpm::fixed_16_16{ 1},  1.0, "1     ");
    ExpectFormat("{:<06}", fpm::fixed_16_16{-1}, -1.0, "-1    ");
}

#endif
#endif
