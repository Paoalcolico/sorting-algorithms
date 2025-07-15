#pragma once

#include <cmath>
#include <vector>

template <typename T>
void shell_sort(std::vector<T>& array) {
    std::vector<int> gaps = {1750, 701, 301, 132, 57, 23, 10, 4, 1};
    for (int gap : gaps) {
        for (size_t i = gap; i < array.size(); ++i) {
            T temp = array[i];
            int j = static_cast<int>(i);
            while (j >= gap && array[j - gap] > temp) {
                array[j] = array[j - gap];
                j -= gap;
            }
            array[j] = temp;
        }
    }
}
