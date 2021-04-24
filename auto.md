# auto 特性
## 1 auto定义的变量必须有初始值
## 2 一条声明语句只能由一个基本数据类型（指针，引用不算）
```cpp
auto i = 0, *p = &i; //i是整数，p是整型指针
```
## 3 auto一般会忽略掉顶层const，保留底层const
```cpp
int i = 0;
const int ci = i, &cr = ci;
auto b = ci; // b是int
auto c = cr; // c是int
auto d = &i; // d是一个int*
auto e = &ci; // e是一个指向整数常量的指针(const int *)
const auto f = ci; // f是const int
auto &g = ci; // g是整型常量引用，const int &
auto &h = 42; //报错，非常量引用不能绑定常量
const auto &j = 42; // 常量引用可以绑定常量
```
## 4 范围for
- 使用范围for循环进行遍历1(也可用于其他序列,但不可改变其元素)
  ```cpp
  string str;
  for (auto c : str)
    cout << c << endl;
  ```
- 使用范围for循环进行遍历2(也可用于其他序列,使用引用后可改变其元素)
  ```cpp
  string str;
  for (auto &c : str)
    c = toupper(c);
  ```
## 5 auto 会将数组名自动替换成一个指向首元素的指针(跟大部分程序一样)
```cpp
int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
auto ia2(ia); // auto将ia视作指向第一个元素的指针，故ia2是一个整形指针，指向ia第一个元素
decltype(ia) ia3 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // decltype仍将ia视作数组
```
## 6 auto用于尾置返回类型trailing return type
- 返回指向数组的指针
  ```cpp
  auto funct(int i) -> int(*)[10];
  ```
- 返回与数组绑定的引用
  ```cpp
  auto func() -> string(&)[10]
  ```
- 返回指向函数的指针
  ```cpp
  auto f1(int) -> int (*) (int*, int);
  ```