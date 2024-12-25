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
inline static TFixed string_to_fixed(const std::string& value)
{
  TFixed rtn{};
  const std::from_chars_result result = std::from_chars(value.data(), value.data() + value.size(), rtn);
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
#endif
