#ifndef PERSON_H_
#define PERSON_H_



class CPerson
{
private:
    string pname;
    string paddress;

public:
    CPerson() = default;
    CPerson(const string &name, const string &add) {
        pname = name;
        paddress = add;
    }
    CPerson(istream &is) { is >> *this; }


public:
    string get_name() const { return pname; }
    string get_address() const { return paddress; }
};





#endif