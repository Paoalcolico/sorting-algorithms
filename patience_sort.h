#pragma once

#include <algorithm>
#include <queue>
#include <vector>

template <typename T>
std::vector<T> merge_piles(const std::vector<std::vector<T>>& piles_input) {
    using PQElement = std::tuple<T, int, int>;
    auto cmp = [](const PQElement& a, const PQElement& b) {
        return std::get<0>(a) > std::get<0>(b);
    };
    std::priority_queue<PQElement, std::vector<PQElement>, decltype(cmp)> min_heap(cmp);
    std::vector<size_t> indices(piles_input.size(), 0);
    std::vector<T> result;
    for (size_t i = 0; i < piles_input.size(); ++i) {
        if (!piles_input[i].empty()) {
            min_heap.emplace(piles_input[i][0], i, 0);
        }
    }
    while (!min_heap.empty()) {
        auto [val, pile_idx, elem_idx] = min_heap.top();
        min_heap.pop();
        result.push_back(val);

        size_t next_idx = elem_idx + 1;
        if (next_idx < piles_input[pile_idx].size()) {
            min_heap.emplace(piles_input[pile_idx][next_idx], pile_idx, next_idx);
        }
    }
    return result;
}

template <typename T>
std::vector<T> patience_sorting(const std::vector<T>& array) {
    std::vector<std::vector<T>> piles;
    for (const T& val : array) {
        auto it = std::lower_bound(
            piles.begin(),
            piles.end(),
            val,
            [](const std::vector<T>& pile, const T& value) {
                return pile.back() < value;
            }
        );
        if (it == piles.end()) {
            piles.push_back({val});
        } else {
            it->push_back(val);
        }
    }
    return merge_piles(piles);
}
