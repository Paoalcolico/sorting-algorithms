#include <deque>
#include <string>

#include "stack1.hpp"

template <>
class Stack<std::string> {
   private:
    std::deque<std::string> elems;

   public:
    void push(const std::string&);
    void pop();
    std::string top() const;
    bool empty() const {
        return elems.empty();
    }
};
