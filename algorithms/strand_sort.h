#pragma once

#include <list>
#include <vector>

template <typename T>
std::list<T> extract_strand(std::list<T>& input) {
    std::list<T> strand;

    auto it = input.begin();
    if (it == input.end()) return strand;

    strand.push_back(*it);
    it = input.erase(it);

    auto last = strand.back();

    while (it != input.end()) {
        if (*it >= last) {
            last = *it;
            strand.push_back(last);
            it = input.erase(it);
        } else {
            ++it;
        }
    }

    return strand;
}

template <typename T>
std::list<T> merge(const std::list<T>& a, const std::list<T>& b) {
    std::list<T> result;
    auto it_a = a.begin();
    auto it_b = b.begin();

    while (it_a != a.end() && it_b != b.end()) {
        if (*it_a <= *it_b) {
            result.push_back(*it_a);
            ++it_a;
        } else {
            result.push_back(*it_b);
            ++it_b;
        }
    }

    result.insert(result.end(), it_a, a.end());
    result.insert(result.end(), it_b, b.end());

    return result;
}

template <typename T>
void strand_sort(std::vector<T>& input_array) {
    std::list<T> input(input_array.begin(), input_array.end());
    std::list<T> sorted;

    while (!input.empty()) {
        std::list<T> strand = extract_strand(input);
        sorted = merge(sorted, strand);
    }

    input_array = std::vector<T>(sorted.begin(), sorted.end());
}
