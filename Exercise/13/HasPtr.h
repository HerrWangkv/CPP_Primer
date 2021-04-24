#ifndef HASPTR_H
#define HASPTR_H
#include <string>
using std::size_t;
using std::string;

class HasPtr;
inline void swap(HasPtr &lhs, HasPtr &rhs) {
    using std::swap;
    swap(lhs.ps, rhs.ps);  //交换指针，而不是string数据
    swap(lhs.i, rhs.i);
}

class HasPtr {
    friend void swap(HasPtr &, HasPtr &);

public:
    HasPtr(const string &s = string()) : ps(new string(s)), i(0) { }
    //不是直接拷贝指针，而是拷贝指针指向的对象
    HasPtr(const HasPtr &p) : ps(new string(*p.ps)), i(p.i) { }
    HasPtr &operator=(HasPtr);
    ~HasPtr() { delete ps; }

private:
    string *ps;
    int i;
};

HasPtr &HasPtr::operator=(HasPtr rhs) {
    //注意rhs是赋值的，即经过拷贝构造函数构造的形参
    swap(*this, rhs);
    //转换后的rhs(原*this自动被析构)
    return *this;
}

#endif