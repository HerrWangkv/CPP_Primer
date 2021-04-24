#include "Message.h"

void swap(Message &lhs, Message &rhs) {
    using std::swap;
    for (auto fp : lhs.folders)
        fp->remMsg(&lhs);
    for (auto fp : rhs.folders)
        fp->remMsg(&rhs);
    swap(lhs.folders, rhs.folders);//swap(set&,set&)
    swap(lhs.contents, rhs.contents);//swap(string&,string&)
    for (auto fp : lhs.folders)
        fp->addMsg(&lhs);
    for (auto fp : rhs.folders)
        fp->addMsg(&rhs);
    std::cout << "Swap of messages succeed" << std::endl;
    std::cout << std::endl;
}

Message::Message(const Message &msg) : contents(msg.contents), folders(msg.folders) {
    add_to_Folders(msg);
}

Message &Message::operator=(const Message &msg){
    remove_from_Folders();//删除当前所在Folders
    contents = msg.contents;
    folders = msg.folders;
    add_to_Folders(msg);
    return *this;
}
/*
//效果等价，但时间复杂度较高
Message& Message::operator=(Message msg) {
    swap(*this, msg);
    return *this;
}
*/

Message::~Message() {
    remove_from_Folders();
}

void Message::save(Folder &f) {
    folders.insert(&f);
    f.addMsg(this);
}

void Message::remove(Folder &f) {
    folders.erase(&f);
    f.remMsg(this);
}

void Message::add_contents(const string &newStr) {
    contents = contents + " " + newStr;
}

void Message::add_to_Folders(const Message &msg) {
    for (auto fp : msg.folders) {
            fp->addMsg(this);
    }
}

void Message::remove_from_Folders() {
    for (auto fp : folders) {
        fp->remMsg(this);
    }
}
