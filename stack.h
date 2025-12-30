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

public:
    Stack() = default;
    Stack(size_t size) : m_pBuffer{new T[size]},
                         m_Size{size}
    {
    }

    ~Stack()
    {
        delete[] m_pBuffer;
    }

    void Push(const T &element)
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
};

// best practice
extern template class Stack<int>;