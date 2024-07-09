*   ## 练习 6.16：下面的这个函数虽然合法，但是不算特别有用。指出它的局限性并设法改善。 
    ```c++
    bool is_empty(string& s) { return s.empty(); } 
    ```

    *   【出题思路】 

        本题旨在考查普通引用和常量引用作为参数类型的区别。一般情况下，与普通
        引用相比，我们更应该选择使用常量引用作为参数类型。 
        
    *   【解答】 
  
        本题的程序把参数类型设为非常量引用，这样做有几个缺陷：一是容易给使用
        者一种误导，即程序允许修改变量 s 的内容；二是限制了该函数所能接受的实参类
        型，我们无法把const 对象、字面值常量或者需要进行类型转换的对象传递给普通
        的引用形参。 
        根据上述分析，该函数应该修改为： 
        ```c++
        bool is_empty(const string& s) { return s.empty(); }
        ```

*   ## 练习6.24：描述下面这个函数的行为。如果代码中存在问题，请指出并改正。 
    ```c++
    void print(const int ia[10]) 
    { 
        for (size_t i = 0; i != 10; ++i) 
            cout << ia[i] << endl; 
    } 
    ```
    *   【出题思路】 
  
        当我们想把数组作为函数的形参时，有三种可供选择的方式：一是声明为指针，
        二是声明为不限维度的数组，三是声明为维度确定的数组。实际上，因为数组传入
        函数时实参自动转换成指向数组首元素的指针，所以这三种方式是等价的。 

    *   【解答】 
  
        由之前的分析可知，print 函数的参数实际上等同于一个常量整型指针const 
        int*，形参ia 的维度10 只是我们期望的数组维度，实际上不一定。即使实参数组
        的真实维度不是10，也可以正常调用print 函数。 
        上述print 函数的定义存在一个潜在风险，即虽然我们期望传入的数组维度是
        10，但实际上任意维度的数组都可以传入。如果传入的数组维度较大，print 函数
        输出数组的前 10 个元素，不至于引发错误；相反如果传入的数组维度不足 10，则
        print 函数将强行输出一些未定义的值。 
        修改后的程序是： 
        ```c++
        void print(const int ia[], const int sz) 
            { 
                for (size_t i = 0; i != sz; ++i) 
                    cout << ia[i] << endl; 
            } 
        ```

*   ## 接受字符串参数

    ```c++
    #include <iostream> 
    using namespace std;  
    int main(int argc, char **argv) {
        string str;     
        for(int i = 0; i != argc; ++i)         
            str += argv[i];     
        cout << str << endl;     
        return 0; 
    }
    ```
    ```c++
    #include <iostream> 
    using namespace std;  
    int main(int argc, char **argv) {     
        for(int i = 0; i != argc; ++i){
            cout << "argc[" << i << "]: " << argv[i] << endl;     
        }     
        return 0; 
    }
    ```

*   ## 练习 6.39：说明在下面的每组声明中第二条声明语句是何含义。如果有非法的声明，请指出来。 

        (a)  int calc(int, int); int calc(const int, const int); 

        (b)  int get(); double get(); 

        (c)  int *reset(int *); double *reset(double *); 

    *   【出题思路】 
  
        本题旨在考查重载函数的含义以及如何判断两个函数是否是重载关系。

    *   【解答】 
  
        (a)的第二个声明是非法的。它的意图是声明另外一个函数，该函数只接受整型常量作为实参，但是因为顶层 const 不影响传入函数的对象，所以一个拥有顶层const 的形参无法与另一个没有顶层const 的形参区分开来。 
        
        (b)的第二个声明是非法的。它的意图是通过函数的返回值区分两个同名的函数，但是这不可行，因为 C++规定重载函数必须在形参数量或形参类型上有所区别。如果两个同名函数的形参数量和类型都一样，那么即使返回类型不同也不行。 
        
        (c)的两个函数是重载关系，它们的形参类型有区别。


*   ## 练习6.47：改写6.3.2 节（205 页）练习中使用递归输出vector 内容的程序，使其有条件地输出与执行过程有关的信息。例如，每次调用时输出 vector 对象的大小。分别在打开和关闭调试器的情况下编译并执行这个程序。 
    *   【出题思路】 
  
        本题旨在考查如何在程序中打开和关闭调试器。 

    *   【解答】 
  
        满足题意的程序如下所示： 
        ```c++
        #include <iostream> 
        #include <vector> 
        using namespace std; // 递归函数输出vector<int>的内容 
        void print(vector<int> vInt, unsigned index) 
        {     
            unsigned sz = vInt.size();   // 设置在此处输出调试信息     
            #ifndef NDEBUG     
            cout << "vector 对象的大小是：" << sz << endl;     
            #endif // NDEBUG     
            if(!vInt.empty() && index < sz)     
            {         
                cout << vInt[index] << endl;         
                print(vInt, index + 1);     
            } 
        }  
        int main() 
        {     
            vector<int> v = {1,3,5,7,9,11,13,15};     
            print(v, 0);     
            return 0; 
        } 
        ```
        打开调试器时，每次递归调用print 函数都会输出“vector 对象的大小是：8”；
        关闭调试器时，程序只输出vector 对象的内容，不再输出其大小。 

*   练习 6.53：说明下列每组声明中的第二条语句会产生什么影响，并指出哪些不合法（如果有的话）。 

    (a)   int calc(int&, int&); int calc(const int&, const int&); 

    (b)   int calc(char*, char*); int calc(const char*, const char*); 

    (c)   int calc(char*, char*); int calc(char* const, char* const); 

    *  【出题思路】 

        考查顶层const 和底层const 对函数重载的影响。 

    *   【本题解答】 
        
        (a)是合法的，两个函数的区别是它们的引用类型的形参是否引用了常量，属于底层const，可以把两个函数区分开来。 
        
        (b)是合法的，两个函数的区别是它们的指针类型的形参是否指向了常量，属于底层const，可以把两个函数区分开来。 
        
        (c)是非法的，两个函数的区别是它们的指针类型的形参本身是否是常量，属于顶层const，根据本节介绍的匹配规则可知，向实参添加顶层const 或者从实参中删除顶层const 属于精确匹配，无法区分两个函数。


    *   ## constexpr函数

        1. **constexpr函数的返回值类型必须是字面值类型**

        2. **constexpr函数的形参可以是非常量，但是实参必须是常量**

        3. **函数体中必须有且只有一条return语句**
