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
    take.
*/

#include <type_traits>
#include <iostream>


// Define a simple class template
template <typename T>
class Number {
public:
    T num;
    
    Number(T input) : num(input) {
    }
};

// std::enable_if takes two types, bool first
// and a template parameter second. When the first 
// paramter evaluates to 'true', then is_integral
// has a public member typedef type equal to T.
// Otherwise compilation fails because no type is 
// available.
// std::is_integral is a helper struct that creates
// a bool 'value' in dependence of template parameter
// T, for the current case 'value' evaluates to true
// if T is any integral type.
// <type_traits> also provides other helper structs
// such as std::is_floating_point.


// Typical approach to handle this specification is to 
// leave the object construction to a helper function
// preamble of a template
template<typename T>
// define return type
typename std::enable_if_t<
    std::is_integral<T>::value,
    Number<T>
    >
gen_number(T in) {
    std::cout << "Creating integral type object" << std::endl;
    return Number<T>(in);
}

int main() {
    int i = 5;
//     float f = 4.5;
    auto n = gen_number(i);
    std::cout << "Hello" << std::endl;
}
