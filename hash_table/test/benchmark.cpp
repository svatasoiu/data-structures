#include <benchmark/benchmark.h>
#include <cstdlib>
#include <map>
#include <unordered_map>

#include "hash_table.hpp"

using namespace hashtable;

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

static void BM_HashTableInsert(benchmark::State& state) {
    const size_t size = state.range(0);

    for (auto _ : state) {
        HashTable<uint64_t, uint64_t> table;
        for (size_t i = 1; i <= size; ++i)
            table.insert(i, i + 1);
    }
}
BENCHMARK(BM_HashTableInsert)->Range(1, 1<<12);
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

static void BM_HashTableFind(benchmark::State& state) {
    const size_t size = state.range(0);

    HashTable<uint64_t, uint64_t> table;
    for (size_t i = 0; i < size; ++i)
        table.insert(i, i + 1);

    for (auto _ : state) {
        benchmark::DoNotOptimize(table.find(rand() % size));
    }
}
BENCHMARK(BM_HashTableFind)->Range(1, 1<<20);
// ========================================================================

BENCHMARK_MAIN();
