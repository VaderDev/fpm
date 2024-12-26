#include <array>

#include "common.hpp"
#include "fpm/ios.hpp"

#if __cplusplus >= 201703L /* C++17 */
template <std::size_t BufferSize, typename B, typename I, unsigned int F, bool R>
inline static std::string fixed_to_string(const fpm::fixed<B,I,F,R>& value)
{
  std::array<char, BufferSize> buffer{};
  const std::to_chars_result result = std::to_chars(buffer.data(), buffer.data() + buffer.size(), value);
  if(result.ec == std::errc{})
  {
    return std::string(buffer.data(), result.ptr);
  }
  else
  {
    switch(result.ec)
    {
      case std::errc::value_too_large:
        throw std::runtime_error("Value too long");
      default:
        throw std::runtime_error("Other problem");
    }
  }
}

template <typename TFixed = fpm::fixed_16_16>
inline static TFixed string_to_fixed(const std::string& value, std::chars_format fmt = std::chars_format::general)
{
  TFixed rtn{};
  const std::from_chars_result result = std::from_chars(value.data(), value.data() + value.size(), rtn, fmt);
  if(result.ec == std::errc{})
  {
    return rtn;
  }
  else
  {
    switch(result.ec)
    {
      case std::errc::invalid_argument:
        throw std::runtime_error("Invalid argument");
      case std::errc::result_out_of_range:
        throw std::runtime_error("Out of range");
      default:
        throw std::runtime_error("Other problem");
    }
  }
}

TEST(chars, to_chars)
{
  using namespace std::string_literals;
  EXPECT_EQ(fixed_to_string<20>(fpm::fixed_16_16{0}), "0"s);
  EXPECT_EQ(fixed_to_string<20>(fpm::fixed_16_16{1}), "1"s);

  EXPECT_ANY_THROW(fixed_to_string<1>(fpm::fixed_16_16{1.25}));
}

TEST(chars, from_chars)
{
  using namespace std::string_literals;
  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("0"s), fpm::fixed_16_16{0});
  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("1"s), fpm::fixed_16_16{1});
  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("1.5"s), fpm::fixed_16_16{1.5});
  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("1.25"s), fpm::fixed_16_16{1.25});
  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("1.125"s), fpm::fixed_16_16{1.125});
}

TEST(chars, from_chars_scientific)
{
  using namespace std::string_literals;

  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("1e0"s, std::chars_format::scientific), fpm::fixed_16_16{1});
  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("1e1"s, std::chars_format::scientific), fpm::fixed_16_16{10});
  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("1e2"s, std::chars_format::scientific), fpm::fixed_16_16{100});
  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("1e3"s, std::chars_format::scientific), fpm::fixed_16_16{1000});

  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("-1e0"s, std::chars_format::scientific), fpm::fixed_16_16{-1});
  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("-1e1"s, std::chars_format::scientific), fpm::fixed_16_16{-10});
  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("-1e2"s, std::chars_format::scientific), fpm::fixed_16_16{-100});
  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("-1e3"s, std::chars_format::scientific), fpm::fixed_16_16{-1000});
}

TEST(chars, from_chars_hexfloat)
{
  using namespace std::string_literals;

  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("1"s, std::chars_format::hex), fpm::fixed_16_16{0x1});
  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("A"s, std::chars_format::hex), fpm::fixed_16_16{0xA});

  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("-1"s, std::chars_format::hex), fpm::fixed_16_16{-0x1});
  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("-A"s, std::chars_format::hex), fpm::fixed_16_16{-0xA});

  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("1p0"s, std::chars_format::hex), fpm::fixed_16_16{0x1 << 0});
  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("1p1"s, std::chars_format::hex), fpm::fixed_16_16{0x1 << 1});
  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("1p2"s, std::chars_format::hex), fpm::fixed_16_16{0x1 << 2});
  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("1p3"s, std::chars_format::hex), fpm::fixed_16_16{0x1 << 3});
  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("1p4"s, std::chars_format::hex), fpm::fixed_16_16{0x1 << 4});
  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("1p5"s, std::chars_format::hex), fpm::fixed_16_16{0x1 << 5});

  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("-1p0"s, std::chars_format::hex), -fpm::fixed_16_16{0x1 << 0});
  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("-1p1"s, std::chars_format::hex), -fpm::fixed_16_16{0x1 << 1});
  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("-1p2"s, std::chars_format::hex), -fpm::fixed_16_16{0x1 << 2});
  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("-1p3"s, std::chars_format::hex), -fpm::fixed_16_16{0x1 << 3});
  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("-1p4"s, std::chars_format::hex), -fpm::fixed_16_16{0x1 << 4});
  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("-1p5"s, std::chars_format::hex), -fpm::fixed_16_16{0x1 << 5});

  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("1.1"s, std::chars_format::hex), fpm::fixed_16_16{1.0625});
  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("1.5"s, std::chars_format::hex), fpm::fixed_16_16{1.3125});

  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("-1.1"s, std::chars_format::hex), fpm::fixed_16_16{-1.0625});
  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("-1.5"s, std::chars_format::hex), fpm::fixed_16_16{-1.3125});

  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("1.1p1"s, std::chars_format::hex), fpm::fixed_16_16{2.125});
  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("1.1p2"s, std::chars_format::hex), fpm::fixed_16_16{4.25});
  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("1.1p3"s, std::chars_format::hex), fpm::fixed_16_16{8.5});
  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("1.1p4"s, std::chars_format::hex), fpm::fixed_16_16{17});
}

TEST(chars, fail)
{
  using namespace std::string_literals;
  EXPECT_ANY_THROW(string_to_fixed<fpm::fixed_16_16>("1"s, std::chars_format::scientific)); // No exponent
  EXPECT_ANY_THROW(string_to_fixed<fpm::fixed_16_16>("1e0"s, std::chars_format::fixed)); // Does not support exponent
  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("0x1"s, std::chars_format::hex), 0); // "0x1" should result in "0" and "x1" be ignored
  EXPECT_EQ(string_to_fixed<fpm::fixed_16_16>("0x1"s, std::chars_format::general), 0); // "0x1" should result in "0" and "x1" be ignored
  EXPECT_ANY_THROW(string_to_fixed<fpm::fixed_16_16>("+1"s)); // Positive sign not supported, only negative one
}
#endif
