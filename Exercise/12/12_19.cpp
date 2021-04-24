#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <initializer_list>
#include <exception>

class StrBlobPtr;

class StrBlob {
    friend class StrBlobPtr;
public:
    typedef std::vector<std::string>::size_type size_type;
    StrBlob();
    StrBlob(std::initializer_list<std::string> il);
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    //添加删除元素
    void push_back(const std::string &t) { data->push_back(t); }
    void pop_back();
    //元素访问
    std::string &front();
    std::string &back();
    //常量对象仅能被常量引用绑定
    const std::string &front() const;
    const std::string &back() const;
    //返回StrBlobPtr，因此提前声明StrBlobPtr,且此处不能定义
    StrBlobPtr begin();
    StrBlobPtr end();

private:
    //此成员会记录有多少个StrBlob共享相同的vector，最后一个使用者被销毁时释放vector
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_type i, const std::string &msg) const;
};

StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()) {}
StrBlob::StrBlob(std::initializer_list<std::string> il) : data(std::make_shared<std::vector<std::string>>(il)) {}
void StrBlob::check(size_type i, const std::string &msg) const {
    //访问元素越界
    if (i >= data->size())
        throw std::out_of_range(msg);
}
void StrBlob::pop_back() {
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}
std::string& StrBlob::front() {
    check(0, "front on empty StrBlob");
    return data->front();
}
std::string& StrBlob::back() {
    check(0, "back on empty StrBlob");
    return data->back();
}
const std::string& StrBlob::front() const{
    check(0, "front on empty StrBlob");
    return data->front();
}
const std::string& StrBlob::back() const{
    check(0, "back on empty StrBlob");
    return data->front();
}

//保存一个weak_ptr，指向StrBlob的data成员
class StrBlobPtr {
    friend bool equal(const StrBlobPtr &a, const StrBlobPtr &b);
public: 
    StrBlobPtr() : curr(0) { }
    StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) { }
    std::string &deref() const;//解引用
    StrBlobPtr &incr();//前缀递增

private:
    //若检查成功，返回一个指向vector的shared_ptr
    std::shared_ptr<std::vector<std::string>>check(std::size_t, const std::string&) const;
    //用来检查vector是否报销毁
    std::weak_ptr<std::vector<std::string>> wptr;
    std::size_t curr;//在数组中的当前位置
};
std::shared_ptr<std::vector<std::string>> StrBlobPtr::check (std::size_t i, const std::string &msg) const {
    auto ret = wptr.lock();
    //如果ret为空指针，即vector不存在
    if (!ret)
        throw std::runtime_error("vector does not exist");
    //如果vector仍存在，但访问索引大于vector的size
    if ( i >= ret->size())
        throw std::out_of_range(msg);
    return ret;
}
std::string& StrBlobPtr::deref() const {
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}
StrBlobPtr& StrBlobPtr::incr() {
    //如果curr已经超过范围，则报错
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}
//定义完StrBlobPtr类，才能具体定义返回值为这个类型的函数
StrBlobPtr StrBlob::begin() { return StrBlobPtr(*this); }
StrBlobPtr StrBlob::end() { return StrBlobPtr(*this, data->size()); }
//类似重载运算符==
bool equal(const StrBlobPtr &a, const StrBlobPtr &b) {
    return (a.curr == b.curr);
}

int main() {
    std::string word;
    StrBlob sb;
    //windows下，用ctrl+z跳出循环
    while(std::cin >> word) {
        sb.push_back(word);
    }
    //StrBlobPtr类似StrBlob的迭代器
    for (StrBlobPtr beg = sb.begin(); !equal(beg, sb.end()); beg.incr()) {
        std::cout << beg.deref() << " ";
    }
}