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
    Creation date: 18 Dec 2021
    
    This is a more elaborate version of the file
    "template_specification_with_traits.cpp", which
    demonstrates how to incorporate another template
    parameter.

    Demonstration on how to use traits (part of c++17
    standard) to specify template parameters to match
    particular types only. The file is organized in four
    sections: Helper keyword definition, example classes
    definition, example function definition, main function.
    
    Particular use case: Communicating systems, e.g. in
    a MPI programm, where data has to be exchanged between 
    a local and a remote process. One class is designed to
    manage local data while another class is designed to 
    manage access to remote data. Then a function "copy"
    can be overloaded to either send data or receive data
    depending on the type of the class. A very similar use 
    case is in CUDA applications where the remote part is
    taken by the GPU.
*/

#include <type_traits>
#include <iostream>


// ############ Definition of helper keywords ##############
// define 'Require' keyword
template <typename T, typename... Args>
using Require = typename std::common_type<T, Args...>::type;

// some more functionalities to compare types,
// will not be used in this example but might come
// in handy in other cases
template <typename T>
struct make_ElementType
{
};

template <template<typename> class X, typename T>
struct make_ElementType<X<T>>
{
    using type = T;
};

template <typename T>
using ElementType
    = typename make_ElementType<typename std::remove_reference<T>::type>::type;

template <typename TX, typename TY>
using SameElementType
    =  typename std::conditional<
                std::is_same<ElementType<TX>, ElementType<TY>>::value,
                bool, void>::type;
   
// following types define the keywords "is_Type", "is_A", and "is_B";
// these have to be included into particular classes in order
// to make them accessible for template specification;
// such a type has to be constructed for every type we want
// to be able to specify

// common type                
template <typename T>
using Type
    = std::enable_if_t<std::remove_reference<T>::type::is_Type::value,
        bool>;

// type A
template <typename T>
using TypeA
    = std::enable_if_t<std::remove_reference<T>::type::is_A::value,
        bool>;

// type B
template <typename T>
using TypeB
    = std::enable_if_t<std::remove_reference<T>::type::is_B::value,
        bool>;

// ############ Definition of example classes ##############
// the following definitions are basically identical, 
// could also have been written using inheritance but
// we will not use it here for reasons of simplicity
// some class definitions
class TypeAclass {
public:
    int number;
    
    // def type attributes, this here is the important
    // part that will enable us to specify this class;
    using is_Type = std::true_type;
    using is_A = std::true_type;
    
    TypeAclass(int num) : number(num) {
    }
};

class TypeBclass {
public:
    int number;
    
    // def type attributes
    using is_Type = std::true_type;
    using is_B = std::true_type;
    
    TypeBclass(int num) : number(num) 
    {
    }
};


class TypeCclass {
public:
    int number;
    
    // def type attributes
    using is_Type = std::true_type;
    
    TypeCclass(int num) : number(num) 
    {
    }
};

// ############ Definition of example functions ##############
// function definitions where certain types are
// required, i.e. for class A and B


template <class TypeX,
    // here comes the "Require" keyword;
    // it takes variadic template arguments,
    // here we target TypeX to only take classes
    // that provide is_A = std::true_type,
    // for TypeY we require is_B
    Require< TypeA<TypeX> > = true>
void set(TypeX& X) {
    std::cout << "Set A with 42" << std::endl;
    X.number = 42;
}

template <class TypeX,
    Require< TypeB<TypeX> > = true>
void set(TypeX& X) {
    std::cout << "Set B with 666" << std::endl;
    X.number = 666;
}

// Function to print number attribute of object
// that provides is_Type
template <class TypeX,
    Require< Type<TypeX> > = true>
void print(TypeX& x) {
    std::cout << "number in arg: " << x.number << std::endl;
}

// We start off with a routine to copy from A to B
template <
    // define template templates
    class TypeX,
    class TypeY,
    Require< TypeA<TypeX>,
            TypeB<TypeY> > = true
    // End of template preamble
    >
void copy(TypeX& x, TypeY& y) {
    std::cout << "copy A to B" << std::endl;
    y.number = x.number;
}

// Now the opposite direction
template <class TypeX,
    class TypeY,
    Require< TypeB<TypeX>,
            TypeA<TypeY> > = true>
void copy(TypeX& x, TypeY& y) {
    std::cout << "copy B to A" << std::endl;
    y.number = x.number;
}


// ############ Add main function ##############
int main() {
    
    // create two instances
    TypeAclass a(3);
    auto b = new TypeBclass(5);
    
    // perform copy operation
    print(a);
    print(*b);
    set(a);
    copy(a,*b);
    print(a);
    print(*b);
    
    // repeat in other direction
    std::cout << "Set number in B to 16" << std::endl;
    set(*b);
    copy(*b,a);
    print(a);
    print(*b);
    
    // another example
    TypeCclass c(13);
    std::cout << "Demonstrate that also TypeCclass can be printed" << std::endl;
    print(c);
    
    // clean up
    delete b;    
}
