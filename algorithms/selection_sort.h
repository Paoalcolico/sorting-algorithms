#pragma once

#include <vector>

template <typename T>
std::vector<T> selection_sorting(std::vector<T> array) {
    size_t size = array.size();
    for (size_t i = 0; i < size - 1; i++) {
        size_t min = i;
        for (size_t j = i + 1; j < size; j++) {
            if (array[j] < array[min]) {
                min = j;
            }
        }
        if (min != i) {
            std::swap(array[min], array[i]);
        }
    }
    return array;
}
