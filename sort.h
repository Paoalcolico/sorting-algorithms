#pragma once

#include <algorithms/block_sort.h>
#include <algorithms/bubble_sort.h>
#include <algorithms/cocktail_sort.h>
#include <algorithms/combo_sort.h>
#include <algorithms/cycle_sort.h>
#include <algorithms/exchange_sort.h>
#include <algorithms/gnome_sorting.h>
#include <algorithms/grail_sort.h>
#include <algorithms/insertion_sort.h>
#include <algorithms/odd_even_sort.h>
#include <algorithms/patience_sort.h>
#include <algorithms/pdq_sort.h>
#include <algorithms/quick_sort.h>
#include <algorithms/radix_sort.h>
#include <algorithms/selection_sort.h>
#include <algorithms/shell_sort.h>
#include <algorithms/smooth_sort.h>
#include <algorithms/strand_sort.h>
#include <algorithms/tim_sort.h>

template <typename T>
std::vector<T> wiki_sorting(std::vector<T> array) {
    Wiki::Sort(array.begin(), array.end(), std::less<T>());
    return array;
}

template <typename T>
std::vector<T> bubble_sorting(std::vector<T> array) {
    bubble_sort(array);
    return array;
}

template <typename T>
std::vector<T> cocktail_sorting(std::vector<T> array) {
    cocktail_sort(array);
    return array;
}

template <typename T>
std::vector<T> combo_sorting(std::vector<T> array) {
    combo_sort(array);
    return array;
}

template <typename T>
std::vector<T> cycle_sorting(std::vector<T> array) {
    cycle_sort(array);
    return array;
}

template <typename T>
std::vector<T> exchange_sorting(std::vector<T> array) {
    exchange_sort(array);
    return array;
}

template <typename T>
std::vector<T> gnome_sorting(std::vector<T> array) {
    gnome_sort(array);
    return array;
}

template <typename T>
std::vector<T> grail_sorting(std::vector<T> array) {
    common_sort(array.data(), array.size(), static_cast<T*>(nullptr), 0);
    return array;
}

template <typename T>
std::vector<T> insertion_sorting(std::vector<T> array) {
    insertion_sort(array);
    return array;
}

template <typename T>
std::vector<T> odd_even_sorting(std::vector<T> array) {
    odd_even_sort(array);
    return array;
}

template <typename T>
std::vector<T> patience_sorting(std::vector<T> array) {
    patience_sort(array);
    return array;
}

template <typename T>
std::vector<T> pdq_sorting(std::vector<T> vec) {
    pdqsort(vec.begin(), vec.end(), std::less<T>());
    return vec;
}

template <typename T>
std::vector<T> quick_sorting(std::vector<T> array) {
    quick_sort(array, 0, array.size() - 1);
    return array;
}

template <typename T>
std::vector<T> radix_sorting(std::vector<T> array) {
    radix_sort(array);
    return array;
}

template <typename T>
std::vector<T> selection_sorting(std::vector<T> array) {
    selection_sort(array);
    return array;
}

template <typename T>
std::vector<T> shell_sorting(std::vector<T> array) {
    shell_sort(array);
    return array;
}

template <typename T>
std::vector<T> smooth_sorting(std::vector<T> array) {
    smooth_sort(array);
    return array;
}

template <typename T>
std::vector<T> strand_sorting(std::vector<T> array) {
    strand_sort(array);
    return array;
}

template <typename T>
std::vector<T> tim_sorting(std::vector<T> array) {
    tim_sort(array);
    return array;
}
