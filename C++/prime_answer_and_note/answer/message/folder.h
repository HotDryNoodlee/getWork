#ifndef F_h_
#define F_H_
#include <string>
#include <set>
#include <vector>
using namespace std;
class Message;
class Folder {
public:
    Folder();
    Folder(const Folder&);
    Folder operator=(const Folder&);
    ~Folder();
private:
    set<Message*> messages;
    void addmsg(Message *m) { messages.insert(m); }
    void remmsg(Message *m) { messages.earse(m); }
    void remove_from_Msgs();
    void add_to_Messages(const Folder&);
};
#endif