#include <iostream>
#include <string>

#pragma once
#include <iostream>
class Integer
{
    int *m_pInt;

public:
    // Default constructor
    Integer();

    // Parameterized constructor
    Integer(int value);

    // Copy constructor
    Integer(const Integer &obj);

    // Move constructor
    Integer(Integer &&obj);

    int GetValue() const;
    void SetValue(int value);
    ~Integer();
};

Integer::Integer()
{
    std::cout << "Integer()" << std::endl;
    m_pInt = new int(0);
}

Integer::Integer(int value)
{
    std::cout << "Integer(int)" << std::endl;
    m_pInt = new int(value);
}

Integer::Integer(const Integer &obj)
{
    std::cout << "Integer(const Integer&)" << std::endl;
    m_pInt = new int(*obj.m_pInt);
}

Integer::Integer(Integer &&obj)
{
    std::cout << "Integer(int&&)" << std::endl;
    m_pInt = obj.m_pInt;
    obj.m_pInt = nullptr;
}

int Integer::GetValue() const
{
    return *m_pInt;
}

void Integer::SetValue(int value)
{
    *m_pInt = value;
}

Integer::~Integer()
{
    std::cout << "~Integer()" << std::endl;
    delete m_pInt;
}

class Employee
{
    std::string m_Name;
    Integer m_Id;

public:
    // Employee(const std::string &name, const Integer &id) :
    //	m_Name{ name },
    //	m_Id{ id } {
    //	std::cout << "Employee(const std::string &name, const Integer &id)" << std::endl;
    // }
    template <typename T1, typename T2>
    Employee(T1 &&name, T2 &&id) : m_Name{std::forward<T1>(name)},
                                   m_Id{std::forward<T2>(id)}
    {
        std::cout << "Employee(std::string &&name,  Integer &&id)" << std::endl;
    }
};

template <typename T1, typename T2>
Employee *Create(T1 &&a, T2 &&b)
{
    return new Employee(std::forward<T1>(a), std::forward<T2>(b));
}
int main()
{
    // Employee emp1{ "Umar", Integer{100} };
    /*std::string name = "Umar";
    Employee emp2{ name, 100 };
    Integer val{ 100 };
    Employee emp3{ std::string{"Umar"}, val };*/
    auto emp = Create("Umar", Integer{100});
    return 0;
}

void Print()
{
    std::cout << std::endl;
}

// Template parameter pack
template <typename T, typename... Params>
// Function parameter pack
void Print(T &&a, Params &&...args)
{
    // std::cout << sizeof...(args) << std::endl;
    // std::cout << sizeof...(Params) << std::endl;
    std::cout << a;
    if (sizeof...(args) != 0)
    {
        std::cout << ",";
    }
    // We can forward a function parameter pack
    Print(std::forward<Params>(args)...);
}

int main()
{
    // Print({ 1,2.5,3,4 });
    // Print(1, 2.5, 3, "4");
    Integer val{1};
    Print(0, val, Integer{2});
    return 0;
}