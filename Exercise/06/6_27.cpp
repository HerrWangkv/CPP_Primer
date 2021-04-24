#include <iostream>
#include <initializer_list>
using std::cout;
using std::initializer_list;

int sum(const initializer_list<int> &lst) {
    int res = 0;
    for (auto i : lst) {
        res += i;
    }
    return res;
}

int main() {
    cout << sum({1, 2, 3, 4, 5});
    return 0;
}