#include <iostream>
#include <cstring>

void CallTemplate();
void More();
void StaticCall();

template <typename T>
T ExternTemplate(T a, T b)
{
    std::cout << "Extern template example: " << typeid(T).name() << " - ";
    return a > b ? a : b;
}

extern template int ExternTemplate(int, int);

template <typename T>
T Max(T a, T b)
{
    std::cout << "Max type: " << typeid(T).name() << " - ";
    return a > b ? a : b;
}

template <typename T>
T Square(T a)
{
    return a * a;
}

template <typename T1, typename T2, typename TResult>
TResult Product(T1 a, T2 b)
{
    return a * b;
}

// but if we add the result type as first parameter we
// won't need to write all parameters, just the one for return
template <typename TResult, typename T1, typename T2>
TResult Product2(T1 a, T2 b)
{
    return a * b;
}

// c++11
template <typename T1, typename T2>
auto Product3(T1 a, T2 b) -> decltype(a * b)
{
    return a * b;
}

// c++14
template <typename T1, typename T2>
auto Product4(T1 a, T2 b) // no need of -> decltype
{
    return a * b;
}

// type traits
template <typename T1, typename T2>
std::common_type_t<T1, T2> Product5(T1 a, T2 b)
{
    return a * b;
}

// default parameters
template <typename TResult = double, typename T1, typename T2>
TResult Product6(T1 a, T2 b)
{
    return a * b;
}

template <typename T1, typename T2,
          typename TResult = std::common_type_t<T1, T2>>
TResult Product7(T1 a, T2 b)
{
    return a * b;
}

// argument conversion
template <typename T>
void Foo(T a)
{
    std::cout << typeid(T).name() << " -> " << a << '\n';
}

// non-type template parameters
// C++11 must have an external linkage
// C++14, more relaxed - external or internal linkage
// C++17 - no restrictions
// can be of integral type (char,short,int,long,enum,ptr_t)
// must be a compile time expression
// it has to be a constant, can't be anything dynamic
// string literals are not allowed
// can't be a temporary or a data member
// the signiture of the functions will include the value
template <int value>
void Print0()
{
    std::cout << value << '\n';
}

// c++17 non-type template parameters - use of auto
// the parameter becomes part of the function name
// this will cause to create a separate function for each parameters
// even if those parameters are of the same type
template <auto value>
void Print1()
{
    std::cout << value << '\n';
}

// overload based on return type
template <typename T1, typename T2>
auto Greater(T1 a, T2 b)
{
    std::cout << "Return type is auto." << std::endl;
    return a > b ? a : b;
}

template <typename Result, typename T1, typename T2>
Result Greater(T1 a, T2 b)
{
    std::cout << "Return type is typename Result." << std::endl;
    return a > b ? a : b;
}

// adding extern template functionality
template <typename T>
T Min(T a, T b)
{
    return a < b ? a : b;
}

extern template int Min(int, int);

// static variables in function templates
/*template <typename T>
void Print(T data)
{
    static int counter{};
    std::cout << counter++ << ". " << data << std::endl;
}*/
// avoid duplication of the same static symbol via extern
template <typename T>
void Print(T value)
{
    static int counter = 0;
    std::cout << counter++ << ": " << value << "\n";
}

extern template void Print<int>(int);