#pragma once

#include <vector>

template <typename T>
std::vector<T> exchange_sorting(std::vector<T> array) {
    size_t size = array.size();
    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = i + 1; j < size; j++) {
            if (array[j] < array[i]) {
                std::swap(array[i], array[j]);
            }
        }
    }
    return array;
}
