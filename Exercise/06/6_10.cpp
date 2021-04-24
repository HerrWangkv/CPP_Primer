#include <iostream>
using std::cout;
using std::endl;

void swap(int *pi1, int *pi2) {
    int temp = *pi1;
    *pi1 = *pi2;
    *pi2 = temp;
}

int main() {
    int i1 = 5, i2 = 10;
    cout << i1 << " " << i2 << endl;
    swap(&i1, &i2);
    cout << i1 << " " << i2 << endl;
    return 0;
}