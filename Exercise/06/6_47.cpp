#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;
//#define NDEBUG
using Iter = vector<int>::const_iterator;
void print(Iter beg, Iter end) {
    #ifndef NDEBUG
    cout << "Vector size: " << end - beg << endl;
    #endif
    if (beg == end)
        return;
    cout << *beg << " ";
    print(beg + 1, end);
}

int main() {
    vector<int> vec{1, 2, 3, 4, 5};
    print(vec.begin(), vec.end());
    return 0;
}