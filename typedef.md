# typedef 用法
## 1 基本类型
```cpp
typedef double a; //a是double的同义词
```
## 2 指针
```cpp
typedef double *b;//b是double*同义词
```
## 3 数组(及指针)
```cpp
typedef int int_array[4];//using int_array = int[4];

int_array *func(int i);//func函数返回一个指向含有4个整数的数组的指针
``` 
## 4 函数(及指针)
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
## 5 模板类型别名
假设Blob是一个模板类：
```cpp
typedef Blob<string> StrBlob
```
typedef只允许我们为模板的**某个实例**定义类型别名。如果想要为模板类定义类型别名，需要使用using。
