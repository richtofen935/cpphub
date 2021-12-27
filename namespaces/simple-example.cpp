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
    Creation date: 27 Dec 2021

    Small demonstration of use of namespaces and also nesting.
*/

#include <iostream>

// let's create a simple namespace and then add a simple function
namespace first {
    void print_int(int i) {
        std::cout << "Printing from 'first': " << i << std::endl;
    }
}

// repeat with a different namespace
namespace second {
    void print_int(int i) {
        std::cout << "Printing from 'second': " << i << std::endl;
    }

    // start nesting the stuff
    namespace subsecond {
        void print_int(int i) {
            std::cout << "Printing from 'second::subsecond': " << i << std::endl;
        }
    }
}

// namespaces are merely a way to additionally specify and groud functions
// hence, we can also easily extend the "std" namespace that usually is used
// for the standard library 
// this means, we can add new functions to a namespace anywhere in the program
// or different files
namespace std {
        void print_int(int i) {
            std::cout << "Printing from 'std': " << i << std::endl;
        }
}


// here comes the main function
int main() {
    int a = 3;
    first::print_int(a);
    second::print_int(a);
    // for nested namespace simply follow the hierarchy
    second::subsecond::print_int(a);
    std::print_int(a);
}
