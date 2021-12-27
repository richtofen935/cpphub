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

    Resource Acquisition Is Initialization (RAII) is a principle used
    to manage resources elegantly and exeception safe.
    A class is built around a resource that is acquired upon creation
    of an instance and released whenever the instance is destructed.
    c++ provides the constructor/destructor methods to make this work.
    Some examples for such resources are:
        - memory on heap
        - threads
        - mutex variables

    This file provides an example for memory management using the RAII
    principle for an elementary datatypes
*/

#include <iostream>
#include <cstddef>

template <typename T>
class Buffer {
    private:
        std::size_t size_;
        T* data_;

    public:
        // Constructor takes the size argument and then allocates
        // memory using the new operator. The returned pointer
        // is stored in a class attribute
        Buffer(size_t s) : 
            size_(s), 
            data_(new T[size_]) {
        }

        // the destructor simply releases allocated memory
        ~Buffer() {
            // brackets are needed in order to free the array
            // and not only the first element
            delete[] data_;
        }

        // add get methods
        T* data() {
            return data_;
        }

        size_t size() {
            return size_;
        }


        // now we will also overload the access operator
        // to make usage convenient and intuitive
        T& operator[] (size_t i) {
            return data_[i];
        }
        
        // delete copy constructor and assignment operator
        // to prevent from usage with double free
        Buffer(const Buffer&) = delete;
        Buffer(const Buffer&&) = delete;
        Buffer& operator=(const Buffer&) = delete;
        Buffer& operator=(const Buffer&&) = delete;
};

// function to initialize such a buffer
template <typename T>
void init_buffer(Buffer<T>& b) {
    for (size_t i=0; i<b.size(); ++i) {
        b[i] = i+1;
    }
}


// add main function for demonstration
int main() {

    // create buffer of size 10 on heap
    Buffer<int> a(10);
    
    // NOT possible as we deleted the copy operator
    //Buffer<int> r(a);
    //r = a

    // we can also control the life time of an object
    // by putting it to a dedicated block
    {
        Buffer<double> b(12);
        init_buffer(b);
    } //destruction of b

    {
        Buffer<float> c(100);
    } // destruction of c

} // destruction of a
