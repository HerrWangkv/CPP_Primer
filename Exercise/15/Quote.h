#ifndef QUOTE_H
#define QUOTE_H
#include <string>
class Quote {
public:
    Quote() = default;
    Quote(const std::string &book, double sales_price) : bookNo(book), price(sales_price) { }
    std::string isbn() const { return bookNo; }
    virtual double net_price(std::size_t n) const { return n * price; }
    //将自己拷贝给新分配的对象
    virtual Quote *clone() const & { return new Quote(*this); }
    //将自己移动到新数据
    virtual Quote *clone() && { return new Quote(std::move(*this)); }
    virtual ~Quote() = default; //基类一般都定义一个虚析构函数
private:
    std::string bookNo; //不能被派生类直接访问
//protected成员在private基础上还能被子类函数访问
protected:
    double price = 0.0; //未打折原价
};
#endif