#pragma once

#include <vector>

template <typename T>
void odd_even_sort(std::vector<T>& array) {
    bool is_sorted = false;
    while (!is_sorted) {
        is_sorted = true;

        for (size_t i = 1; i <= array.size() - 2; i += 2) {
            if (array[i] > array[i + 1]) {
                std::swap(array[i], array[i + 1]);
                is_sorted = false;
            }
        }

        for (size_t i = 0; i <= array.size() - 2; i += 2) {
            if (array[i] > array[i + 1]) {
                std::swap(array[i], array[i + 1]);
                is_sorted = false;
            }
        }
    }
}
