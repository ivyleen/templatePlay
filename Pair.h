#pragma once
template <typename T1, typename T2>
class Pair
{
    T1 m_First{};
    T2 m_Second{};

public:
    Pair() = default;
    Pair(T1 first, T2 second) : m_First(first),
                                m_Second(second)
    {
    }

    T1 &GetFirst()
    {
        return m_First;
    }
    const T1 &GetFirst() const
    {
        return m_First;
    }

    T1 &GetSecond()
    {
        return m_Second;
    }
    const T1 &GetSecond() const
    {
        return m_Second;
    }

    void SetFirst(T1 first)
    {
        return m_First;
    }

    void SetSecond(T2 second)
    {
        return m_Second;
    }
};

// factory function
template <typename T1, typename T2>
Pair<T1, T2> MakePair(T1 first, T2 second)
{
    // compiler will automatically deduce this expression
    // from the return type - that's why no need to specify
    // the class before the {}
    return {first, second};
}
