#include <iostream>
#include <vector>
#include "Person.h"

std::istream &read(std::istream &is, Person &p) {
    is >> p.name >> p.address;
    return is;
}
std::ostream &print(std::ostream &os, const Person &p) {
    os << p.getName() << " " << p.getAddress();
    return os;
}

int main() {
    Person a("Kevin", "Germany");
    std::vector<Person> vec{a};
    bool flag = true;
    char cont;
    while (flag) {
        std::cout << "Please enter a name and an address: ";
        Person *ptr = new Person(std::cin);
        vec.push_back(*ptr);
        std::cout << "Continue?(y/N): ";
        std::cin >> cont;
        flag = (cont == 'y' ? true : false);
    }
    std::cout << "**************************Name List**************************" << std::endl;
    for (auto person : vec) {
        std::cout << person.display() << std::endl;
    }
    std::cout << "-------------------------------------------------------------" << std::endl;
    Person::count();
    return 0;
}