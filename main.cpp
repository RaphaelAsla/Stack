#include <iostream>

#include "stack.hpp"

int main() {
    Stack<int> a{};

    for (int i = 0; i < 100; i++) {
        a.push(i);
    }

    while (!a.is_empty()) {
        auto popped = a.pop();
        std::cout << popped.has_value() << " - " << *popped << std::endl;
    }
}
