#pragma once

#include <vector>

template <typename T>
std::vector<T> cycle_sorting(std::vector<T> array) {
    const size_t n = array.size();
    if (n < 2) return array;

    for (size_t cycle_start = 0; cycle_start < n - 1; ++cycle_start) {
        T item = array[cycle_start];
        size_t pos = cycle_start;
        for (size_t i = cycle_start + 1; i < n; ++i) {
            if (array[i] < item) ++pos;
        }

        if (pos == cycle_start) continue;

        while (item == array[pos]) ++pos;

        if (pos != cycle_start) std::swap(item, array[pos]);

        while (pos != cycle_start) {
            pos = cycle_start;
            for (size_t i = cycle_start + 1; i < n; ++i) {
                if (array[i] < item) ++pos;
            }
            while (item == array[pos]) ++pos;
            std::swap(item, array[pos]);
        }
    }
    return array;
}
