#include <benchmark/benchmark.h>
#include <fpm/fixed.hpp>
#include <cnl/fixed_point.h>

#include <fixmath.h>

#define BENCHMARK_TEMPLATE1_CAPTURE(func, test_case_name, a, b, ...)   \
  BENCHMARK_PRIVATE_DECLARE(func) =                                 \
      (::benchmark::internal::RegisterBenchmarkInternal(            \
          new ::benchmark::internal::FunctionBenchmark(             \
              #func "<" #a "," #b ">/" #test_case_name,					\
              [](::benchmark::State& st) { func<a,b>(st, __VA_ARGS__); })))

// Constants for our arithmetic2 operands.
// Stored as volatile to force the compiler to read them and
// not optimize the entire expression into a constant.
static volatile int16_t s_x = 1543;
static volatile int16_t s_y = 2552;

template <typename TValue, typename TValue2>
static void arithmetic2(benchmark::State& state, TValue (*func)(TValue, TValue2))
{
    for (auto _ : state)
    {
        TValue x{ static_cast<TValue>(static_cast<int16_t>(s_x)) };
        TValue2 y{ static_cast<TValue2>(static_cast<int16_t>(s_y)) };
        benchmark::DoNotOptimize(func(x, y));
    }
}

#define FUNC(TYPE, TYPE2, OP) \
    [](TYPE x, TYPE2 y) -> TYPE { return x OP y; }

using CnlFixed16 = cnl::fixed_point<std::int32_t, -16>;

BENCHMARK_TEMPLATE1_CAPTURE(arithmetic2, add, float, int, FUNC(float, int, +));
BENCHMARK_TEMPLATE1_CAPTURE(arithmetic2, sub, float, int, FUNC(float, int, -));
BENCHMARK_TEMPLATE1_CAPTURE(arithmetic2, mul, float, int, FUNC(float, int, *));
BENCHMARK_TEMPLATE1_CAPTURE(arithmetic2, div, float, int, FUNC(float, int, /));

BENCHMARK_TEMPLATE1_CAPTURE(arithmetic2, add, double, int, FUNC(double, int, +));
BENCHMARK_TEMPLATE1_CAPTURE(arithmetic2, sub, double, int, FUNC(double, int, -));
BENCHMARK_TEMPLATE1_CAPTURE(arithmetic2, mul, double, int, FUNC(double, int, *));
BENCHMARK_TEMPLATE1_CAPTURE(arithmetic2, div, double, int, FUNC(double, int, /));

BENCHMARK_TEMPLATE1_CAPTURE(arithmetic2, add, fpm::fixed_16_16, int, FUNC(fpm::fixed_16_16, int, +));
BENCHMARK_TEMPLATE1_CAPTURE(arithmetic2, sub, fpm::fixed_16_16, int, FUNC(fpm::fixed_16_16, int, -));
BENCHMARK_TEMPLATE1_CAPTURE(arithmetic2, mul, fpm::fixed_16_16, int, FUNC(fpm::fixed_16_16, int, *));
BENCHMARK_TEMPLATE1_CAPTURE(arithmetic2, div, fpm::fixed_16_16, int, FUNC(fpm::fixed_16_16, int, /));

BENCHMARK_TEMPLATE1_CAPTURE(arithmetic2, add, Fix16, int, FUNC(Fix16, int, +));
BENCHMARK_TEMPLATE1_CAPTURE(arithmetic2, sub, Fix16, int, FUNC(Fix16, int, -));
BENCHMARK_TEMPLATE1_CAPTURE(arithmetic2, mul, Fix16, int, FUNC(Fix16, int, *));
BENCHMARK_TEMPLATE1_CAPTURE(arithmetic2, div, Fix16, int, FUNC(Fix16, int, /));

BENCHMARK_TEMPLATE1_CAPTURE(arithmetic2, add, CnlFixed16, int, FUNC(CnlFixed16, int, +));
BENCHMARK_TEMPLATE1_CAPTURE(arithmetic2, sub, CnlFixed16, int, FUNC(CnlFixed16, int, -));
BENCHMARK_TEMPLATE1_CAPTURE(arithmetic2, mul, CnlFixed16, int, FUNC(CnlFixed16, int, *));
BENCHMARK_TEMPLATE1_CAPTURE(arithmetic2, div, CnlFixed16, int, FUNC(CnlFixed16, int, /));
