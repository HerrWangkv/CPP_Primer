#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <initializer_list>
#include <exception>

class StrBlob {
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
int main() {
    StrBlob b1;
    {
        StrBlob b2 = {"a"};
        b1 = b2;
        b2.push_back("about");
        std::cout << "b2: " << b2.front() << " " << b2.back() << std::endl; // a about
    }
    std::cout << "b1: " << b1.front() << " " << b1.back() << std::endl; // a about
    b1.pop_back();
    b1.pop_back();
    std::cout << b1.front();//此时应报错
    return 0;
}