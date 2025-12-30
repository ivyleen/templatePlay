#include "utils.h"

extern template char *Max(char *, char *);

void CallTemplate()
{
    char *str1 = new char[]{"C++"};
    char *str2 = new char[]{"C"};
    std::cout << "Utils: " << Max(str1, str2) << "\n";
    std::cout << "Utils max: " << Max(2, 4) << std::endl;
    std::cout << "Utils min: " << Min(2, 4) << std::endl;

    std::cout << ExternTemplate(1, 2) << std::endl;
}

// explicit instanstiation for float
template <>
float Max(float a, float b)
{
    return a > b ? a : b;
}

// pre-c++20 -> use case could be a way to constrain usage
// if the Max template base was only in this cpp file
// explicit instanstiation for short
template short Max(short, short);