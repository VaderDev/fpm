#include <benchmark/benchmark.h>
#include <fpm/fixed.hpp>
#include <cnl/fixed_point.h>

#include <fixmath.h>

#define BENCHMARK_TEMPLATE1_CAPTURE(func, a, b, ...)   \
  BENCHMARK_PRIVATE_DECLARE(func) =                                 \
      (::benchmark::internal::RegisterBenchmarkInternal(            \
          new ::benchmark::internal::FunctionBenchmark(             \
              #func "<" #a "->" #b ">",					\
              [](::benchmark::State& st) { func<a,b>(st, __VA_ARGS__); })))

// Constants for to_float argument.
// Stored as volatile to force the compiler to read them and
// not optimize the entire expression into a constant.
static volatile int16_t s_x = 1543;

template <typename TValue, typename TResult>
static void to_float(benchmark::State& state, TResult (*func)(TValue))
{
    for (auto _ : state)
    {
        TValue x{ static_cast<TValue>(static_cast<int16_t>(s_x)) };
        benchmark::DoNotOptimize(func(x));
    }
}

#define FUNC(TYPE, FLOATING) \
    [](TYPE x) -> FLOATING { return static_cast<FLOATING>(x); }

using CnlFixed16 = cnl::fixed_point<std::int32_t, -16>;

BENCHMARK_TEMPLATE1_CAPTURE(to_float, fpm::fixed_24_8, float, FUNC(fpm::fixed_24_8, float));
BENCHMARK_TEMPLATE1_CAPTURE(to_float, fpm::fixed_24_8, double, FUNC(fpm::fixed_24_8, double));

BENCHMARK_TEMPLATE1_CAPTURE(to_float, fpm::fixed_16_16, float, FUNC(fpm::fixed_16_16, float));
BENCHMARK_TEMPLATE1_CAPTURE(to_float, fpm::fixed_16_16, double, FUNC(fpm::fixed_16_16, double));

BENCHMARK_TEMPLATE1_CAPTURE(to_float, Fix16, float, FUNC(Fix16, float));
BENCHMARK_TEMPLATE1_CAPTURE(to_float, Fix16, double, FUNC(Fix16, double));

BENCHMARK_TEMPLATE1_CAPTURE(to_float, CnlFixed16, float, FUNC(CnlFixed16, float));
BENCHMARK_TEMPLATE1_CAPTURE(to_float, CnlFixed16, double, FUNC(CnlFixed16, double));
