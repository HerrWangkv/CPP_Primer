#include <iostream>
#include <fstream>
#include <string>
#include "Query.h"
#include "WordQuery.h"
#include "NotQuery.h"
#include "BinaryQuery.h"
#include "AndQuery.h"
#include "OrQuery.h"

using std::cout;
using std::endl;


inline Query operator&(const Query&lhs, const Query &rhs) {
    return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

inline Query operator|(const Query&lhs, const Query &rhs) {
    return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

inline Query operator~(const Query &operand) {
    return std::shared_ptr<Query_base>(new NotQuery(operand));
}

int main() {
    Query q1 = Query("hair") & Query("Daddy");
    Query q2 = Query("hair") | Query("Daddy");
    Query q3 = ~Query("hair");
    std::ifstream infile("./storyDataFile.txt");
    TextQuery tq(infile);
    q1.eval(tq).print(cout);
    cout << endl;
    q2.eval(tq).print(cout);
    cout << endl;
    q3.eval(tq).print(cout);
    return 0;
}