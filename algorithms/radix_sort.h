#pragma once

#include <vector>

template <typename T>
T get_max(const std::vector<T>& array) {
    T max_val = array[0];
    for (const T& val : array)
        if (val > max_val) max_val = val;
    return max_val;
}

template <typename T>
void count_sort(std::vector<T>& array, T exp) {
    constexpr int base = 10;
    std::vector<T> output(array.size());
    int count[base] = {0};

    for (const T& val : array) count[(val / exp) % base]++;

    for (int i = 1; i < base; i++) count[i] += count[i - 1];

    for (std::ptrdiff_t i = array.size() - 1; i >= 0; i--) {
        int index = (array[i] / exp) % base;
        output[--count[index]] = array[i];
    }

    array.swap(output);
}

template <typename T>
void radix_sort(std::vector<T>& array) {
    const T max_val = get_max(array);
    for (T exp = 1; max_val / exp > 0; exp *= 10) count_sort(array, exp);
}
