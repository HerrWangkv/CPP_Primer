#include "Query.h"
#include <sstream>

TextQuery::TextQuery(std::ifstream &infile) : text(new std::vector<std::string>) {
    std::string line;
    std::size_t row = 0;
    while (std::getline(infile, line)) {
        text->push_back(line);
        std::string word;
        std::istringstream inword(line);
        while(inword >> word) {
            //删除首尾符号
            while(!isalpha(word.front()))
                word.erase(word.begin());
            while (!isalpha(word.back()))
                word.pop_back();
            //如果第一次遇见这个词，该指针为空
            if (!lineNumber[word])
                //分配一个新的set内存
                lineNumber[word].reset(new lineNo);
            lineNumber[word]->emplace(row);
        }
        ++row;
    }
    /*
    for (auto i : lineNumber) {
        std::cout << i.first << ": ";
        for (auto j : (*i.second)) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
    */
}

QueryResult TextQuery::findWord(const std::string &word) {
    //局部static对象，指向一个空set
    static std::shared_ptr<lineNo> nodata(new lineNo);
    if (lineNumber.find(word) == lineNumber.end())
        return QueryResult(word, nodata, text);
    return QueryResult(word, lineNumber[word], text);
}

std::ostream & QueryResult::print(std::ostream& os) {
    os << word << " occures " << lines->size() << " time(s)" << std::endl;
    for (auto num : *lines) {
        os << "\t(line " << num + 1 << ") "
            << *(text->begin() + num) << std::endl;
    }
    return os;
}