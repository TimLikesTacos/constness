/***************************************
* Demonstration of const correctness of functions and member variables
* Illegal operations are written, but commented out to allow compilation.
* This program, once compiled, does not do anything as it is only made
* to illastrate comilation errors with incorrect applications of const
* and non-const functions
*
* Made by Tim Reed 9/24/2019
****************************************/
#include <iostream>

using namespace std;

class X
{
    int val;
    int const cNumber = 0;
    static int const scNumber = 0;

    public:
    void const_func () const {cout << val;} // ok, does not change member variable
    //int const_func2 () const {return ++val;} // illegal - function promises not to change members, but changes member variable, compile error
    void not_const_func () {cout << ++val;} // ok, changes member variable

    //void change_cNumber () { ++cNumber;} // illegal, attempts to change const variable.
    //void change_scNumber () { ++scNumber;} // illegal, attempts to change const variable.
    X () : val(1){}
};

void change_stuff_value (X t) // pass by value. no promises that anything is const.
{
    t.const_func(); // ok
    t.not_const_func(); //ok
}

void change_stuff_const_ref (const X& t) // from right to left. "t is a reference to an X that is constant"
{
    t.const_func(); // ok
    //t.not_const_func(); // illegal.  discards the const of t. Compile error.
}

void change_stuff_pointer (X* ptr) // ptr is a pointer that points to an object of X
{
    ptr->const_func(); // ok
    ptr->not_const_func(); // ok

    ptr = nullptr; // ok, pointer is not const.
}

void change_stuff_const_ptr (const X* ptr) // right to left: "ptr is a pointer that points to an object of X that is constant"
{
    ptr->const_func(); // ok
    // ptr->not_const_func(); // illegal.  dicards const of the value that ptr points at. Compile error.

    ptr = nullptr; // ok, ptr is not const.

    X test;
    ptr = &test;
    ptr->const_func();
    //ptr->not_const_func(); // illegal. Compile error
}

void change_stuff_ptr_const (X* const ptr) // right to left: "ptr is constant, and it's a pointer that points to an object of X"
{
    ptr-> const_func (); // ok
    ptr-> not_const_func(); //ok, value of type X is not const.

    //ptr = nullptr; //illegal, ptr is const. Compile error.
}

void change_stuff_const_ptr_const (const X* const ptr) // right to left: "ptr is constant, and it's a pointer that points to an object of X that is const"
{
    ptr-> const_func (); // ok
   // ptr-> not_const_func(); //illegal, value of type X is const. Compile error.

   // ptr = nullptr; //illegal, ptr is const. Compile error.
}

int main()
{
    X x;
    return 0;
}
