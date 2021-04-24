#include "Query.h"
#include <iostream>
#include <string>

int main() {
    std::ifstream infile("./storyDataFile.txt");
    TextQuery tq(infile);
    std::string word;
    std::cout << "Please enter the word you want to find: ";
    std::cin >> word;
    tq.findWord(word).print(std::cout);
    return 0;

}