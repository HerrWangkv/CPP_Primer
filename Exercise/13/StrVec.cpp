#include "StrVec.h"
//类外定义static变量
allocator<string> StrVec::alloc;
//拷贝版本
void StrVec::push_back(const string &s)
{
    chk_n_alloc();//确保有空间容纳新元素
    alloc.construct(first_free++, s);
}
//移动版本
void StrVec::push_back(string &&s) {
    chk_n_alloc();
    alloc.construct(first_free++, std::move(s));
}
//拷贝指定范围，返回拷贝部分的首指针和尾后指针
pair<string *, string *> StrVec::alloc_n_copy(const string *b, const string *e) {
    //分配长度为e-b的未初始化的内存,data指向其首元素
    auto data = alloc.allocate(e - b);
    //unintialized_copy用来向未初始化内存拷贝，返回拷贝后第一元素
    return {data, std::uninitialized_copy(b, e, data)};
}

void StrVec::free() {
    if(elements) {
        std::for_each(elements, first_free, [this](const string &rhs) { alloc.destroy(&rhs); });
        /*
        for (auto p = first_free; p != elements;)
            //销毁初始化的数据，但未释放内存
            alloc.destroy(--p);
        */
        //释放内存
        alloc.deallocate(elements, cap - elements);
    }
}

StrVec::StrVec(const StrVec &s) {
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec& StrVec::operator=(const StrVec& rhs) {
    //防止自赋值
    auto newdata = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = newdata.first;
    first_free = cap = newdata.second;
    return *this;
}

//noexcept不是函数名，表示通知标准库我们的构造函数不抛出任何异常
StrVec::StrVec(StrVec &&s) noexcept : elements(s.elements), first_free(s.first_free),cap(s.cap) {
    //对源对象析构
    s.elements = s.first_free = s.cap = nullptr;
}


StrVec &StrVec::operator=(StrVec &&rhs) noexcept {
    //直接检查自赋值
    if (this != &rhs) {
        free();
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}

//分配新内存，移动原有元素
void StrVec::reallocate() {
    auto newcapacity = capacity() ? 2 * capacity() : 1;
    //注意此处不用alloc_n_copy()来拷贝，直接移动
    //分配新内存，newdata指向首元素
    auto newdata = alloc.allocate(newcapacity);
    //创建一个指向新内存首元素的指针的副本
    auto dest = newdata;
    auto elem = elements;
    for (size_t i = 0; i != size(); ++i) {
        //std::move表示希望使用string的移动构造函数
        alloc.construct(dest++, std::move(*elem++));
    }
    free();
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}