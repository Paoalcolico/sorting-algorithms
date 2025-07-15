#include <algorithms/block_sort.h>
#include <algorithms/bubble_sort.h>
#include <algorithms/cocktail_sort.h>
#include <algorithms/combo_sort.h>
#include <algorithms/cycle_sort.h>
#include <algorithms/exchange_sort.h>
#include <algorithms/gnome_sorting.h>
#include <algorithms/grail_sort.h>
#include <algorithms/insertion_sort.h>
#include <algorithms/odd_even_sort.h>
#include <algorithms/patience_sort.h>
#include <algorithms/pdq_sort.h>
#include <algorithms/quick_sort.h>
#include <algorithms/radix_sort.h>
#include <algorithms/selection_sort.h>
#include <algorithms/shell_sort.h>
#include <algorithms/smooth_sort.h>
#include <algorithms/strand_sort.h>
#include <algorithms/tim_sort.h>

#include <algorithm>
#include <vector>

#include "benchmark.h"
#include "generate_random_vector.h"

int main() {
    std::vector<int> base100 = generate_random_vector(100);

    const size_t SIZE10 = 10000;
    std::vector<int> base10k = generate_random_vector(SIZE10);

    const size_t SIZE20 = 20000;
    std::vector<int> base20k = generate_random_vector(SIZE20);

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
    benchmark("Strand Sort 10k elements", strand_sorting<int>, base10k);
    benchmark("Patience Sort 10k elements", patience_sorting<int>, base10k);
    benchmark("Shell Sort 500k elements", shell_sorting<int>, base500k);
    benchmark("Smooth Sort 500k elements", smooth_sorting<int>, base500k);
    benchmark("Block Sort 500k elements", wiki_sorting<int>, base500k);
    benchmark("Quick Sort 500k elements", quick_sorting<int>, base500k);
    benchmark("Grail Sort 500k elements", grail_sorting<int>, base500k);
    benchmark("Combo Sort 500k elements", combo_sorting<int>, base500k);
    benchmark("Tim Sort 500k elements", tim_sorting<int>, base500k);
    benchmark("PQD Sort 500k elements", pdq_sorting<int>, base500k);
    benchmark("Radix Sort 500k elements", radix_sorting<int>, base500k);

    auto start = std::chrono::high_resolution_clock::now();
    std::sort(base500k.begin(), base500k.end());
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "C++ native Sort 500k elements: " << diff.count() << " segundos\n";

    return 0;
}
