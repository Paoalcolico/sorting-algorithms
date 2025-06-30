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
    size_t len1 = m - l + 1;
    size_t len2 = r - m;

    std::vector<T> left(array.begin() + l, array.begin() + m + 1);
    std::vector<T> right(array.begin() + m + 1, array.begin() + r + 1);

    size_t i = 0, j = 0, k = l;

    while (i < len1 && j < len2) {
        array[k++] = (left[i] <= right[j]) ? std::move(left[i++]) : std::move(right[j++]);
    }

    while (i < len1) array[k++] = std::move(left[i++]);
    while (j < len2) array[k++] = std::move(right[j++]);
}

template <typename T>
std::vector<T> tim_sorting(std::vector<T> array) {
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
    return array;
}
