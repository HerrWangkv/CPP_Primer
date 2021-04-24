#include <iostream>
#include "Blob.h"
#include <string>

int main() {
    Blob<int> squares = {0, 1, 2, 3, 4, 5};
    const Blob<std::string> articles = {"a", "an", "the"};
    std::cout << squares[5] << std::endl;
    squares.pop_back();
    std::cout << squares.back() << std::endl;
    std::cout << articles.front() << std::endl;
    return 0;
}