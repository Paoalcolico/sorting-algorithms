#pragma once

#include <vector>

template <typename T>
std::vector<T> gnome_sorting(std::vector<T> array) {
    size_t index = 0;
    while (index < array.size()) {
        if (index == 0) {
            index++;
            continue;
        }
        if (array[index] >= array[index - 1]) {
            index++;
        } else {
            std::swap(array[index], array[index - 1]);
            index--;
        }
    }
    return array;
}
