#ifndef BLOB_H
#define BLOB_H
#include <memory>
#include <vector>
#include <initializer_list>
#include "BlobPtr.h"

//尽管已经include了头文件，仍然必须声明
template <typename>
class BlobPtr;
template <typename>
class Blob;
//模板函数
template <typename T>
bool operator==(const Blob<T> &, const Blob<T> &);

template <typename T>
class Blob
{
    //每个Blob实例仅将访问权限授予用相同类型实例化的BlobPtr和相等运算符
    //<T>表示其也是模板
    friend class BlobPtr<T>;
    friend bool operator==<T>(const Blob<T> &, const Blob<T> &);

public:
    //T表示Blob保存的元素类型
    typedef T value_type;
    //此处加typename是因为T未知，编译器不知道std::vector<T>::size_type是变量还是类型
    typedef typename std::vector<T>::size_type size_type;
    Blob();
	Blob(std::initializer_list<T>);
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    void push_back(const T &t) { data->push_back(t); }
    void push_back(T &&t) { data->push_back(std::move(t)); }
    void pop_back();
    T &front();
    T &back();
    T &operator[](size_type);
    //常量对象仅能被常量引用绑定
    const T &front() const;
    const T &back() const;
    const T &operator[](size_type) const;
    //注意begin和end返回的都是右值
    BlobPtr<T> begin() { return BlobPtr<T>(*this); }
    BlobPtr<T> end() { return BlobPtr<T>(*this, size()); }
    const BlobPtr<T> cbegin() const {
        const BlobPtr<T> ret(*this);
        return ret;
    }
    const BlobPtr<T> cend() const {
        const BlobPtr<T> ret(*this, size());
        return ret;
    }

private:
    std::shared_ptr<std::vector<T>> data;
    //若data[i]无效，抛出msg
    void check(size_type, const std::string &) const;
};

template <typename T> Blob<T>::Blob() : data(std::make_shared<std::vector<T>>()) { }
template <typename T> Blob<T>::Blob(std::initializer_list<T> il) : data(std::make_shared<std::vector<T>>(il)) { }
template <typename T> void Blob<T>::pop_back() {
    check(0, "pop back on empty Blob");
    data->pop_back();
}
template <typename T> T& Blob<T>::front() {
    check(0, "front on empty Blob");
    return data->front();
}
template <typename T> T& Blob<T>::back() {
    check(0, "back on empty Blob");
    return data->back();
}
template <typename T> T& Blob<T>::operator[](size_type i) {
    check(i, "subscript out of range");
    return (*data)[i];
}
template <typename T> const T& Blob<T>::front() const {
    check(0, "front on empty Blob");
    return data->front();
}
template <typename T> const T& Blob<T>::back() const{
    check(0, "back on empty Blob");
    return data->back();
}
template <typename T> const T& Blob<T>::operator[](size_type i) const {
    check(i, "subscript out of range");
    return (*data)[i];
}
template <typename T> 
void Blob<T>::check(size_type i, const std::string &msg) const {
    if (i >= data->size())
        throw std::out_of_range(msg);
}
//模板函数声明和定义都必须在头文件
template <typename T>
bool operator==(const Blob<T> &lhs, const Blob<T> &rhs) {
    return (lhs.data == rhs.data);
}

#endif