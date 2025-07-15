#pragma once

#include <vector>

template <typename T>
std::vector<T> bubble_sorting(std::vector<T> array) {
    for (size_t n = array.size(); n > 1; --n) {
        bool swapped = false;
        for (size_t i = 0; i < n - 1; ++i) {
            if (array[i] > array[i + 1]) {
                std::swap(array[i], array[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }

    return array;
}
