#include "utils.h"
#include "classExample.h"
#include "stack.h"
#include "Pair.h"

#include <string>

// empty functions for passing to Foo
void A() {}
void B() {}

// explicit specialization for the Max function will look:
// it will not work for char* because it will compare
// the pointer addresses and not the values
template <>
char *Max(char *a, char *b)
{
    std::cout << "Explicit specialization: ";
    return strcmp(a, b) > 0 ? a : b;
}

// non-type overload -> this will be prefered over any template speciliation
char *Max(char *a, char *b)
{
    std::cout << "Non template overload. ";
    return strcmp(a, b) > 0 ? a : b;
}

// the extern template is now only here
template int ExternTemplate(int, int);
template int Min(int, int);
template void Print<int>(int);

int main()
{
    // invoking the Max function will instanstiate it
    auto result1 = Max(static_cast<double>(3), 5.54);
    auto result2 = Max<double>(73, 5.54);
    auto result3 = Max(1.3, 8.5);

    std::cout << result1 << std::endl;
    std::cout << result2 << std::endl;
    std::cout << result3 << std::endl;

    int num = 5;
    auto squared = Square(num);
    std::cout << squared << std::endl;

    std::cout << "Explicit template types of everything: " << Product<int, double, double>(5, 2.5) << std::endl;
    std::cout << "Explicit template type of the return: " << Product2<double>(5, 2.5) << std::endl;
    std::cout << "C++11: " << Product3(5, 2.5) << std::endl;
    std::cout << "C++14: " << Product4(5, 2.5) << std::endl;
    std::cout << "Type traits: " << Product5(5, 2.5) << std::endl;
    std::cout << "Default hard coded return template type: " << Product6(5, 2.5) << std::endl;
    std::cout << "Default dynamically deduced return template type: " << Product7(5, 2.5) << std::endl;

    Foo(3u);
    Foo(8);
    Foo('a');

    const int x = 5;
    Foo(x); // <- will remove the const

    int y = 10;
    Foo(&y);

    int arr[5];
    Foo(arr);

    Foo(A);
    Foo(B); // will be only one instantiation since A and B are the same in thier declarations

    Print0<4>();
    Print1<2u>();
    Print1<'u'>();

    char *str1 = new char[]{"C++"};
    char *str2 = new char[]{"C"};
    std::cout << "Explicit specialization or non template overload: " << Max(str1, str2) << "\n";

    std::cout << Greater(9.5f, 2) << std::endl;
    // if i change it to <int> will not compile
    // the idea is that here we are specifying the first type
    // in 1) case that would be the T1 type
    // in 2) case that would be the Result type
    // in all cases (2, 9.5f) will be deduced to (int, float)
    // which means that if we choose <int> will mean that
    // we can use both template functions which creates
    // ambiguaty for the compiler
    std::cout << Greater<double>(2, 9.5f) << std::endl;

    // function pointer to the template Max function
    // this is another way to instantiate the template function
    double (*pfn)(double, double) = Max;
    auto pfn2 = Max<char>;

    std::cout << "Min: " << Min(3, 5) << std::endl;
    CallTemplate();
    More();
    std::cout << ExternTemplate(1, 2) << std::endl;

    Print(100);
    Print(200);
    StaticCall();

    Print(1.3);
    Print(10.50);

    Stack<int> s{5};
    for (int i = 0; i < 5; ++i)
    {
        s.Push(i);
    }

    s.Print();
    while (!s.Empty())
    {
        std::cout << s.Top() << ' ';
        s.Pop();
    }

    std::cout << std::endl;

    s.Print();

    // creating a second integer type to test the counter
    Stack<int> s1{5};

    Stack<int>::PrintInstances();

    Stack<std::string> numbers{5};
    numbers.Push("One");
    numbers.Push("Two");
    numbers.Push("Three");
    numbers.Push("Four");
    numbers.Push("Five");
    numbers.Print();

    Stack<std::string>::PrintInstances();

    using namespace std::string_literals;
    Pair<int, std::string> p1{101, "C++"}; // before c++17
    auto p2 = MakePair(101, "C++"s);
    Pair p3{101, "C++"s}; // after c++17, this will match our constructor
}