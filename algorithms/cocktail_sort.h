#pragma once

#include <utility>
#include <vector>

template <typename T>
void cocktail_sort(std::vector<T>& array) {
    size_t start = 0;
    size_t end = array.size() - 1;
    bool swapped;
    do {
        swapped = false;
        for (size_t i = start; i < end; ++i) {
            if (array[i] > array[i + 1]) {
                std::swap(array[i], array[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
        swapped = false;
        --end;
        for (size_t i = end; i > start; --i) {
            if (array[i - 1] > array[i]) {
                std::swap(array[i - 1], array[i]);
                swapped = true;
            }
        }
        ++start;
    } while (swapped);
}
