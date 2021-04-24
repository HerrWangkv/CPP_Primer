#ifndef ORQUERY_H
#define ORQUERY_H
#include "BinaryQuery.h"
#include "Query.h"

class OrQuery : public BinaryQuery {
    friend Query operator|(const Query &, const Query &);
    OrQuery(const Query &l, const Query &r) : BinaryQuery(l, r, "|") { }
    QueryResult eval(const TextQuery &) const;
    //OrQuery继承BinaryQuery定义的rep函数
};
//内联函数应定义在头文件中
inline Query operator|(const Query&lhs, const Query &rhs) {
    return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}
#endif