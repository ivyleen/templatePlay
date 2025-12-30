#pragma once

#include <iostream>
#include <stdexcept>

// Stack is a FILO

template <typename T>
class Stack
{
    T *m_pBuffer{};
    size_t m_Top{};
    size_t m_Size{};
    // the static member must be instantiated inside this header
    // because this is a template class
    // static size_t counter; // pre c++17
    inline static size_t counter{}; // c++17 with value initialization

public:
    // Rule of 5
    // It applies to resource-owning classes, and if you define any one of these
    // Copy constructor, Destructor, Copy assignment operator, Move constructor
    // Move asignment operator - you usually need to define all five.
    // The “resource” can be:
    // - heap memory (new[] / delete[])
    // - file handles
    // - mutexes
    // - sockets
    // In our case - we have heap memory

    Stack() = default;
    Stack(size_t size) : m_pBuffer{new T[size]},
                         m_Size{size}
    {
        ++counter;
    }

    // copy
    Stack(const Stack &other) : m_pBuffer{other.m_pBuffer ? new T[other.m_Size] : nullptr},
                                m_Top{other.m_Top},
                                m_Size{other.m_Size}
    {
        for (size_t i = 0; i < m_Top; ++i)
        {
            m_pBuffer[i] = other.m_pBuffer[i];
        }

        ++counter;
    }

    // copy assignment
    Stack &operator=(const Stack &other)
    {
        if (this == &other)
        {
            return *this;
        }

        delete[] m_pBuffer;

        m_Size = other.m_Size;
        m_Top = other.m_Top;
        m_pBuffer = m_Size ? new T[other.m_Size] : nullptr;

        for (size_t i = 0; i < m_Top; ++i)
        {
            m_pBuffer[i] = other.m_pBuffer[i];
        }

        return *this;
    }

    // move contructor
    Stack(Stack &&other) noexcept : m_pBuffer{other.m_pBuffer},
                                    m_Top{other.m_Top},
                                    m_Size{other.m_Size}
    {
        other.m_pBuffer = nullptr;
        other.m_Top = other.m_Size = 0;
    }

    // move assignment
    Stack &operator=(Stack &&other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }

        delete[] m_pBuffer;
        m_pBuffer = other.m_pBuffer;
        m_Top = other.m_Top;
        m_Size = other.m_Size;

        other.m_pBuffer = nullptr;
        other.m_Top = other.m_Size = 0;

        return *this;
    }

    ~Stack()
    {
        delete[] m_pBuffer;
    }

    void
    Push(const T &element)
    {
        if (Full())
        {
            throw std::logic_error("Stack is full");
        }
        m_pBuffer[m_Top] = element;
        ++m_Top;
    }

    void Pop()
    {
        if (Empty())
        {
            throw std::logic_error("Stack is empty");
        }
        --m_Top;
    }

    T &Top() const
    {
        if (Empty())
        {
            throw std::logic_error("Stack is empty");
        }
        return m_pBuffer[m_Top - 1];
    }

    bool Empty() const
    {
        return m_Top == 0;
    }

    bool Full() const
    {
        return m_Top == m_Size;
    }

    void Print()
    {
        if (Empty())
        {
            std::cout << "stack is empty\n";
            return;
        }

        for (size_t i = m_Top; i > 0; --i)
        {
            std::cout << m_pBuffer[i - 1] << " ";
        }
        std::cout << std::endl;
    }

    size_t Size() const
    {
        return m_Size;
    }

    static void PrintInstances()
    {
        std::cout
            << "Total instances for: " << typeid(Stack<T>).name()
            << " are: " << counter
            << std::endl;
    }
};

// pre c++17
// template <typename T>
// size_t Stack<T>::counter = 0;

// best practice
extern template class Stack<int>;

// declaration for explicitly specialized member function
// for stask<stack<int> outside of the class in the same namespace
// if we don't declare it here the compiler will try to do it
// on its own and will use the standard Print function
// because will not be able to see the definition of the
// explicitly specilized member function in stack.cpp.
// The standard print wouldn't work because of the <<
// stream operator that doesn't know how to operate our
// Stack of Stacks<int>.
// It will also not be able to link because main.o will
// already have the Stack<Stack<int>>::Print() instantiated
// so when it tries to link with stack.cpp for the exe
// it will come up "already defined" error.
template <>
void Stack<Stack<int>>::Print();