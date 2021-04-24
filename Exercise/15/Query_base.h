#ifndef QUERY_BASE_H
#define QUERY_BASE_H
#include "TextQuery.h"
#include <string>
//抽象基类不需要public成员
class Query_base {
    friend class Query;
protected:
    using lineNo = TextQuery::lineNo;
    virtual ~Query_base() = default;
private:
    //返回一个QueryResult对象，表示查询结果
    virtual QueryResult eval(const TextQuery &) const = 0;
    //
    virtual std::string rep() const = 0;
};
#endif