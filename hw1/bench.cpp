#include <algorithm>
#include <benchmark/benchmark.h>
#include "seq.cpp"
#include "par.cpp"

static void StdSort(benchmark::State& state) {
    std::vector<uint32_t> v(6);
    for (auto _ : state) {
        v = {6, 5, 4, 3, 2, 1};

        std::sort(v.begin(), v.end());
        benchmark::DoNotOptimize(v.data());
    }
}

static void SeqQsort(benchmark::State& state) {
    std::vector<uint32_t> v(6);
    for (auto _ : state) {
        v = {6, 5, 4, 3, 2, 1};

        seq_qsort(v);
        benchmark::DoNotOptimize(v.data());
    }
}

static void ParQsort(benchmark::State& state) {
    std::vector<uint32_t> v(6);
    for (auto _ : state) {
        v = {6, 5, 4, 3, 2, 1};

        par_qsort(v);
        benchmark::DoNotOptimize(v.data());
    }
}

static std::vector<uint32_t> RandomInput() {
    std::vector<uint32_t> input(100000000);
    std::mt19937 data_rng(67);
    for (auto& x : input) {
        x = data_rng();
    }
    return input;
}

static void StdSortLarge(benchmark::State& state) {
    const auto input = RandomInput();
    std::vector<uint32_t> input2;
    for (auto _ : state) {
        state.PauseTiming();
        input2 = input;
        state.ResumeTiming();

        std::sort(input2.begin(), input2.end());
        benchmark::DoNotOptimize(input2.data());
    }
}

static void SeqQsortLarge(benchmark::State& state) {
    const auto input = RandomInput();
    std::vector<uint32_t> input2;
    for (auto _ : state) {
        state.PauseTiming();
        input2 = input;
        state.ResumeTiming();

        seq_qsort(input2);
        benchmark::DoNotOptimize(input2.data());
    }
}

static void ParQsortLarge(benchmark::State& state) {
    const auto input = RandomInput();
    std::vector<uint32_t> input2;
    for (auto _ : state) {
        state.PauseTiming();
        input2 = input;
        state.ResumeTiming();

        par_qsort(input2);
        benchmark::DoNotOptimize(input2.data());
    }
}

BENCHMARK(StdSort);
BENCHMARK(SeqQsort);
BENCHMARK(ParQsort);
BENCHMARK(StdSortLarge)->Iterations(1)->Unit(benchmark::kMillisecond);
BENCHMARK(SeqQsortLarge)->Iterations(1)->Unit(benchmark::kMillisecond);
BENCHMARK(ParQsortLarge)->Iterations(1)->Unit(benchmark::kMillisecond);
BENCHMARK_MAIN();
