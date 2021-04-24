#include <iostream>
#include "Message.h"
#include "Folder.h"
using std::cout;
using std::endl;

int main()
{
    Folder f1;
    Message m1("Hello World"), m2(m1), m3("I hate cpp");
    m2.add_contents("cpp");
    m1.save(f1);
    m2.save(f1);
    Folder f2 = f1;
    m3.save(f2);
    m1.remove(f2);
    cout << "Folder 1: " << endl;
    //f1此时包含m1 m2
    f1.print();
    cout << "Folder 2: " << endl;
    //f1此时包含m2 m3
    f2.print();

    swap(m1, m2);
    swap(f1, f2);
    
    cout << "Folder 1 after swapping: " << endl;
    //f1此时包含原m1 m3
    f1.print();
    cout << "Folder 2 after swapping: " << endl;
    //f1此时包含原m1 m2
    f2.print();
    return 0;
}