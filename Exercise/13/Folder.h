#ifndef FOLDER_H
#define FOLDER_H
#include <set>
#include "Message.h"
#include <iostream>
using std::cout;
using std::endl;
using std::set;

class Message;
class Folder;//必须声明，为了swap能够理解
void swap(Folder &, Folder &);
class Folder
{
    friend class Message; 
    friend void swap(Folder &, Folder &);
    friend void swap(Message &lhs, Message &rhs);

public:
    Folder() = default;
    Folder(const Folder &f);
    Folder &operator=(const Folder &);
    ~Folder();
    void print();

private:
    set<Message *> msgs;
    //不允许用户操纵Folder添加信息
    void addMsg(Message *msg) { msgs.insert(msg); }
    void remMsg(Message *msg) { msgs.erase(msg); }
    void add_to_Msgs(const Folder &);
    void remove_from_Msgs();
};
#endif