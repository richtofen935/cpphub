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

    Basic example of a macro definition with variadic arguments:
    takes a function name, evaluates it and acts accordingly.

    Mind the additional curly braces, that make sure that local variables
    do not outlive the macro. This prevents the stack from being 
    cluttered unintentionally.
    Also mind, that in the last line no '\' is allowed.

    Such macros to check the return values of a function provided
    are a convenient approach to check the return values of API calls
    while keeping the code relatively clean.

    NOTE: cpp might require ##__VA_ARGS__ instead of __VA_ARGS__.
    BUT: there we can use type 'auto' for the return value and
    leave type handling to compiler.
*/

#include <stdio.h>
#include <stdbool.h>

#ifndef CHECK_SUCCESS
#define CHECK_SUCCESS(funcname, ...) \
{ \
    bool res = funcname(__VA_ARGS__); \
    printf("function evaluation at line %d ", __LINE__); \
    printf("in file %s returned ", __FILE__); \
    if (res) { \
        printf("true\n"); \
    } else { \
        printf("false\n"); \
    } \
} 
#endif

bool is_positive(int a) {
    return a>=0;
}

bool is_equal(int a, int b) {
    return a==b;
}

int main() {
    int a = 3;
    int b = 5;
    printf("Comparing 3 and 5:\n");
    CHECK_SUCCESS(is_equal, a, b);

    printf("Checking for 3 greater than zero:\n");
    CHECK_SUCCESS(is_positive, a);
};
