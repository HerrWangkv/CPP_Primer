#include <iostream>
#include "Blob.h"
#include "BlobPtr.h"
#include <string>
using std::cout;
using std::endl;

int main()
{
    Blob<int> squares = {0, 1, 2, 3, 4, 5};
    const Blob<std::string> articles = {"a", "an", "the"};
    /*
    std::cout << squares[5] << std::endl;
    squares.pop_back();
    std::cout << squares.back() << std::endl;
    std::cout << articles.front() << std::endl;
    */
    for (BlobPtr<int> beg = squares.begin(); beg != squares.end(); ++beg) {
        cout << *beg << " ";
    }
    cout << endl;

    for (BlobPtr<std::string> beg = articles.cbegin(); beg != articles.cend(); ++beg) {
        cout << *beg << " ";
    }
    cout << endl;
    return 0;
}