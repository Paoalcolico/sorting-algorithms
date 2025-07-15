#pragma once

#include <vector>

template <typename T>
void insertion_sort(std::vector<T>& array) {
    size_t i = 1;
    while (i < array.size()) {
        size_t j = i;
        while (j > 0 && array[j - 1] > array[j]) {
            std::swap(array[j], array[j - 1]);
            j--;
        }
        i++;
    }
}
