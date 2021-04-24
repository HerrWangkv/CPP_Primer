#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

class Person {
    friend std::istream &read(std::istream &is, Person &p);

public:
    Person() = default;
    Person(const std::string &n, const std::string &a) : name(n), address(a) { add(); } //初始化一人，++num
    //读入一人信息，++num，且抑制隐式转换
    explicit Person(std::istream &is) { 
        read(is, *this);
        add();
    }
    std::string getName() const { return this->name; }
    std::string getAddress() const { return this->address; }
    std::string display() const;
    static void add();
    static void count() { std::cout << "We have now " << num << " people." << std::endl; }

private:
    std::string name;
    std::string address;
    static int num; //静态成员表示一共记录了多少个人的信息
    static int initNum() { return 0; }
};
#endif