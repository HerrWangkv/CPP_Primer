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
#endif