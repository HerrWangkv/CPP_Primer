#ifndef QUERY_H
#define QUERY_H
#include <string>
#include <memory>
#include "TextQuery.h"
#include "Query_base.h"
#include "WordQuery.h"
//接口类，用于隐藏继承体系

class Query {
    friend Query operator~(const Query &);
    friend Query operator&(const Query &, const Query &);
    friend Query operator|(const Query &, const Query &);
public:
    Query(const std::string &s) : q(new WordQuery(s)) { }
    QueryResult eval(const TextQuery &t) const {
        return q->eval(t);
    }
    std::string rep() const {
        return q->rep();
    }

private:
    //该构造函数不是explizit的
    Query(std::shared_ptr<Query_base> query) : q(query) { }
    std::shared_ptr<Query_base> q;
};

#endif