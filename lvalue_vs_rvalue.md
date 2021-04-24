# 左值 VS 右值
## 1 主要区别
左值持久，右值短暂。拷贝左值，移动右值。

## 2 表达式
### 2.1 左值
1. 变量是左值(即使变量类型是右值引用)
2. 返回左值引用的函数，赋值```=```、下标```[]```、解引用```*```和前置递增递减```++ --```运算符都返回左值表达式，反例见[移动迭代器](#5-一般迭代器-vs-移动迭代器)

### 2.2 右值
1. 字面常量、临时量(如两个string相加，或对某变量取地址)为右值
2. std::move函数可以实现左值到右值引用的映射，该映射不能隐式进行，必须标注std::move。但是如果将该右值引用赋值给一个变量，该变量又是原变量的左值了(包括实参到函数形参的赋值，函数中再想调用右值引用，如派生类的移动则依旧需要std::move,见[派生类的拷贝控制成员](./15_面向对象程序设计.md)#7.3-派生类的拷贝控制成员)。
    ```cpp
    int &&rr1 = 42; //正确，字面常量是右值
    int &&rr2 = rr1;//错误，变量rr1也是左值
    ```
3. 返回非引用类型的函数，联通算术```+ - * / %```、关系```&& || ！```、位```<< >>```和后置递增递减```++ --```运算符都返回右值。这类表达式不能绑定一个左值引用，只能绑定一个const左值引用(因为[常量引用可以绑定字面常量(右值)](const.md#底层const))或右值引用。
4. 解引用[移动迭代器](#5-一般迭代器-vs-移动迭代器)获得右值

## 3 函数参数
```cpp
void f1(int &i) {}
void f2(const int &i) {}
void f3(int &&i) {}

int main() {
    int j = 5;
    f1(j);//正确：左值引用可以绑定左值(变量是左值)
    f2(j);//正确：常量引用可以绑定非常量
    f3(j);//报错：an rvalue reference cannot be bound to an lvalue，右值引用不能绑定左值
    f1(std::move(j));//报错：initial value of reference to non-const must be an lvalue
    f2(std::move(j));//正确：const左值引用可以绑定右值
    f3(std::move(std::move(j)));//正确：实参虚参都是右值
    f1(5);//报错：initial value of reference to non-const must be an lvalue,字面常量为右值
    f2(5);//正确
    f3(5);//正确
    return 0;
}
```
分析：(非const)左值引用和右值引用可以认为只能用于表示函数的虚参类型和返回类型。但他们表示该函数接受的实参以及返回到main的类型是左值还是右值。

## 4 拷贝 VS 移动
### 4.1 拷贝
要分配内存
```cpp
//拷贝指定范围，返回拷贝部分的首指针和尾后指针
pair<string *, string *> StrVec::alloc_n_copy(const string *b, const string *e) {
    //分配长度为e-b的未初始化的内存,data指向其首元素
    auto data = alloc.allocate(e - b);
    //unintialized_copy用来向未初始化内存拷贝，返回拷贝后第一元素
    return {data, std::uninitialized_copy(b, e, data)};
}
//拷贝的参数是常量左值引用
StrVec::StrVec(const StrVec &s) {
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}
StrVec& StrVec::operator=(const StrVec& rhs) {
    //防止自赋值
    auto newdata = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = newdata.first;
    first_free = cap = newdata.second;
    return *this;
}
//调用
StrVec sv1;//默认构造函数
StrVec sv2(sv1);//调用拷贝构造函数
```
### 4.2 移动
不分配内存
```cpp
//移动参数是右值引用
//noexcept不是函数名，表示通知标准库我们的构造函数不抛出任何异常
StrVec::StrVec(StrVec &&s) noexcept : elements(s.elements), first_free(s.first_free),cap(s.cap) {
    //对源对象析构
    s.elements = s.first_free = s.cap = nullptr;
}
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
//调用
StrVec sv1;//默认构造函数
StrVec sv2(std::move(sv1));//调用移动构造函数
```
详见[拷贝控制](13_拷贝控制.md)

## 5 一般迭代器 VS 移动迭代器
新标准库中定义了一种**移动迭代器**。一般迭代器解引用后得到左值，但是移动迭代器解引用后得到右值。标准库中```make_move_iterator```可以将一个普通迭代器转换为一个移动迭代器。下例类似vector<string>内存不够了，需要重分配更大的内存并移动所有元素：
```cpp
//原写法
void StrVec::reallocate() {
    auto newcapacity = capacity() ? 2 * capacity() : 1;
    //注意此处不用alloc_n_copy()来拷贝，直接移动
    //分配新内存，newdata指向首元素
    auto newdata = alloc.allocate(newcapacity);
    //创建一个指向新内存首元素的指针的副本
    auto dest = newdata;
    auto elem = elements;
    for (size_t i = 0; i != size(); ++i) {
        //std::move表示希望使用string的移动构造函数
        alloc.construct(dest++, std::move(*elem++));
    }
    free();
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}
//新写法
void StrVec::reallocate() {
    auto newcapicity = capacity() ? 2 * capacity() : 1;
    auto first = alloc.allocate(newcapacity);
    auto last = uninitialized_copy(make_move_iterator(begin()), make_move_iterator(end()), first);
    free();
    elements = first;
    first_free = last;
    cap = elements + newcapacity;
}
```
即通过std::move和移动迭代器```make_move_iterator```两种方法获得右值