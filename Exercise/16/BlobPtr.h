#ifndef BLOBPTR_H
#define BLOBPTR_H
#include "Blob.h"
#include <memory>
#include <vector>
//尽管已经include了头文件，仍然必须声明
template <typename T>
class Blob;
template <typename T>
class BlobPtr;
template <typename T>
bool operator==(const BlobPtr<T> &, const BlobPtr<T> &);
template <typename T>
bool operator!=(const BlobPtr<T> &, const BlobPtr<T> &);
template <typename T>
class BlobPtr
{
    friend bool operator==<T>(const BlobPtr<T> &, const BlobPtr<T> &);
public:
    BlobPtr() : curr(0) { }
    BlobPtr(Blob<T> &a, std::size_t sz = 0) : wptr(a.data), curr(sz) { }
    //必须重载以接受常量对象为了cbegin和cend
    BlobPtr(const Blob<T> &a, std::size_t sz = 0) : wptr(a.data), curr(sz) { }
    T &operator*() const
    {
        auto p = check(curr, "dereference past end");
        return (*p)[curr];//p指向vector
    }
    //在类模板内使用简化模板类名
    BlobPtr &operator++();//前置运算符
    BlobPtr &operator--();//前置运算符
    BlobPtr operator++(int);//后置运算符
    BlobPtr operator--(int);//后置运算符

private:
    std::shared_ptr<std::vector<T>> check(std::size_t, const std::string &) const;
    //保存一个weak_ptr，表示底层vector是否被销毁
    std::weak_ptr<std::vector<T>> wptr;
    std::size_t curr;//数组中的当前位置
};
//在类模板作用域外使用类模板名
template <typename T> BlobPtr<T>& BlobPtr<T>::operator++() {
    //前置需要检查
    check(curr, "Increment past end of BlobPtr");
    ++curr;
    return *this;
}
template <typename T> BlobPtr<T>& BlobPtr<T>::operator--() {
    //前置需要检查
    check(curr, "Decrement past begin of BlobPtr");
    --curr;
    return *this;
}
//对于后置运算符编译器会为int形参赋值0
template <typename T> BlobPtr<T> BlobPtr<T>::operator++(int) {
    //此处无需检查，调用前置运算符时会进行检查
    BlobPtr ret = *this;//此处又在类模板作用域内了，简化类名
    ++*this;
    return ret;
}
template <typename T> BlobPtr<T> BlobPtr<T>::operator--(int) {
    BlobPtr ret = *this;//此处又在类模板作用域内了，简化类名
    --*this;
    return ret;
}
template <typename T>std::shared_ptr<std::vector<T>> BlobPtr<T>::
check(std::size_t i, const std::string &msg) const {
    auto ret = wptr.lock();//返回wptr弱绑定的shared_ptr
    //如果ret为空指针，即vector不存在
    if (!ret)
        throw std::runtime_error("vector does not exist");
    //如果vector仍存在，但访问索引大于vector的size
    if ( i >= ret->size())
        throw std::out_of_range(msg);
    return ret;
}
//模板函数声明和定义都必须在头文件
template<typename T> bool operator==(const BlobPtr<T>&lhs, const BlobPtr<T>&rhs) {
    return (lhs.curr == rhs.curr);
}
template<typename T> bool operator!=(const BlobPtr<T>&lhs, const BlobPtr<T>&rhs) {
    return !(lhs == rhs);
}
#endif