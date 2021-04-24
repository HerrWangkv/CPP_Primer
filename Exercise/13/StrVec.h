#ifndef STRVEC_H
#define STRVEC_H
#include <memory>
#include <string>
#include <utility>
#include <algorithm>
using std::allocator;
using std::pair;
using std::string;

class StrVec
{
public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) { }
    StrVec(const StrVec &);
    StrVec &operator=(const StrVec &);
    //noexcept不是函数名，表示通知标准库我们的构造函数不抛出任何异常
    StrVec(StrVec &&s) noexcept;
    StrVec &operator=(StrVec &&rhs) noexcept;
    ~StrVec() { free(); }
    void push_back(const string &);
    void push_back(string &&);
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }
    string *begin() const { return elements; }
    string *end() const { return first_free; }

private:
    static allocator<string> alloc;//用来装字符串
    string *elements;//指向第一个元素，类似于begin
    string *first_free;//指向(已初始化元素的)尾后元素，类似于end
    string *cap; //指向分配内存末尾之后的位置
    void free(); //销毁元素并释放内存
    void reallocate(); //分配新内存，拷贝原有元素
    //所有分配的内存都初始化了，分配新内存
    void chk_n_alloc() {
        if (size() == capacity())
            reallocate();
    }
    pair<string *, string *> alloc_n_copy(const string *, const string *);
};
#endif