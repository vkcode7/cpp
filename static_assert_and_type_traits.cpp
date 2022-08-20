// static assert and type traits (is_floating_type etc)
#include <type_traits>
template <typename T>
T Divide(T a, T b)
{
    static_assert(std::is_floating_point<T>::value, "Only floating point type supported");
    if (std::is_floating_point<T>::value == false)
    {
        std::cout << "Use floating point types only\n";
        return 0;
    }
    return a / b;
}

template <typename T>
void Check(T &&)
{
    std::cout << std::boolalpha;
    std::cout << "Is reference?" << std::is_reference<T>::value << std::endl;
    std::cout << "After removing:" << std::is_reference<typename std::remove_reference<T>::type>::value << std::endl;
}

int main_static_assert_and_type_traits()
{
    std::cout
        << std::boolalpha
        << "Is integer?" << std::is_integral<int>::value << std::endl;

    std::cout << Divide(5.1, 7.4) << std::endl;

    Check(5);
    int value{};
    Check(value);
}
