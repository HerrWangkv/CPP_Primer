#include "Query.h"
#include <iostream>

//调用时：cout << query << endl;
std::ostream &operator<<(std::ostream &os, const Query &query)
{
    return os << query.rep();
}
