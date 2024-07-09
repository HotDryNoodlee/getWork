#include <string>
#include <iostream>
#include "saleclass.h"
using namespace std;

// CSales_data::CSales_data(const std::string &book, const unsigned num, const double sellp, const double salep)
// {
//     bookno = book;
//     units_sold = num;
//     prices = sellp;
//     saleprices = salep;
//     if (prices != 0)
//         discount = saleprices / prices; // 计算实际折扣
// }



CSales_data add(const CSales_data &lhs, const CSales_data &rhs)
{
    CSales_data sum = lhs;
    sum.combine(rhs);
    return sum;
}

istream &read(istream &is, CSales_data &item)
{
    is >> item.bookno >> item.units_sold >> item.prices >> item.saleprices;
    return is;
}

ostream &print(ostream &os, const CSales_data &item)
{
    os << item.isbn() << " " << item.units_sold << " " << item.prices << " " << item.saleprices << " " << item.discount;
    return os;
}

string CSales_data::isbn() const { return bookno; }

CSales_data& CSales_data::combine(const CSales_data &rhs)
{
    units_sold += rhs.units_sold;
    saleprices = (rhs.saleprices * rhs.units_sold + saleprices * units_sold) / (rhs.units_sold + units_sold);
    if (prices != 0)
    {
        discount = saleprices / prices;
        return *this;
    }
    else {
        discount = 0.0;
        return *this;
    }
}


inline double CSales_data::avg_price() const {
    if (units_sold) 
        return prices / units_sold;
    else 
        return 0;
}