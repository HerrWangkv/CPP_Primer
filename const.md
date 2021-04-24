# const 用法，详见[const 限定符](./02_变量和基本类型.md#4-const-限定符)
## 顶层const
1. 基本数据类型 
   - const对象 可以被 同类型 非const对象 初始化
   - const对象 可以用于初始化 同类型 非const对象
    ```cpp
    int i = 42;
    const int j = i;
    int k = j;
    ```
2. 常量指针
   
   常量指针指向的地址不变，但被指对象的值可以变。
    ```cpp
    int i = 0;
    int *const cptr = &i; // cptr一直指向i
    *cptr = 42;
    ```

## 底层const
1. 常量引用
   - const对象 不能被 非常量引用 绑定
   - const引用 可以绑定 同类型 或 其他类型但可以进行类型转换的 非常量(有可能改变值)
   - 常量引用可以绑定字面常量
    ```cpp
    double pi = 3.14;//
    const int &rpi = pi; //正确，但rpi=3，且不可改变
    int &rpi2 = rp1; // 报错
    const int &r = 42;// 正确，常量引用可以绑定字面常量
    int &r2 = 42;// 报错
    ```
2. 指向常量的指针
   - 普通指针 不能指向 常量
   - 指向常量的指针 可以指向 同类型的 非常量
   - 指向常量的指针可以更改所指对象
    ```cpp
    double pi = 3.14;
    const double *cptr1 = &pi; //定义并初始化一个 指向常量的指针
    const int *cptr2 = &pi; //报错，跟引用略有区别，数据类型不能变
    double *cptr3 = cptr1; // 报错

    void print(const int *beg, const *int end) {
      while (beg != end)
        cout << *beg++ <<endl; //正确，可以更换所指对象
    }
    ```

3. [const_iterator](./03_字符串_向量和数组.md#41-使用迭代器)

   如果容器是const，迭代器只能用const_iterator，此时对容器只读不写。普通容器既可用const_iterator也可用iterator
   
4. 类的 const 成员函数(将非常量类对象暂时视为常量类对象，除可变成员外均不可改变)
   ```cpp
   std::string isbn() const { return this->bookNo; }//等价
   ```
   紧随参数列表之后的const关键字修改了隐式this指针的类型:从**指向非常量的常量指针**到指向**常量的常量指针**。
   
   常量对象以及常量对象的引用或指针都**只能调用常量成员函数**。

5. 动态分配的const对象

   分配出指向常量的指针。内置类型的const对象不能默认初始化，定义了默认构造函数的类类型可以默认初始化
    ```cpp
    const int *pci = new const int(1024);
    const string *pcs = new const string;
    ```
