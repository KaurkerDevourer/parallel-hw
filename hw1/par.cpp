#include <cstddef>
#include <cstdint>
#include <random>
#include <utility>
#include <vector>
#include <parlay/parallel.h>

static thread_local std::mt19937 par_rng(42);

void par_qsort(std::vector<uint32_t>& v, size_t l, size_t r) {
    size_t sz = r - l;
    if (sz <= 1)
        return;

    size_t pivot_idx = par_rng() % sz + l;
    uint32_t pivot = v[pivot_idx];
    std::swap(v[pivot_idx], v[r - 1]);

    size_t i = l;
    for (size_t j = l; j < r - 1; j++) {
        if (v[j] < pivot) {
            std::swap(v[i], v[j]);
            i++;
        }
    }
    std::swap(v[i], v[r - 1]);

    parlay::par_do(
        [&] { par_qsort(v, l, i); },
        [&] { par_qsort(v, i + 1, r); }
    );
}

void par_qsort(std::vector<uint32_t>& v) {
    par_qsort(v, 0, v.size());
}
