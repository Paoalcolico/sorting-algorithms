#pragma once

#include <bits/stdc++.h>

template <typename T>
std::vector<T> merge_piles(std::vector<std::vector<T>>& v) {
    std::vector<T> ans;
    while (!v.empty()) {
        T minu = v[0].back();
        int index = 0;
        for (size_t i = 1; i < v.size(); i++) {
            if (v[i].back() < minu) {
                minu = v[i].back();
                index = i;
            }
        }
        ans.push_back(minu);
        v[index].pop_back();
        if (v[index].empty()) {
            v.erase(v.begin() + index);
        }
    }
    return ans;
}

template <typename T>
void patience_sort(std::vector<T>& arr) {
    std::vector<std::vector<T>> piles;
    for (const T& val : arr) {
        bool placed = false;
        for (auto& pile : piles) {
            if (val < pile.back()) {
                pile.push_back(val);
                placed = true;
                break;
            }
        }
        if (!placed) {
            piles.push_back({val});
        }
    }

    arr = merge_piles(piles);
}
