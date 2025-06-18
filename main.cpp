#include <vector>

#include "benchmark.h"
#include "bubble_sort.h"
#include "cocktail_sort.h"
#include "cycle_sort.h"
#include "exchange_sort.h"
#include "generate_random_vector.h"
#include "gnome_sorting.h"
#include "insertion_sort.h"
#include "odd_even_sorting.h"
#include "selection_sort.h"
#include "show_vector.h"
#include "strand_sort.h"

int main() {
    const size_t SIZE = 10000;
    std::vector<int> base = generate_random_vector(SIZE);

    benchmark("Cycle Sort", cycle_sorting<int>, base);
    benchmark("Exchange Sort", exchange_sorting<int>, base);
    benchmark("Selection Sort", selection_sorting<int>, base);
    benchmark("Strand Sort", strand_sorting<int>, base);
    benchmark("Odd-Even Sort", odd_even_sorting<int>, base);
    benchmark("Gnome Sort", gnome_sorting<int>, base);
    benchmark("Cocktail Sort", cocktail_sorting<int>, base);
    benchmark("Bubble Sort", bubble_sorting<int>, base);
    benchmark("Insertion Sort", insertion_sorting<int>, base);

    return 0;
}
