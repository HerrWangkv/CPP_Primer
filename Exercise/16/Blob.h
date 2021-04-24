#ifndef BLOB_H
#define BLOB_H
#include <memory>
#include <vector>
#include <initializer_list>

template <typename T> class Blob {
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

#endif