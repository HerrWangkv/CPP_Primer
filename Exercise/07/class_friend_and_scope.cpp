#include <iostream>
#include <vector>
using namespace std;

class A;
class B {
public:
	B(A *g, A &h, vector<A> j) :  b(g), c(h), d(j) { }
	void append(A);

private:
	//A a;//报错，不允许使用不完全类型
	A *b;//正确
	A &c;//正确
	vector<A> d;//正确，默认初始化为空vector，没有真实创建A对象
	//vector<A> e{A(2)};//报错，不能真实创建
	static A f;//正确，静态成员可以定义为不完全类型
};

class A {
	friend void B::append(A);//此处也可将B类声明为A的友元
	//可以在类内定义是其友元的非成员函数
	friend void print(A a) { cout << "objA: " << a.value << endl; }

public:
	explicit A(int i) : value(i) { }
private :
	int value;
};
//作为A的友元(必须在A中的友元声明前声明)，又要使用A对象(必须在A定义后定义)
void B::append(A obj){
	d.push_back(obj);
	cout << "*b: " << b->value << endl;
	cout << "c: " << c.value << endl;
	cout << "d: ";
	for (auto i : d) {
		cout << i.value << " ";
	}
	cout << endl;
	cout << "f: " << f.value << endl;
}
//定义并初始化静态数据成员
A B::f(1);
//必须声明print
void print(A a);


int main(){
	A objA(2);
	print(objA);
	B objB(&objA, objA, {objA});
	objB.append(A(3));
	return 0;
}