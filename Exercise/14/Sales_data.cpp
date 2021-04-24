#include "Sales_data.h"

//非成员函数
std::istream &operator>>(std::istream &is, Sales_data &item) {
    double price;
    is >> item.bookNo >> item.units_sold >> price;
    if (is)//不代表还有字符要输入，代表之前的输入没发生错误
        item.revenue = item.units_sold * price;
    //输入运算符必须处理输入可能失败的情况。
    else
        item = Sales_data();
    return is;
}
std::ostream &operator<<(std::ostream &os, const Sales_data &item) {
    os << item.isbn() << " " << item.units_sold << " "
       << item.revenue << " " << item.avg_price();
    return os;
}
Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs) {
    Sales_data sum = lhs;//拷贝构造函数
    sum += rhs;//+=此时尚未定义
    return sum;
}
bool operator==(const Sales_data &lhs, const Sales_data &rhs) {
    return lhs.isbn() == rhs.isbn() &&
           lhs.units_sold == rhs.units_sold &&
           lhs.revenue == rhs.revenue;
}
bool operator!=(const Sales_data &lhs, const Sales_data &rhs) {
    return !(lhs == rhs);
}
//委托构造函数
Sales_data::Sales_data(std::istream &is) : Sales_data(){
    is >> *this;
}

Sales_data& Sales_data::operator+=(const Sales_data &rhs) {
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}