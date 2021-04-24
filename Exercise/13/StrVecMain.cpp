#include "StrVec.h"
#include <iostream>
using std::cout;
using std::endl;

int main()
{
    StrVec sv1, sv2;
    sv1.push_back("Hello World");
    sv1.push_back("Hello World cpp");
    sv2 = sv1;
    cout << "sv1:" << endl;
    auto beg1 = sv1.begin();
    for (size_t i = 0; i != sv1.size(); ++i)
    {
        cout << *(beg1++) << endl;
    }
    cout << endl;
    sv2.push_back("I hate cpp");
    cout << "sv2:" << endl;
    auto beg2 = sv2.begin();
    for (size_t i = 0; i != sv2.size(); ++i)
    {
        cout << *(beg2++) << endl;
    }
    return 0;
}