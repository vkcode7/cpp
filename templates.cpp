#include <iostream>
#include <string.h>
// Old Code
// int Max(int x, int y) {
//	return x > y ? x : y;
// }
// float Max(float x, float y) {
//	return x > y ? x : y;
// }

// Primary Template
template <typename T>
T Max(T x, T y)
{
    std::cout << typeid(T).name() << std::endl;
    return x > y ? x : y;
}
// Explicit Instantiation
template char Max(char x, char y);

// Explicit Specialization
template <>
const char *Max<const char *>(const char *x, const char *y)
{
    std::cout << "Max<const char*>()" << std::endl;
    return strcmp(x, y) > 0 ? x : y;
}

void Examples()
{
#pragma region Instantiation Examples
    Max(static_cast<float>(3), 5.5f);

    // Override compiler's deduction process
    Max<double>(3, 6.2);

    // Causes implicit instantiation of Max<int>
    int (*pfn)(int, int) = Max;

#pragma endregion
#pragma region Explicit Instantiation
    const char *b{"B"};
    const char *a{"A"};
    auto s = Max(a, b);
    std::cout << s << std::endl;
#pragma endregion
}

// Non-type template parameter
template <int size>
void Print()
{
    char buffer[size];
    std::cout << size << std::endl;
}
// Requires size as explicit argument
template <typename T>
T Sum(T *parr, int size)
{
    T sum{};
    for (int i = 0; i < size; ++i)
    {
        sum += parr[i];
    }
    return sum;
}
// Size is implicitly calculated in non-type template argument
template <typename T, int size>
T Sum(T (&arr)[size])
{
    T sum{};
    for (int i = 0; i < size; ++i)
    {
        sum += arr[i];
    }
    return sum;
}

int main_functions()
{
    Examples();
    Print<3>();
    int arr[]{3, 1, 9, 7};
    // int (&ref)[5] = arr ;
    int sum = Sum(arr);
    std::cout << sum << std::endl;
    return 0;
}

// template classes
template <typename T, int size>
class Stack
{
    T m_Buffer[size];
    int m_Top{-1};

public:
    Stack() = default;
    Stack(const Stack<T, size> &obj)
    {
        m_Top = obj.m_Top;
        for (int i = 0; i <= m_Top; ++i)
        {
            m_Buffer[i] = obj.m_Buffer[i];
        }
    }
    void Push(const T &elem)
    {
        m_Buffer[++m_Top] = elem;
    }
    void Pop();
    const T &Top() const
    {
        return m_Buffer[m_Top];
    }
    bool IsEmpty()
    {
        return m_Top == -1;
    }
    /*
    Shorthand notation for class name as return type,
    because it appears inside the class
    */
    static Stack Create();
};

template <typename T, int size>
void Stack<T, size>::Pop()
{
    --m_Top;
}

template <typename T, int size>
/*
Longhand notation for class name as return type,
because it appears outside the class
*/
Stack<T, size> Stack<T, size>::Create()
{
    return Stack<T, size>();
}

int main()
{
    main_functions();
    /*
    The template parameter list is part of the type of class.
    The following code will not work.
    Stack<float, 9> s = Stack<float, 10>::Create();
                 ^
    */
    Stack<const char *, 5> ss2;
    ss2.Push("Hello");

    Stack<float, 10> s = Stack<float, 10>::Create();
    s.Push(3);
    s.Push(1);
    s.Push(6);
    s.Push(9);
    auto s2(s);
    while (!s2.IsEmpty())
    {
        std::cout << s2.Top() << " ";
        s2.Pop();
    }
    Stack<char *, 5> ss;
    ss.Push("Hello");
    return 0;
}