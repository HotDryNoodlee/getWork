#include "Message.h"
#include <string>
using namespace std;


// void Message::Message


Message::Message(const Message& M) :
    contents(M.contents),
    folders(M.folders) {
    add_to_folders(M)
}
Message& Message::operator=(const Message& M) { 
    remove_from_folders();
    contents = M.contents;
    folders = M.contents;
    add_to_folders(M);
    return *this;
}
Message::~Message() {
    remove_from_folders();
}

void Message::save(Folder& F) {
    folders.insert(&F);
    F.addmsg(this);
}

void Message::remove(Folder& F) {
    folders.erase(&F);
    F.remmsg(this);
}

void Message::add_to_folders(const Message& M) {
    for (auto f : M.folders)
        f->add(this);
}

void Message::remove_from_folders() {
    for(auto f : folders)
        f->remmsg(this);
}


void swap(Message& m1, Message& m2) {
    for(auto f : m1.folders) {
        f->remmeg(&m1);
    }
    for(auto f : m2.folders) {
        f->remmeg(&m2);
    }
    swap(m1.contents, m2.contents);
    swap(m1.folders, m2.folders);
    for(auto f : m1.folders) {
        f->addmeg(&m1);
    }
    for(auto f : m2.folders) {
        f->addmeg(&m2);
    }
}