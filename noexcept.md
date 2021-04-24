# noexcept特性
## 1 移动构造函数
```cpp
//noexcept不是函数名，表示通知标准库我们的构造函数不抛出任何异常
StrVec::StrVec(StrVec &&s) noexcept : elements(s.elements), first_free(s.first_free),cap(s.cap) {
    //对源对象析构
    s.elements = s.first_free = s.cap = nullptr;
}
```
## 2 移动赋值运算符
```cpp
StrVec &StrVec::operator=(StrVec &&rhs) noexcept {
    //直接检查自赋值
    if (this != &rhs) {
        free();
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}
```