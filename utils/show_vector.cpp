#include "show_vector.h"

#include <iostream>

void show_vector(const std::vector<int>& array) {
    for (int e : array) {
        std::cout << e << " ";
    }
    std::cout << '\n';
}
