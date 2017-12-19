#include <benchmark/benchmark.h>

#include "skip_list.hpp"

using namespace skiplist;

static void BM_SkiplistFind(benchmark::State& state) {
    const size_t size = state.range(0);

    SkipList<int, int> skiplist;
    for (size_t i = 0; i < size; ++i)
        skiplist.insert(i, i + 1);

    for (auto _ : state) {
        benchmark::DoNotOptimize(skiplist.find(6));
    }
}
BENCHMARK(BM_SkiplistFind)->Range(1, 1<<20);

BENCHMARK_MAIN();
