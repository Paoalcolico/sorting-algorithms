#include <stdexcept>
#include <vector>

template <typename T>
class Stack {
   private:
    std::vector<T> elems;

   public:
    Stack(){};
    Stack(const Stack<T>&);
    Stack<T>& operator=(const Stack<T>&);
    void push(const T&);
    T pop();
    T top() const;
    bool empty() const {
        return elems.empty();
    }
};

template <typename T>
void Stack<T>::push(const T& elem) {
    elems.push_back(elem);
}

template <typename T>
T Stack<T>::pop() {
    if (elems.empty()) {
        throw std::out_of_range("Stack<>::pop(): empty stack");
    }
    T elem = elems.back();
    elems.pop_back();
    return elem;
}

template <typename T>
T Stack<T>::top() const {
    if (elems.empty()) {
        throw std::out_of_range("Stack<>::top(): empty stack");
    }
    return elems.back();
}
