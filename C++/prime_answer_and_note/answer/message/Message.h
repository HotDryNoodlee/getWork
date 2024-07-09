#ifndef M_h_
#define M_H_
#include <string>
#include <set>
#include <vector>
using namespace std;
class Message {
    friend class Folder;
public:
    Message(const string& s = string()); { }
    Message(const Message&);
    Message operator=(const Message&);
    ~Message();
    void save(Folder&);
    void remove(Folder&);
    
private:
    string contents;
    set<Folder*> folders;
    void add_to_folders(const Message&);
    void remove_from_folders();
    void addFldr(Folder *f) { folders.insert(f); }
    void remFldr(Folder *f) { folders.erase(f); }
};
#endif