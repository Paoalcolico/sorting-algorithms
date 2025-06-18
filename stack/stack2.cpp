#include "stack2.h"

#include <stdexcept>

void Stack<std::string>::push(const std::string& elem) {
    elems.push_back(elem);
}

void Stack<std::string>::pop() {
    if (elems.empty()) {
        throw std::out_of_range("Stack<std::string>::pop(): empty stack");
    }
    elems.pop_back();
}

std::string Stack<std::string>::top() const {
    if (elems.empty()) {
        throw std::out_of_range("Stack<std::string>::top(): empty stack");
    }
    return elems.back();
}
