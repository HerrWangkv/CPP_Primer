#include <iostream>
#include <string>
using std::cout;
using std::string;

int main(int argc, char *argv[]) {
    if (argc < 2)
        cout << "Error!";
    string s1 = argv[1], s2 = argv[2];
    cout << s1 + s2;
    return 0;
}