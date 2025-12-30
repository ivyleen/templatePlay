#include "stack.h"

// if we want to separate definition and declaration
// we also need to specify the type of the Stack class
// which in this case would be a typename T
// template <typename T>
// void Stack<T>::Push(const T &element){}

// if i want to explictly instantiate the stack for int:
// this will be the only instantiation of the Stack<int> type
template class Stack<int>;