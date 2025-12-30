#include "stack.h"

// if we want to separate definition and declaration
// we also need to specify the type of the Stack class
// which in this case would be a typename T
// template <typename T>
// void Stack<T>::Push(const T &element){}

// if i want to explictly instantiate the stack for int:
// this will be the only instantiation of the Stack<int> type
template class Stack<int>;

template <>
void Stack<Stack<int>>::Print()
{
    if (Empty())
    {
        std::cout << "stack is empty\n";
        return;
    }

    for (size_t i = m_Top; i > 0; --i)
    {
        m_pBuffer[i - 1].Print();
    }
    std::cout << std::endl;
}