istream &read(istream &is, CPerson &per)
{
    is >> per.name >> per.address;
    return is;
}

ostream &print(ostream &os, const CPerson &per)
{
    os << per.get_name() << per.get_address();
    return os;
}