# typename 用法
## 1 模板类声明及定义(与template连用,可以用class替换)
typename仅涉及模板类型参数的情况，即不同实例之间的区别在于参数类型，而与[非类型模板参数](16_模板与泛型编程.md#1.1-函数模板)无关。
### 1.1 函数模板
```cpp
//声明
template <typename T> int compare(const T&, const T&);
//定义
template <typename T> int compare(const T &v1, const T &v2) {
    if (v1 < v2) return -1;
    if (v1 < v1) return 1;
    return 0;
}
```
### 1.2 类模板
```cpp
template <typename T> class BlobPtr {
public:
    //在类模板内使用简化模板类名
    BlobPtr operator++(int);//后置运算符
    /*...*/
};
//在类模板作用域外使用类模板名
template <typename T> BlobPtr<T> BlobPtr<T>::operator++(int) {
    BlobPtr ret = *this;//此处又在类模板作用域内了，简化类名
    ++*this;
    return ret;
}
```

# 2 显式告诉编译器某个名字是类型(不与template连用,不能被class替换)
对于下面的代码(T为typename)
```cpp
T::size_type *p;
```
在实例化之前，编译器不知道我们在定义一个名为p的指针(如类型为T::size_type)还是将一个(类T中)名为size_type的static数据成员与名为p的变量相乘。因此我们需要显示告诉编译器T::size_type是一个类型，需要使用typename：
```cpp
//typename T::value_type表示返回类型
template <typename T>
typename T::value_type top(const T& c) {
    if (!c.empty())
        return c.back();
    else
        //typename T::value_type为类型
        return typename T::value_type();
}
```
或者在某个类模板中定义类型别名：
```cpp
template <typename T> class Blob {
public:
    typedef typename std::vector<T>::size_type size_type;
};
```