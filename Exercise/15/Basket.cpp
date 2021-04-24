#include "Basket.h"
double print_total(std::ostream &os, const Quote &item, std::size_t n) {
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << std::endl;
    return ret;
}
double Basket::total_receipt(std::ostream &os) const {
    double sum = 0.0;
    //upper_bound返回一个迭代器，指向第一个关键字大于其参数的元素
    //调用upper_bound可以令我们跳过与当前关键字相同的所有元素
    for (auto iter = items.cbegin(); iter != items.cend(); iter = items.upper_bound(*iter)) {
        sum += print_total(os, **iter, items.count(*iter));
    }
    os << "Total Sale: " << sum << std::endl;
    return sum;
}