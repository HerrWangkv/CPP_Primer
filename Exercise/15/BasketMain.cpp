#include <iostream>
#include "Quote.h"
#include "Bulk_quote.h"
#include "Basket.h"

using std::cout;
using std::endl;

int main() {
    Basket bk;
    //买10本，每本20.6，超过20本打7折
    for (unsigned i = 0; i != 10; ++i)
        bk.add_item(Bulk_quote("Bible", 20.6, 20, 0.3));
    //买10本，每本30.9，超过25本打6折
    for (unsigned i = 0; i != 10; ++i)
		bk.add_item(Bulk_quote("C++Primer", 30.9, 5, 0.4));
    //买10本，每本40.1，不参与优惠
	for (unsigned i = 0; i != 10; ++i)
		bk.add_item(Quote("CLRS", 40.1));
    bk.total_receipt(cout);
}