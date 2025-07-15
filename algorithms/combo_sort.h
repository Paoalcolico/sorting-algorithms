#pragma once

#include <cmath>
#include <vector>

template <typename T>
void combo_sort(std::vector<T>& array) {
    size_t gap = array.size();
    double shrink = 1.3;
    bool swapped = true;
    while (gap > 1 || swapped) {
        gap = static_cast<size_t>(std::floor(gap / shrink));
        if (gap < 1) gap = 1;
        if (gap == 9 || gap == 10) gap = 11;
        swapped = false;
        for (size_t i = 0; i + gap < array.size(); ++i) {
            if (array[i] > array[i + gap]) {
                std::swap(array[i], array[i + gap]);
                swapped = true;
            }
        }
    }
}
