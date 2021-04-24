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

#endif