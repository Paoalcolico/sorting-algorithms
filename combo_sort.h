#pragma once

#include <cmath>
#include <vector>

template <typename T>
std::vector<T> combo_sorting(std::vector<T> array) {
    size_t gap = array.size();
    double shrink = 1.3;
    bool sorted = false;
    while (!sorted) {
        gap = std::floor(gap / shrink);
        if (gap <= 1) {
            gap = 1;
            sorted = true;
        } else if (gap == 9 || gap == 10) {
            gap = 11;
        }

        size_t i = 0;
        while (i + gap < array.size()) {
            if (array[i] > array[i + gap]) {
                std::swap(array[i], array[i + gap]);
                sorted = false;
            }
            i++;
        }
    }
    return array;
}
