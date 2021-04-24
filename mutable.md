# mutable用法
## 1 可变数据成员 mutable data member
即使类对象是const(或者普通类对象的const成员函数中)，可变成员也可变。
```cpp
class Screen {
public:
void some_member() const;//即使是普通对象，该函数中的const声明也将其视为const对象
private:
mutable size_t access_ctr;//可变成员
};
void Screen::some_member() const {
++access_ctr;
}
```

## 2 lambda表达式中使用值捕获但是想要在lambda中改变其值
采用值捕获的变量，如果想要在lambda中改变其值，需要在参数列表**之后**加上关键字 mutable
```cpp
size_t v1 = 42;
auto f = [v1] () mutable {return ++v1;};
v1 = 0;
auto j = f();//j为43
```