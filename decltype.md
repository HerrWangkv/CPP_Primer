# decltype特性
## 1 保留顶层const
```cpp
const int ci = 0, &cj = ci;
decltype(ci) x = 0; // x是 const int
```

## 2 decltype 与 引用
- decltype(variable)仅当variable这个**变量**本身是引用时结果才是引用
  ```cpp
  const int ci = 0, &cj = ci;
  decltype(ci) x = 0; // x是 const int
  decltype(cj) y = x; // y是 const int &
  ```
- decltype(expression)，如果expression是左值，结果即是引用；
  ```cpp
  int i = 42, *p = &i, &r = i;
  decltype(r) a = i; // a是 int &，必须初始化
  decltype(*p) b = i; // b也是 int &，必须初始化，*p为左值
  decltype(r + 0) c; // c是 int，尚未初始化
  ```
- decltype((variable))结果永远是引用
  ```cpp
  decltype(i) d; // d 是 int，尚未初始化
  decltype((i)) e = i; // e是 int &
  ```

## 3 decltype不会将数组名或函数名转换成指针
- 数组
  ```cpp
  int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  auto ia2(ia); // auto将ia视作指向第一个元素的指针，故ia2是一个整形指针，指向ia第一个元素
  decltype(ia) ia3 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // decltype仍将ia视作数组
  ```
- 函数
  ```cpp
  //函数
  bool lengthCompare(const string &, const string &);
  //func是函数类型，非函数名。形参列表是两个常字符串引用，输出bool
  typedef bool func(const string &, const string &);
  typedef decltype(lengthCompare) func2; // func 和 func2等价

  //funcP和funcP2是指向函数的指针
  typedef bool (*funcP)(const string &, const string &);
  typedef decltype(lengthCompare) *funcP2; // funcP 和 funcP2等价
  ```

## 4 函数返回值(数组指针/引用，函数指针)
- 返回指向数组的指针
  ```cpp
  int odd[] = {1, 3, 5, 7, 9};
  decltype(odd) *f(int i);
  ```
- 返回与数组绑定的引用
  ```cpp
  string s[10];
  decltype(s) &func();
  ```
- 返回指向函数的指针
  ```cpp
  int f(int*, int);
  decltype(f) *f1(int);
  ```

## 5 左值/右值/右值引用
```cpp
int i;
decltype(42);//int
decltype(i);//int&
decltype(std::move(i));//int &&
```