#include "Folder.h"
void swap(Folder &lhs, Folder &rhs)
{
    using std::swap;
    for (auto mp : lhs.msgs)
        //mp->remove(lhs); //错误，因为remove函数会删除msgs中内容
        mp->folders.erase(&lhs);
    for (auto mp : rhs.msgs)
        mp->folders.erase(&rhs);
    swap(lhs.msgs, rhs.msgs);
    for (auto mp : lhs.msgs)
        mp->save(lhs);//save函数没问题是因为set不会再添加已经添加过的元素
    for (auto mp : rhs.msgs)
        mp->save(rhs);
    std::cout << "Swap of folders succeed" << std::endl;
    std::cout << std::endl;
}

Folder::Folder(const Folder &f) : msgs(f.msgs) {
    add_to_Msgs(f);
}

Folder &Folder::operator=(const Folder &f) {
    remove_from_Msgs();
    msgs = f.msgs;
    add_to_Msgs(f);
    return *this;
}

Folder::~Folder() {
    remove_from_Msgs();
}

void Folder::print() {
    for (auto mp : msgs)
        cout << mp->contents << endl;
    cout << endl;
}

void Folder::add_to_Msgs(const Folder &f) {

    for (auto mp : f.msgs) {
        mp->folders.insert(this);
    }
}
//同时删除Folder和Message
void Folder::remove_from_Msgs() {
    for (auto mp : msgs) {
        mp->folders.erase(this);
    }
}