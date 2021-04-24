#ifndef BINARYQUERY_H
#define BINARYQUERY_H
#include "Query_base.h"
#include "Query.h"
#include <string>
class BinaryQuery : public Query_base {
protected:
    BinaryQuery(const Query &l, const Query &r, std::string s) : lhs(l), rhs(r), opSym(s) { }
    //抽象类BinaryQuery直接继承Query_base中的纯虚函数eval
    std::string rep() const {
        return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")";
    }
    Query lhs, rhs;
    std::string opSym;//运算符
};
#endif
