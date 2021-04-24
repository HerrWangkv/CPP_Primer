#include <iostream>
using std::cout;
using std::endl;

void swap(int &ri1, int &ri2) {
    int temp = ri1;
    ri1 = ri2;
    ri2 = temp;
}

int main() {
    int i1 = 5, i2 = 10;
    cout << i1 << " " << i2 << endl;
    swap(i1, i2);
    cout << i1 << " " << i2 << endl;
    return 0;
}