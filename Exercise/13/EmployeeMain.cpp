#include <iostream>
#include "Employee.h"
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
int main() {
    //非explicit构造函数
    vector<Employee> google = {static_cast<string>("QD Liu"), static_cast<string>("Bill Gaites")};
    //只有在允许拷贝构造函数时才能与标准库容器联用
    google.emplace_back("Jackie Ma");
    google.emplace_back("Tonya Ma");
    google.emplace_back();
    //必须加引用，因为默认拷贝构造函数被delete了
    for (auto &person : google) {
        cout << person.returnId() << ": " << person.returnName() << endl;
    }
    return 0;
}