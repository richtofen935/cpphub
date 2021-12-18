/* 
    Copyright (c) 2021 Lennart Bosch

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

/* 
    Created by: Lennart Hendrik Bosch
    Creation date: 12 Dec 2021

    Simple example to demonstrate how to control
    what types a template parameter is allowed to
    take using the c++20 standard.
*/

#include <type_traits>
#include <iostream>

#if __cplusplus < 201709L
#error This file requires compiler and library support for the \
ISO C++ 2020 standard.
#else


// Define a simple class template that allows
// template parameter T only to take integral 
// values
template <typename T>
requires std::is_integral<T>::value
class Number {
public:
    T num;
    
    Number(T input) : num(input) {
    }
};



int main() {
    int a = 5;
    std::cout << __cplusplus << std::endl;
    
    //Automatic type deduction
    Number n(a);
    
    //Fails: 
    //float f = 5.3;
    //Number m(f);
    std::cout << "Hello" << std::endl;
}

#endif // of #if __cplusplus < 201709L #else ...
