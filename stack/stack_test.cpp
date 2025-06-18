#include <cstdlib>
#include <iostream>
#include <string>

#include "stack4.hpp"

// int main3() {
//     try {
//         Stack<int, 20> int20stack;
//         Stack<int, 40> int40stack;
//         Stack<std::string, 40> stringStack;

//         int20stack.push(7);
//         std::cout << int20stack.top() << std::endl;
//         int20stack.pop();

//         stringStack.push("Hello");
//         std::cout << stringStack.top() << std::endl;
//         stringStack.pop();
//         stringStack.pop();
//     } catch (const std::exception& ex) {
//         std::cerr << "Exception: " << ex.what() << std::endl;
//         return EXIT_FAILURE;
//     }
// }

// #include "stack3.hpp"

// int main2() {
//     try {
//         Stack<int> intStack;

//         Stack<double, std::deque<double>> doubleStack;

//         intStack.push(7);
//         std::cout << intStack.top() << std::endl;
//         intStack.pop();

//         doubleStack.push(42.42);
//         std::cout << doubleStack.top() << std::endl;
//         doubleStack.pop();
//         doubleStack.pop();
//     } catch (const std::exception& ex) {
//         std::cerr << "Exception: " << ex.what() << std::endl;
//         return EXIT_FAILURE;
//     }
//     return 0;
// }

// #include "stack1.hpp"

// int main1() {
//     try {
//         Stack<int> intStack;
//         Stack<std::string> stringStack;

//         intStack.push(7);
//         std::cout << intStack.top() << std::endl;

//         stringStack.push("hello");
//         std::cout << stringStack.top() << std::endl;
//         stringStack.pop();
//         stringStack.pop();
//     } catch (std::exception const& ex) {
//         std::cerr << "Exception: " << ex.what() << std::endl;
//         return EXIT_FAILURE;
//     }
//     return 0;
// }
