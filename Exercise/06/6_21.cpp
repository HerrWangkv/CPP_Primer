#include <iostream>
using std::cout;

int returnBigger(const int i, const int *p) {
    return (i > *p ? i : *p);
}
int main() {
    int a = 5, b = 10;
    cout << returnBigger(a, &b);
    return 0;
}
