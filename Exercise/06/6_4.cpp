#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int fact(int val) {
    if (val == 1)
        return 1;
    else
        return val * fact(val - 1);
}

void interactiveFact() {
    int num;
    cout << "Please enter a positive integer inside [0,10]:";
    while (cin >> num) {
        if (num > 0 && num < 11)
            break;
        else
            cout << "Error: out of range! Please try again" << endl;
    }
    cout << num << "! = " << fact(num);
}
int main() {
    interactiveFact();
    return 0;
}