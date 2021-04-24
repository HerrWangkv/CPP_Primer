#ifndef DISC_QUOTE_H
#define DISC_QUOTE_H
#include "Quote.h"

class Disc_quote : public Quote {
public:
    Disc_quote() = default;
    Disc_quote(const std::string &book, double price, std::size_t qty, double disc) : Quote(book, price), quantity(qty), discount(disc) { }
    //覆盖基类的函数版本以实现基于大量购买的折扣政策
    double net_price(std::size_t) const = 0;//声明为纯虚函数
    Disc_quote *clone() const & = 0;
    //将自己移动到新数据
    Disc_quote *clone() && = 0;

protected:
    std::size_t quantity = 0;//适用优惠政策的最低购买量
    double discount = 0.0;
};
#endif