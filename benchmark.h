#pragma once

#include <chrono>
#include <iostream>

template <typename Func>
void benchmark(const std::string& name, Func func, const std::vector<int>& data) {
    auto start = std::chrono::high_resolution_clock::now();
    func(data);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << name << ": " << diff.count() << " segundos\n";
}
