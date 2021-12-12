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

    print_binary uses the bit shifting operator to access single bits of 
    variable "in" and prints them in correct order to the standard output;

    the construction: in & (1 << i) 
    performs a bitwise AND comparison of a bitshifted 1 (i.e. all bits in
    00000001 are shifted by i positions). Because for the bitshifted 1 there
    is only a single bit set, the comparison returns 00000000 only if bits 
    at i-th position are equal. According to this outcome, the corresponding
    character is either set to '0' or '1' and then printed.
    Because most significant bits should be printed first, we traverse the
    series of bits from behind in the for-loop.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

void print_binary(int8_t in) {
    bool firstone = false;
    for (int i=sizeof(in)*CHAR_BIT-1; i>=0; --i) {
        char p = (in & (1 << i))? '1' : '0';
        if (p=='1') {
            firstone = true;
        }
        if (firstone || i==0) {
            putchar(p);
        }
    }
    putchar('\n');
}

int main() {
    int8_t a;

    printf("Enter an integer number:\n");
    if (scanf("%hhd", &a) != 1) {
        exit(1);
    }

    printf("This number in binary representation:\n");
    print_binary(a);
}

