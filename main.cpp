#include <vector>

#include "benchmark.h"
#include "bubble_sort.h"
#include "cocktail_sort.h"
#include "combo_sort.h"
#include "cycle_sort.h"
#include "exchange_sort.h"
#include "generate_random_vector.h"
#include "gnome_sorting.h"
#include "insertion_sort.h"
#include "odd_even_sorting.h"
#include "patience_sort.h"
#include "quick_sort.h"
#include "selection_sort.h"
#include "shell_sort.h"
#include "strand_sort.h"
#include "tim_sort.h"

int main() {
    const size_t SIZE10 = 10000;
    std::vector<int> base10k = generate_random_vector(SIZE10);

    const size_t SIZE20 = 20000;
    std::vector<int> base20k = generate_random_vector(SIZE20);

    const size_t SIZE200 = 200000;
    std::vector<int> base200k = generate_random_vector(SIZE200);

    const size_t SIZE500 = 500000;
    std::vector<int> base500k = generate_random_vector(SIZE500);

    benchmark("Bubble Sort 10k elements", bubble_sorting<int>, base10k);
    benchmark("Gnome Sort 10k elements", gnome_sorting<int>, base10k);
    benchmark("Odd-Even Sort 10k elements", odd_even_sorting<int>, base10k);
    benchmark("Exchange Sort 10k elements", exchange_sorting<int>, base10k);
    benchmark("Cycle Sort 10k elements", cycle_sorting<int>, base10k);
    benchmark("Cocktail Sort 10k elements", cocktail_sorting<int>, base10k);
    benchmark("Insertion Sort 10k elements", insertion_sorting<int>, base10k);
    benchmark("Selection Sort 10k elements", selection_sorting<int>, base10k);
    benchmark("Strand Sort 20k elements", strand_sorting<int>, base20k);
    benchmark("Patience Sort 200k elements", patience_sorting<int>, base200k);
    benchmark("Shell Sort 500k elements", shell_sorting<int>, base500k);
    benchmark("Quick Sort 500k elements", quick_sorting<int>, base500k);
    benchmark("Combo Sort 500k elements", combo_sorting<int>, base500k);
    benchmark("Tim Sort 500k elements", tim_sorting<int>, base500k);

    return 0;
}
