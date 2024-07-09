#ifndef CAPTER7_H_
#define CAPTER7_H_
#include <string>
#include <iostream>
using namespace std;


class CSales_data
{
friend CSales_data add(const CSales_data &lhs, const CSales_data &rhs);
friend istream &read(istream &is, CSales_data &item);
friend ostream &print(ostream &os, const CSales_data &item);


public:
    CSales_data(const string &book, const unsigned num, const double sellp, const double salep)
    :bookno(book), units_sold(num), prices(sellp), saleprices(salep) {
        if (prices) {
            discount = saleprices/prices;
        cout << "dafult" << endl;
        }
    };
    CSales_data():CSales_data("", 0, 0, 0){
        cout << "none" << endl;
    }
    CSales_data(const string &book) :CSales_data(book, 0, 0, 0) {
        cout << "book_no" << endl;
    }
    CSales_data(istream &is) : CSales_data()
    {
        read(is, *this);
        cout << "cin" << endl;
    }


private:
    string bookno;
    unsigned units_sold = 0;
    double prices = 0.0;
    double saleprices = 0.0;
    double discount = 0.0;

public:
    string isbn() const;
    CSales_data &combine(const CSales_data& );
    double avg_price() const;
};
#endif