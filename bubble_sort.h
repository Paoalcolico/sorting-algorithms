#pragma once

#include <vector>

template <typename T>
std::vector<T> bubble_sorting(std::vector<T> array) {
    size_t size = array.size();
    bool sorted = false;
    while (!sorted) {
        sorted = true;
        for (size_t i = 0; i < size - 1; i++) {
            if (array[i] > array[i + 1]) {
                std::swap(array[i], array[i + 1]);
                sorted = false;
            }
        }
        size--;
    }
    return array;
}
