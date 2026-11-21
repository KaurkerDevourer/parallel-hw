# WARNING

Была использована LLM для написания CMake. CMake гавнище и я не хочу в нем разбираться. Все остальное было сделано руками.

Тесты и бенчмарки были реализованы через гугл тест/бенч. Гонялось это все на M2 Pro.

Для случая когда у нас есть равные элементы, алгоритм будет работать за `N^2`. Это плохо, зато текущий алгоритм получился очень красивый. Исправить это достаточно просто - вместо одного пивота находить все (и отрезать тоже все).

# Тесты

В `test.cpp` описаны тесты, их всего 3, и они очень простые. Каждый дублируется для параллельной и последовательной части. 
1) Проверяем, что для {3, 2, 1} все корректно.
2) Проверяем, что перестановки сортируются
3) Стресс-тест. Рандомно генерим данные, и проверяем идентичность `std::sort`. (там можно строчку `par_qsort/seq_qsort` закоментить и увидить что тесты падают).

Запускать так:
```
cmake --build build --target test -j 4 && PARLAY_NUM_THREADS=4 ./build/test
```

# Бенчмарки

В `bench.cpp` описаны бенчмарки. `std::sort` там для красоты. Первый бенчмарк скорее потестить что все запускается, а вот толстые бенчмарки как и просили.

Чтобы запустить все бенчмарки, делаем так:
```
cmake --build build --target bench -j 4 && PARLAY_NUM_THREADS=4 ./build/bench
```

Тут результат такой:
```
Run on (12 X 24 MHz CPU s)
CPU Caches:
  L1 Data 64 KiB
  L1 Instruction 128 KiB
  L2 Unified 4096 KiB (x12)
Load Average: 2.17, 2.53, 2.80
---------------------------------------------------------------------
Benchmark                           Time             CPU   Iterations
---------------------------------------------------------------------
StdSort                          12.0 ns         12.0 ns     57112553
SeqQsort                         77.0 ns         77.0 ns      8977697
ParQsort                          329 ns          329 ns      2193766
StdSortLarge/iterations:1        2302 ms         2285 ms            1
SeqQsortLarge/iterations:1       7894 ms         7875 ms            1
ParQsortLarge/iterations:1       2342 ms         2338 ms            1
```

Видим, что на мелком тесте ожидаемо параллельный работает сильно дольше, на быстром же втрое быстрее. Тем не менее, всего 1 итерация, чтобы сделать 5 итераций делаем так:

```
cmake --build build --target bench -j 4 && PARLAY_NUM_THREADS=4 ./build/bench --benchmark_filter=Large --benchmark_repetitions=5
```

Тут уже будет 5 итераций.

```
----------------------------------------------------------------------------
Benchmark                                  Time             CPU   Iterations
----------------------------------------------------------------------------
StdSortLarge/iterations:1               2267 ms         2266 ms            1
StdSortLarge/iterations:1               2241 ms         2240 ms            1
StdSortLarge/iterations:1               2228 ms         2227 ms            1
StdSortLarge/iterations:1               2230 ms         2229 ms            1
StdSortLarge/iterations:1               2269 ms         2256 ms            1
StdSortLarge/iterations:1_mean          2247 ms         2244 ms            5
StdSortLarge/iterations:1_median        2241 ms         2240 ms            5
StdSortLarge/iterations:1_stddev        19.9 ms         16.8 ms            5
StdSortLarge/iterations:1_cv            0.88 %          0.75 %             5

SeqQsortLarge/iterations:1              7866 ms         7865 ms            1
SeqQsortLarge/iterations:1              7770 ms         7768 ms            1
SeqQsortLarge/iterations:1              8008 ms         7988 ms            1
SeqQsortLarge/iterations:1              7920 ms         7892 ms            1
SeqQsortLarge/iterations:1              8039 ms         8011 ms            1
SeqQsortLarge/iterations:1_mean         7921 ms         7905 ms            5
SeqQsortLarge/iterations:1_median       7920 ms         7892 ms            5
SeqQsortLarge/iterations:1_stddev        109 ms         98.1 ms            5
SeqQsortLarge/iterations:1_cv           1.37 %          1.24 %             5

ParQsortLarge/iterations:1              2513 ms         2508 ms            1
ParQsortLarge/iterations:1              2481 ms         2464 ms            1
ParQsortLarge/iterations:1              2357 ms         2346 ms            1
ParQsortLarge/iterations:1              2421 ms         2413 ms            1
ParQsortLarge/iterations:1              2445 ms         2441 ms            1
ParQsortLarge/iterations:1_mean         2443 ms         2435 ms            5
ParQsortLarge/iterations:1_median       2445 ms         2441 ms            5
ParQsortLarge/iterations:1_stddev       59.8 ms         60.4 ms            5
ParQsortLarge/iterations:1_cv           2.45 %          2.48 %             5
```

Победа!

# P.S.

Чтобы увидеть, что реально что-то параллелится можно запустить еще с PARLAY_NUM_THREADS=2 и 8. 

Там мы увидим `4531 ms` и `1470 ms` соответственно. В моем случае это +- все, интернет (llm) говорит что "на M2 Pro 12 ядер: 8 производительных и 4 энергоэффективных". Что за энергоэффективные я предпочитаю не знать.