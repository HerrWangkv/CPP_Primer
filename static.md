# static用法
## 1 局部静态对象
将局部变量定义成static类型，从而保证生命周期贯穿函数调用及之后的时间：
```cpp
//统计函数被调用多少次
size_t count_calls() {
    static size_t ctr = 0;//仅控制流第一次经过ctr定义时初始化，后面不再初始化
    return ++ctr;
}
int main() {
    for (size_t i = 0; i != 10; ++i)
    cout << count_calls() << endl; //最终输出1-10
    return 0;
}
```
## 2 类内静态成员
有时候类的成员与类本身直接相关，而不是与类的各个对象保持关联，也就说所有该类对象共享这个成员。
  ```cpp
  class Account {
  public:
    void calculate() { amount += amount * interestRate; }
    static double rate() { return interestRate; }
    static void rate(double);
  private:
    std::string owner;
    double amount;
    static double interestRate;
    static double initRate();
  };

  //该函数的目的是对interestRate进行初始化，而是赋值
  void Account::rate(double newRate) {
    interestRate = newRate;
  }
  static double Account::initRate() { return 0.3; }
  //必须在类外定义并初始化静态数据成员，且不能在类外重复static
  //从类名开始该语句剩余部分已经在类作用域内了，不用再标注Account::initRate()
  double Account::interestRate = initRate();
  ```
  1. 静态函数/数据成员声明之前加上关键字static使得其与类而非对象关联在一起
  2. 类作用域外使用 类名+作用域运算符(::)直接访问 或者 该类的对象/引用/指针+成员访问符(. / ->)访问静态函数/数据成员
  3. 而成员函数不用通过作用域运算符就能直接使用静态成员
  4. **静态函数成员**可以在类内定义，也可以在类外定义。但在类外部定义静态成员函数时，不能重复static关键字。static函数体内不能使用this指针。但不是所用需要用到静态成员的函数都必须声明为static。
  5. **静态数据成员**不属于类的任何一个对象，故他们不能由类的构造函数初始化。此外我们 **一般情况下** 不能对静态数据成员进行类内初始化，**需要在类的外部定义和初始化**每个静态数据成员，且一个静态数据成员只能定义一次(但可以多次赋值)。类外定义静态数据成员也不能重复static关键字。确保对象仅被定义一次的最佳方法是把静态数据成员的定义与其他费内敛函数的定义放在同一个文件中。
  6. 静态数据成员可以是[不完全类型](#33-类类型)(仅声明未定义的类类型)，而非静态成员不可以。特别的，静态数据成员的类型可以就是它所属的类类型。
  ```cpp
  class Bar {
  public:
    ...
  private:
    static Bar mem1;//正确
    Bar *mem2;//正确
    Bar mem3;//错误
  };
  ```
  7. 静态成员可以作为类的函数成员的默认实参，而非静态成员不可以。