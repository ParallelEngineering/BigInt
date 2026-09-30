#include <benchmark/benchmark.h>

#include "bigint.h"
#include "math_utils.h"

#include <cstddef>
#include <cstdint>

using operations::BigInt;

namespace {

// Erstellt einen BigInt mit ungefähr/exakt der gewünschten Limb-Größe.
// Da ein Limb uint64_t ist:
// 2048 Bit = 32 Limbs.
BigInt makeBigInt(const std::size_t bits, const std::uint64_t pattern) {
    const std::size_t limbCount = (bits + 63) / 64;

    ByteArray limbs(limbCount, pattern);

    return BigInt(std::move(limbs));
}


// ------------------------------------------------------------
// Addition
// ------------------------------------------------------------

static void BM_Add(benchmark::State& state) {
    const auto bits = static_cast<std::size_t>(state.range(0));

    const BigInt a = makeBigInt(bits, 0xAAAAAAAAAAAAAAAAULL);
    const BigInt b = makeBigInt(bits, 0x5555555555555555ULL);

    for (auto _ : state) {
        BigInt result = a + b;

        benchmark::DoNotOptimize(result);
    }

    state.SetComplexityN(static_cast<benchmark::IterationCount>(bits / 64));
}

BENCHMARK(BM_Add)
    ->RangeMultiplier(2)
    ->Range(64, 8192)
    ->Complexity();


// ------------------------------------------------------------
// Subtraction
// ------------------------------------------------------------

static void BM_Subtract(benchmark::State& state) {
    const auto bits = static_cast<std::size_t>(state.range(0));

    // a > b, wichtig bei unsigned BigInt
    const BigInt a = makeBigInt(bits, 0xFFFFFFFFFFFFFFFFULL);
    const BigInt b = makeBigInt(bits, 0x5555555555555555ULL);

    for (auto _ : state) {
        BigInt result = a - b;

        benchmark::DoNotOptimize(result);
    }

    state.SetComplexityN(static_cast<benchmark::IterationCount>(bits / 64));
}

BENCHMARK(BM_Subtract)
    ->RangeMultiplier(2)
    ->Range(64, 8192)
    ->Complexity();


// ------------------------------------------------------------
// Multiplikation
// ------------------------------------------------------------

static void BM_Multiply(benchmark::State& state) {
    const auto bits = static_cast<std::size_t>(state.range(0));

    const BigInt a = makeBigInt(bits, 0xAAAAAAAAAAAAAAAAULL);
    const BigInt b = makeBigInt(bits, 0x5555555555555555ULL);

    for (auto _ : state) {
        BigInt result = a * b;

        benchmark::DoNotOptimize(result);
    }

    state.SetComplexityN(static_cast<benchmark::IterationCount>(bits / 64));
}

BENCHMARK(BM_Multiply)
    ->RangeMultiplier(2)
    ->Range(64, 8192)
    ->Complexity();


// ------------------------------------------------------------
// Division
// ------------------------------------------------------------

static void BM_Divide(benchmark::State& state) {
    const auto bits = static_cast<std::size_t>(state.range(0));

    // a > b
    const BigInt a = makeBigInt(bits, 0xFFFFFFFFFFFFFFFFULL);
    const BigInt b = makeBigInt(bits, 0x5555555555555555ULL);

    for (auto _ : state) {
        BigInt result = a / b;

        benchmark::DoNotOptimize(result);
    }

    state.SetComplexityN(static_cast<benchmark::IterationCount>(bits / 64));
}

BENCHMARK(BM_Divide)
    ->RangeMultiplier(2)
    ->Range(64, 4096)
    ->Complexity();


// ------------------------------------------------------------
// Modulo
// ------------------------------------------------------------

static void BM_Modulo(benchmark::State& state) {
    const auto bits = static_cast<std::size_t>(state.range(0));

    const BigInt a = makeBigInt(bits, 0xFFFFFFFFFFFFFFFFULL);
    const BigInt b = makeBigInt(bits, 0x5555555555555555ULL);

    for (auto _ : state) {
        BigInt result = a % b;

        benchmark::DoNotOptimize(result);
    }

    state.SetComplexityN(static_cast<benchmark::IterationCount>(bits / 64));
}

BENCHMARK(BM_Modulo)
    ->RangeMultiplier(2)
    ->Range(64, 4096)
    ->Complexity();


// ------------------------------------------------------------
// Modular Exponentiation
//
// Verwendet exponent = 65537.
// Das ist für einen ersten Benchmark wesentlich sinnvoller als
// direkt einen mehrere tausend Bit großen Exponenten zu verwenden.
// ------------------------------------------------------------

static void BM_ModPow65537(benchmark::State& state) {
    const auto bits = static_cast<std::size_t>(state.range(0));

    const BigInt base =
        makeBigInt(bits, 0x5555555555555555ULL);

    const BigInt exponent(65537);

    // modulus > base
    const BigInt modulus =
        makeBigInt(bits, 0xFFFFFFFFFFFFFFFFULL);

    for (auto _ : state) {
        BigInt result =
            operations::math::modPow(base, exponent, modulus);

        benchmark::DoNotOptimize(result);
    }
}

BENCHMARK(BM_ModPow65537)
    ->RangeMultiplier(2)
    ->Range(256, 2048);

} // namespace