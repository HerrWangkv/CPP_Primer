#ifndef BASKET_H
#define BASKET_H
#include <memory>
#include <set>
#include <iostream>
#include "Quote.h"
class Basket {
public:
    //Basket使用合成的默认构造函数和拷贝控制成员
    
    //拷贝给定对象
    void add_item(const Quote &sale) {
        //会按照isbn升序插入
        items.insert(std::shared_ptr<Quote>(sale.clone()));
    }
    //移动给定对象
    void add_item(Quote && sale) {
        //注意变量sale为左值
        items.insert(std::shared_ptr<Quote>(std::move(sale).clone()));
    }
    double total_receipt(std::ostream &) const;

private:
    static bool compare(const std::shared_ptr<Quote> &lhs, const std::shared_ptr<Quote> &rhs) {
        return lhs->isbn() < rhs->isbn(); 
    }
    //compare函数用于指定multiset中排序顺序,使用大括号防止被认定为函数成员的声明
    std::multiset<std::shared_ptr<Quote>, decltype(compare) *> items{compare};
};
#endif