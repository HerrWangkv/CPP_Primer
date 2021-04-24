#include <iostream>
#include "Chapter6.h"
using std::cin;
using std ::cout;
using std::endl;

int main() {
    int num;
    cout << "Please enter a positive integer inside [0,10]:";
    while (cin >> num) {
        if (num > 0 && num < 11)
            break;
        else
            cout << "Error: out of range! Please try again" << endl;
    }
    cout << num << "! = " << fact(num);
    return 0;
}