#include <iostream>
using std::cin;
using std ::cout;
using std ::endl;

int  printAbs(int val) {
    return (val > 0 ? val : -val);
}

int main() {
    cout << printAbs(5) << endl;
    cout << printAbs(-5) << endl;
    return 0;
}