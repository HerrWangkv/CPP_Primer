#include <iostream>
#include <string>
#include <cctype>

using std::cout;
using std::endl;
using std::string;

bool hasCapital(const string &str) {
    for (auto c : str) {
        if (c >= 'A' && c <= 'Z')
            return true;
    }
    return false;
}

void toLowerCase(string &str) {
    for (auto &c : str)
        c = tolower(c);
}

int main() {
    string str = "happY";

    cout << "This string "
         << (hasCapital(str) ? "has " : "doesn't have ")
         << "capital letters" << endl;
    toLowerCase(str);
    cout << str;
    return 0;
}