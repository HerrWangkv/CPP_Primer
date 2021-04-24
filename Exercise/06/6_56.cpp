#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

int f(int, int);
int sum(int i, int j) {
    cout << __func__ << ": ";
    return i + j;
}
int minus(int i, int j) {
    cout << __func__ << ": ";
    return i - j;
}
int multiply(int i, int j) {
    cout << __func__ << ": ";
    return i * j;
}
int divide(int i, int j) {
    cout << __func__ << ": ";
    return i / j;
}

int main() {
    vector<decltype(f) *> vec = {sum, minus, multiply, divide};
    for (int i = 0; i != 4; ++i) {
        cout << vec[i](4, 2) << endl;
    }
    return 0;
}