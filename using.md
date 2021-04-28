# using 用法
## 1 别名声明 alias declaration
```cpp
using c = double; // c是double的同义词
using int_array = int[4]; //int_array表示创建容量为4的整型数组
using F = int(int*, int); // F是函数类型
using PF = int (*) (int*, int); //PF才是指针类型

PF f1(int);// 返回类型为函数指针
F *f1(int);//等价
```

## 2 命名空间的using声明
```cpp
using std::cin; //仅使用命名空间的某个成员
using std::cout; using std::endl;//一行可以放多句，但需要一分号分隔
```

## 3 改变派生类中成员的可访问性
```cpp
class Base {
public:
    std::size_t size() const {return n;}
protected:
    std::size_t n;
};
//私有继承使所有积累成员在派生类中可访问性为private
class Derived : private Base {
public:
    using Base::size;//将size成员定为public
protected:
    using Base::n;
};
```
派生类只能为那些它可以访问的名字提供using声明，基类中private成员不能使用using声明。

## 4 继承基类构造函数
类不能继承默认、拷贝和移动构造函数，也就是说参数不能是空、类的常量引用、类的右值引用。
```cpp
class Bulk_quote : public Disc_quote {
public:
    using Disc_quote::Disc_quote;//继承Disc_quote的构造函数，并直接令编译器产生代码
    //等价于
    Bulk_quote::Bulk_quote(const std::string &book, double p, std::size_t qty, double disc) : Disc_quote(book, p, qty, disc) { }
};
```
如果派生类含有自己的数据成员，则这些成员将被默认初始化。

一个构造函数的using声明不会改变构造函数的访问级别。基类的私有构造函数在派生类中还是一个私有构造函数。且一个using声明不会改变explicit或者constexpr的继承。

## 5 模板类型别名
```cpp
template<typename T> using twin = pair<T, T>;
template<typename T> using partNo = pair<T, unsigned>;
twin<string> authors;//pair<string, string>
partNo<string> books;//pair<string, unsigned>
```