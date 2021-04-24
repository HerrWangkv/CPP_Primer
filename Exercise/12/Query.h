#ifndef QUERY_H
#define QUERY_H

#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <memory>
#include <iostream>

class QueryResult;
class TextQuery {
public:
    using lineNo = std::set<std::size_t>;
    TextQuery(std::ifstream &infile);
    QueryResult findWord(const std::string &word);

private:
    std::shared_ptr<std::vector<std::string>> text;
    std::map<std::string, std::shared_ptr<lineNo>> lineNumber;
};

class QueryResult {
public:
    QueryResult(const std::string str,
                std::shared_ptr<TextQuery::lineNo> lset,
                std::shared_ptr<std::vector<std::string>> txt) : word(str), lines(lset), text(txt) { }
    std::ostream &print(std::ostream &os);

private:
    std::string word;//待查询单词
    std::shared_ptr<TextQuery::lineNo> lines;//word出现的行号集合
    std::shared_ptr<std::vector<std::string>> text;//输入文件
};

#endif