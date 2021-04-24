#ifndef WORDQUERY_H
#define WORDQUERY_H
#include "Query_base.h"
#include "TextQuery.h"
#include <string>
//单纯的查找，实际调用TextQuery，
class WordQuery: public Query_base {
    friend class Query;
    WordQuery(const std::string &s) : query_word(s) { }
    QueryResult eval(const TextQuery &t) const {
        return t.findWord(query_word);
    }
    std::string rep() const  {
        return query_word;
    }
    std::string query_word;
};

#endif