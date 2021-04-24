#include "NotQuery.h"
#include <memory>
#include "TextQuery.h"
#include <set>

inline Query operator~(const Query &operand) {
    return std::shared_ptr<Query_base>(new NotQuery(operand));
}

QueryResult NotQuery::eval(const TextQuery& text) const {
    //逻辑非之前能查找到该单词的行
    auto result = query.eval(text);
    auto ret_lines = std::make_shared<lineNo>();
    auto sz = result.get_file()->size();
    auto beg = result.begin(), end = result.end();
    for (size_t n = 0; n != sz; ++n) {
        //beg表示遍历处之后含有该单词的第一行
        if (beg == end || *beg != n)
            ret_lines->insert(n);
        else if (beg != end)
            ++beg;
    }
    return QueryResult(rep(), ret_lines, result.get_file());
}