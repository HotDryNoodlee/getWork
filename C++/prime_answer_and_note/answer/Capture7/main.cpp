#include <iostream>
// #include "saleclass.h"
// #include "window_arg.h"
// #include "screen.h"
#include "NoDefault.h"
#include "C.h"
using namespace std;


int main()
{   
    C ans(12);
    cout << ans.get_member().get_val() << endl;
    // CSales_data fist("978-7-121-15535-2", 85, 128, 109);
    // CSales_data second;
    // CSales_data third("978-7-121-15535-2");
    // CSales_data last(cin);
    // return 0;

    // cout << "请输入交易记录(ISBN、销售量、原价、实际售价):" << endl;
    // // CSales_data total(cin);
    // CSales_data total(cin);
    // if (cin)
    // {
    //     CSales_data trans(cin);
    //     do
    //     {
    //         if (total.isbn() == trans.isbn())
    //             total = add(total, trans);
    //         else
    //         {
    //             print(cout, total);
    //             cout << endl;
    //             total = trans;
    //         }
    //     } while (read(cin, trans));
    //     print(cout, total);
    //     cout << endl;
    // }
    // else
    // {
    //     cerr << "No data?!" << endl;
    //     return -1;
    // }
    // return 0;

    // Window_arg w;
    // Screen befor(1, 2, 'c');
    // cout << befor.size() << endl;
    // w.clear(befor);
    // return 0;

    // Screen myScreen(5, 5, 'X');
    // myScreen.move(4, 0).set('#').display();
    // cout << "\n";
    // myScreen.display();
    // cout << "\n";
}