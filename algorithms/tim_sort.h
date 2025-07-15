#pragma once

#include <algorithm>
#include <vector>

const int RUN = 32;

template <typename T>
void insertion_sort(std::vector<T>& array, size_t left, size_t right) {
    for (size_t i = left + 1; i <= right; i++) {
        T temp = std::move(array[i]);
        size_t j = i;
        while (j > left && array[j - 1] > temp) {
            array[j] = std::move(array[j - 1]);
            --j;
        }
        array[j] = std::move(temp);
    }
}

template <typename T>
void merge(std::vector<T>& array, size_t l, size_t m, size_t r) {
    auto left = std::vector<T>(
        std::make_move_iterator(array.begin() + l),
        std::make_move_iterator(array.begin() + m + 1)
    );
    auto right = std::vector<T>(
        std::make_move_iterator(array.begin() + m + 1),
        std::make_move_iterator(array.begin() + r + 1)
    );

    size_t i = 0, j = 0, k = l;
    while (i < left.size() && j < right.size()) {
        array[k++] = (left[i] <= right[j]) ? std::move(left[i++]) : std::move(right[j++]);
    }
    while (i < left.size()) array[k++] = std::move(left[i++]);
    while (j < right.size()) array[k++] = std::move(right[j++]);
}

template <typename T>
void tim_sort(std::vector<T>& array) {
    size_t n = array.size();
    for (size_t i = 0; i < n; i += RUN) {
        insertion_sort(array, i, std::min(i + RUN - 1, n - 1));
    }
    for (size_t size = RUN; size < n; size *= 2) {
        for (size_t left = 0; left < n; left += 2 * size) {
            size_t mid = left + size - 1;
            if (mid >= n - 1) continue;
            size_t right = std::min(left + 2 * size - 1, n - 1);
            merge(array, left, mid, right);
        }
    }
}
