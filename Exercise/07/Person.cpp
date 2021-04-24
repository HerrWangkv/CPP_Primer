#include "Person.h"

std::string Person::display() const {
    //字符串字面值隐式转换成string
    std::string tmp = name + " lives in " + address + ".";
    return tmp;
}
void Person::add() {
    ++num;
}
//num必须在类外定义并初始化，initNum函数此处无需标注类名
int Person::num = initNum();