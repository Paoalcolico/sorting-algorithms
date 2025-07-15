#pragma once

#include <vector>

template <typename T>
int partition(std::vector<T>& array, int low, int high) {
    int pivot = array[high];

    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (array[j] <= pivot) {
            i++;
            std::swap(array[i], array[j]);
        }
    }

    std::swap(array[i + 1], array[high]);
    return i + 1;
}

template <typename T>
void quick_sort(std::vector<T>& array, int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);

        quick_sort(array, low, pi - 1);
        quick_sort(array, pi + 1, high);
    }
}
