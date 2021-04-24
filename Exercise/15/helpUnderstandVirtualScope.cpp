#include <iostream>
using namespace std;

class  Base {
public:
    virtual int fcn() {
        cout << 1 << endl;
        return 1;
    }
};
class D1 : public  Base {
public:
    //Base::fcn()被隐藏，但同时由于没有覆盖，被继承
    int fcn(int)//与虚函数Base::fcn()的形参列表不同
    {
        cout << 2 << endl;
        return 2;
    }
    virtual void f2()//新的虚函数
    {
        cout << 3 << endl;
    }
};
class D2 : public D1  {
public:
    int fcn(int)//非虚函数，隐藏了D1::fcn(int)
    {
        cout << 4 << endl;
        return 4;
    }
    int fcn()//覆盖了Base::fcn()
    {
        cout << 5 << endl;
        return 5;
    }
    void f2()//覆盖了D1的虚函数f2
    {
        cout << 6 << endl;
    }
};

int main() {
    Base bobj;
    D1 d1obj;
    D2 d2obj;
    //静态类型为Base，只能找到虚函数，但实际调用版本取决于动态类型
    Base *bp1 = &bobj, *bp2 = &d1obj, *bp3 = &d2obj;
    bp1->fcn();//虚调用，调用Base::fcn
    bp2->fcn();//虚调用，调用Base::fcn，通过基类调用隐藏的虚函数
    bp3->fcn();//虚调用，调用D2::fcn (动态绑定)

    D1 *d1p = &d1obj;
    D2 *d2p = &d2obj;
    //bp2->f2();//错误，静态类型是Base，f2不可见
    d1p->f2();//虚调用，调用D1::f2 （静态动态类型相同）
    d2p->f2();//虚调用，调用D2::f2 (动态绑定)
    //不同静态类型，动态类型都是D2
    Base *p1 = &d2obj;
    D1 *p2 = &d2obj;
    D2 *p3 = &d2obj;
    //p1->fcn(42);//错误，静态类型是Base，Base::fcn函数不接受参数
    p2->fcn(42);//静态绑定，调用D1::fcn(int)
    p3->fcn(42);//静态绑定，调用D2::fcn(int)

    //d1p->fcn();//错误，Base::fcn()被隐藏
    return 0;
}