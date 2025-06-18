#pragma once

#include <vector>

template <typename T>
std::vector<T> cocktail_sorting(std::vector<T> array) {
    size_t start = 0;
    size_t end = array.size() - 1;
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (size_t i = start; i < end; ++i) {
            if (array[i] > array[i + 1]) {
                std::swap(array[i], array[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
        swapped = false;
        --end;
        for (size_t i = end - 1; i > start; --i) {
            if (array[i] > array[i + 1]) {
                std::swap(array[i], array[i + 1]);
                swapped = true;
            }
        }
        ++start;
    }
    return array;
}
