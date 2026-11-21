#include <vector>
#include <random>

std::mt19937 rng(42);

void seq_qsort(std::vector<uint32_t>& v, size_t l, size_t r) {
    size_t sz = r - l;
    if (sz <= 1) 
        return;

    size_t pivot_idx = rng() % sz + l;
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
    seq_qsort(v, l, i);
    seq_qsort(v, i + 1, r);
}

void seq_qsort(std::vector<uint32_t>& v) {
    seq_qsort(v, 0, v.size());
}
