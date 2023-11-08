#include <benchmark/benchmark.h>

//Just a placeholder
static void BM_StringCreation(benchmark::State& state)
{
    for (auto _ : state) {
        std::string empty_string;
        benchmark::DoNotOptimize(empty_string);
    }
}
BENCHMARK(BM_StringCreation);

BENCHMARK_MAIN();

//Output example
// 2023-11-08T16:10:32+00:00
// Running /workspaces/inverted-pendulum-controller/build/benchmark/benchmarkPOC
// Run on (12 X 4287.79 MHz CPU s)
// CPU Caches:
//   L1 Data 32 KiB (x6)
//   L1 Instruction 32 KiB (x6)
//   L2 Unified 512 KiB (x6)
//   L3 Unified 16384 KiB (x1)
// Load Average: 0.93, 0.96, 1.00
// ***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
// ------------------------------------------------------------
// Benchmark                  Time             CPU   Iterations
// ------------------------------------------------------------
// BM_StringCreation       1.24 ns         1.24 ns    578543877