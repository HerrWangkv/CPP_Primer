# explicit用法
## 1 explicit构造函数
```cpp
class A {
public:
A() = default;
explicit A(string str) : a(str) { } //隐式转换被抑制
...
private:
string a;
};
A temp("abc");//正确
A temp = "abc";//错误，explicit构造函数仅能通过直接初始化的方式初始化
```
explicit只允许出现在类内声明处，类外定义时不允许使用。且explicit构造函数**仅能**通过直接初始化的方式初始化，不允许通过 = 赋值初始化。


但显式转换是允许的：
```cpp
string str = "def";
temp.combine(str);//报错：explicit抑制了隐式转换
temp.comine(A(str));//正确,使用构造函数显示转换
temp.comine(static_cast<A>(str));//正确，显示转换
```
- 标准库中的explicit
1. 字符串字面值可以隐式转换成string，不是explicit的
2. vector<int> vec(10);用来表示初始化一个含有10个默认元素的数组是explicit，不然数字可以隐式转换成vector了。

## 2 explicit类型转换运算符
显式转换：
```cpp
class SmallInt {
public:
    //int 向 SmallInt的转换
    SmallInt(int i = 0) : val(i) {
        if (i < 0 || i > 255)
            throw std::out_of_range("Bad SmallInt Value");
    }
    //编译器不会自动执行这一类型转换
    explicit operator int() const { return val;}
    /*...*/
private:
    std::size_t val;
};
SmallInt si = 3;//正确
si + 3;//错误
static_cast<int>(si) + 3;//正确，显式请求类型转换
```
例外：如果表达式是条件(如用在if中)，则不一定显式转换也可以进行直接隐式转换。但一般```operator bool```定义成explicit的。