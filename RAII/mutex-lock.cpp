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
        - threads (as in std::thread)
        - mutex variables

    This file provides an example for usage of a mutex variable by the RAII
    principle. The standard library also provides a more sophisticated
    version as std::lock_guard in <mutex>.
*/

#include <mutex>
#include <iostream>

// This class is designed to support all datatypes that
// provide 'un-/lock' method, e.g. a mutex variable
template <typename T>
class Lock {
    private:
        // resource is absolutely required to be caught
        // by reference
        T& resource;

    public:
        // constructor locks the resource
        Lock(T& r) : resource(r) {
            resource.lock();
            std::cout << "Resource is locked" << std::endl;
        }

        // destructor releases the resource
        ~Lock() {
            resource.unlock();
            std::cout << "Resource is unlocked" << std::endl;
        }
};

int main() {
    std::cout << "Start of script" << std::endl;
    std::mutex m;
    {
        Lock<std::mutex> lock(m);
    }

    // Repeat the procedure with the STL lock_guard
    {
        std::lock_guard<std::mutex> lock(m);
    }


    std::cout << "End of script" << std::endl;
}
