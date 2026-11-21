#include <gtest/gtest.h>

#include "seq.cpp"
#include "par.cpp"
#include <algorithm>

TEST(SeqSort, SortThreeElements) {
    std::vector<uint32_t> actual{3, 2, 1};
    const std::vector<uint32_t> expected{1, 2, 3};

    seq_qsort(actual);

    EXPECT_EQ(actual, expected);
}

TEST(SeqSort, SortManyElements) {
    std::vector<uint32_t> input;
    for (uint32_t i = 0; i < 1000; ++i) {
        input.push_back(i);
    }
    std::mt19937 rng(42);
    for (size_t i = 0; i < 10; i++) {
        std::shuffle(input.begin(), input.end(), rng);
        seq_qsort(input);
        for (size_t j = 0; j < 1000; j++) {
            EXPECT_EQ(input[j], j);
        }
    }
}

TEST(SeqSort, StressTest) {
    size_t N = 10000;
    std::vector<uint32_t> input(N);
    std::mt19937 rng(67);
    for (size_t i = 0; i < 100; i++) {
        for (uint32_t j = 0; j < N; j++) {
            input[j] = rng();
        }
        std::vector<uint32_t> input2 = input;
        std::sort(input2.begin(), input2.end());
        seq_qsort(input);
        EXPECT_EQ(input, input2);
    }
}

TEST(ParSort, SortThreeElements) {
    std::vector<uint32_t> actual{3, 2, 1};
    const std::vector<uint32_t> expected{1, 2, 3};

    par_qsort(actual);

    EXPECT_EQ(actual, expected);
}

TEST(ParSort, SortManyElements) {
    std::vector<uint32_t> input;
    for (uint32_t i = 0; i < 1000; ++i) {
        input.push_back(i);
    }
    std::mt19937 rng(42);
    for (size_t i = 0; i < 10; i++) {
        std::shuffle(input.begin(), input.end(), rng);
        par_qsort(input);
        for (size_t j = 0; j < 1000; j++) {
            EXPECT_EQ(input[j], j);
        }
    }
}

TEST(ParSort, StressTest) {
    size_t N = 10000;
    std::vector<uint32_t> input(N);
    std::mt19937 rng(67);
    for (size_t i = 0; i < 100; i++) {
        for (uint32_t j = 0; j < N; j++) {
            input[j] = rng();
        }
        std::vector<uint32_t> input2 = input;
        std::sort(input2.begin(), input2.end());
        par_qsort(input);
        EXPECT_EQ(input, input2);
    }
}