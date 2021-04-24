#ifndef MESSAGE_H
#define MESSAGE_H
#include <set>
#include <string>
#include <iostream>
#include "Folder.h"
using std::set;
using std::string;

class Folder;
class Message;//必须声明，为了swap能够理解
void swap(Message &, Message &);
class Message
{
    friend class Folder;
    friend void swap(Message &, Message &);
    friend void swap(Folder &, Folder &);

public:
    //folders被隐式初始化为空集合
    explicit Message(const string &str = "") : contents(str) { }
    Message(const Message &);
    Message &operator=(const Message &);
    //Message &operator=(Message);
    ~Message();
    void save(Folder &);
    void remove(Folder &);
    void add_contents(const string&);
    void print() { std::cout << contents << std::endl; }

private:
    //消息文本
    string contents;
    //保存指向本Message所在Folder的指针的set
    set<Folder *> folders;
    //创建副本时的辅助函数，加入到原对象的所有Folder中
    void add_to_Folders(const Message&);
    //销毁的辅助函数，从所有加入的Folder删除该Message
    void remove_from_Folders();
};
#endif