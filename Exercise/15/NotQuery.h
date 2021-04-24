#ifndef NOTQUERY_H
#define NOTQUERY_H
#include "Query_base.h"
#include "Query.h"
#include <string>
class NotQuery : public Query_base {
    friend Query operator~(const Query &);
    NotQuery(const Query &q) : query(q) { }
    QueryResult eval(const TextQuery &) const;
    std::string rep() const { return "~(" + query.rep() + ")"; }
    Query query;
};
//内联函数应定义在头文件中
inline Query operator~(const Query &operand) {
    return std::shared_ptr<Query_base>(new NotQuery(operand));
}

#endif