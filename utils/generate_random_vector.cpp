#include "generate_random_vector.h"

#include <random>

std::vector<int> generate_random_vector(size_t size, int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);

    std::vector<int> vec(size);
    for (auto& val : vec) {
        val = dist(gen);
    }
    return vec;
}
