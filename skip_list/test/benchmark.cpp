#include <benchmark/benchmark.h>
#include <cstdlib>
#include <map>
#include <unordered_map>

#include "skip_list.hpp"

// ========================= INSERTION BENCHMARKS =========================
static void BM_UnorderedMapInsert(benchmark::State& state) {
    srand(time(NULL));
    const size_t size = state.range(0);

    for (auto _ : state) {
        std::unordered_map<uint64_t, uint64_t> m;
        for (size_t i = 1; i <= size; ++i)
            m.insert({i, i + 1});
    }
}
BENCHMARK(BM_UnorderedMapInsert)->Range(1, 1<<12);

static void BM_MapInsert(benchmark::State& state) {
    srand(time(NULL));
    const size_t size = state.range(0);

    for (auto _ : state) {
        std::map<uint64_t, uint64_t> m;
        for (size_t i = 1; i <= size; ++i)
            m.insert({i, i + 1});
    }
}
BENCHMARK(BM_MapInsert)->Range(1, 1<<12);

static void BM_SkiplistInsert(benchmark::State& state) {
    srand(time(NULL));
    const size_t size = state.range(0);

    for (auto _ : state) {
        skiplist::SkipList<uint64_t, uint64_t> skiplist;
        for (size_t i = 1; i <= size; ++i)
            skiplist.insert(i, i + 1);
    }
}
BENCHMARK(BM_SkiplistInsert)->Range(1, 1<<12);
// ========================================================================

// =========================== FIND BENCHMARKS ============================
static void BM_UnorderedMapFind(benchmark::State& state) {
    const size_t size = state.range(0);

    std::unordered_map<uint64_t, uint64_t> m;
    for (size_t i = 0; i < size; ++i)
        m.insert({i, i + 1});

    for (auto _ : state) {
        benchmark::DoNotOptimize(m.find(rand() % size));
    }
}
BENCHMARK(BM_UnorderedMapFind)->Range(1, 1<<20);

static void BM_MapFind(benchmark::State& state) {
    const size_t size = state.range(0);

    std::map<uint64_t, uint64_t> m;
    for (size_t i = 0; i < size; ++i)
        m.insert({i, i + 1});

    for (auto _ : state) {
        benchmark::DoNotOptimize(m.find(rand() % size));
    }
}
BENCHMARK(BM_MapFind)->Range(1, 1<<20);

static void BM_SkiplistFind(benchmark::State& state) {
    srand(time(NULL));
    const size_t size = state.range(0);

    skiplist::SkipList<uint64_t, uint64_t> skiplist;
    for (size_t i = 0; i < size; ++i)
        skiplist.insert(i, i + 1);

    for (auto _ : state) {
        benchmark::DoNotOptimize(skiplist.find(rand() % size));
    }
}
BENCHMARK(BM_SkiplistFind)->Range(1, 1<<20);
// ========================================================================

BENCHMARK_MAIN();
