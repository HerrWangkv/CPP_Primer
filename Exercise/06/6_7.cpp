#include <iostream>
using std::cin;
using std::cout;
using std::endl;

//impuls为形参
int accumulate(int impuls) {
    //initial为局部静态变量
    static int initial = -1;
    initial += impuls;
    return initial;
}

int main() {
    //i 为局部变量
    for (int i = 0; i < 10; ++i)
        cout << accumulate(1) << endl;
    return 0;
}