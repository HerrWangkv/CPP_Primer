#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <string>
using std::string;

class Employee {
public:
    Employee();
    Employee(const string &name);
    Employee(const Employee &) = default;
    Employee &operator=(const Employee &) = default;
    const int returnId() { return this->id; }
    const string returnName() { return this->name; }

private:
    string name;
    int id;
    static int total;
};
//静态数据成员必须在类外定义，且不能重复static
int Employee::total = 0;

Employee::Employee() {
    name = "You Know Who";
    id = ++total;
}
Employee::Employee(const string &name) {
    this->name = name;
    id = ++total;
}
#endif