#ifndef BULK_QUOTE_H
#define BULK_QUOTE_H
#include "Quote.h"

class Bulk_quote : public Quote {
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string &book, double p, std::size_t qty, double disc) : Quote(book, p), quantity(qty), discount(disc) { }
    //覆盖基类的函数版本以实现基于大量购买的折扣政策
    double net_price(std::size_t cnt) const override {
        if (cnt >= quantity)
            return cnt * (1 - discount) * price;
        else
            return cnt * price;
    }
    //将自己拷贝给新分配的对象
    Bulk_quote *clone() const & { return new Bulk_quote(*this); }
    //将自己移动到新数据
    Bulk_quote *clone() && { return new Bulk_quote(std::move(*this)); }

private:
    std::size_t quantity;
    double discount;
};
#endif