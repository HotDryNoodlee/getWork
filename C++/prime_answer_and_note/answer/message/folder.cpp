void Folder::add_to_Messages(const Folder &f)
{
    for (auto msg : f.messages)
        msg->addFldr(this);
}
void Folder::remove_from_Msgs()
{
    for (auto msg : messages)
        msg->remFldr(this);
}

Folder::Folder(const Folder &f) : messages(f.messages) { add_to_Messages(f); }

Folder::~Folder() { remove_from_Msgs(); }

Folder &Folder::operator=(const Folder &f)
{
    remove_from_Msgs();
    messages = f.messages;
    add_to_Messages(f);
    return *this;
}