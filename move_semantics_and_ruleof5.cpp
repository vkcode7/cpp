#include <iostream>
class Integer
{
    int *m_pInt;

public:
    // Default constructor
    Integer()
    {
        std::cout << "Integer(): default cons" << std::endl;
        m_pInt = new int(0);
    }

    // Parameterized constructor
    Integer(int value)
    {
        std::cout << "Integer(int): parametrized cons" << std::endl;
        m_pInt = new int(value);
    }

    // Copy constructor
    Integer(const Integer &obj)
    {
        std::cout << "Integer(const Integer&): copy cons" << std::endl;
        m_pInt = new int(*obj.m_pInt);
    }

    // Move constructor
    Integer(Integer &&obj)
    {
        std::cout << "Integer(Integer&&): move cons" << std::endl;
        m_pInt = obj.m_pInt;
        obj.m_pInt = nullptr;
    }

    // Copy assignment
    Integer &operator=(const Integer &obj)
    {
        std::cout << "operator=(const Integer& obj): copy assignment" << std::endl;
        if (this == &obj)
        {
            return *this;
        }
        delete m_pInt;
        m_pInt = new int(*obj.m_pInt);
        return *this;
    }

    // Move assignment
    Integer &operator=(Integer &&obj)
    {
        std::cout << "operator=(Integer&& obj): move assignment" << std::endl;
        if (this == &obj)
        {
            return *this;
        }
        delete m_pInt;
        m_pInt = obj.m_pInt;
        obj.m_pInt = nullptr;
        return *this;
    }

    int GetValue() const
    {
        return *m_pInt;
    }

    void SetValue(int value)
    {
        *m_pInt = value;
    }

    void SetValue(float) = delete; // float is not allowed

    ~Integer()
    {
        if (m_pInt)
        {
            std::cout << "~Integer(" << *m_pInt << "): destructor" << std::endl;
        }
        else
            std::cout << "~Integer(nullptr): destructor" << std::endl;
        delete m_pInt;
    }
};

class Number
{
    Integer m_Value{};

public:
    Number() = default;
    Number(int value) : m_Value{value}
    {
    }
    /*Number(const Number &n):m_Value{n.m_Value}{
    }*/
    /*~Number(){
    }*/
    Number(Number &&n) = default;
    Number(const Number &n) = default;
    Number &operator=(Number &&) = default;
    Number &operator=(const Number &) = default;
};
Number CreateNumber(int num)
{
    Number n{num};
    return n;
}

void TestMove(Integer &&intObj)
{
    std::cout << "TestMove::intObj.GetValue(): " << intObj.GetValue() << std::endl;
}

int main()
{
    // default constructor
    Number n1;

    // copy constructor
    auto n2 = n1;

    // copy assignment
    n2 = n1;

    std::cout << "---calling auto n3{CreateNumber(2)};" << std::endl;
    // parameterized constructor
    auto n3{CreateNumber(2)};

    std::cout << "---calling n3 = CreateNumber(3);" << std::endl;
    // move assignment: operator=(Integer&& obj)
    n3 = CreateNumber(3);

    std::cout << "---calling Integer i1(100)" << std::endl;
    Integer i1(4);

    std::cout << "---calling auto i2 = std::move<Integer&>(i1);" << std::endl;
    // move constructor
    auto i2 = std::move<Integer &>(i1);
    i2.SetValue(5);
    std::cout << "i2.GetValue(): " << i2.GetValue() << std::endl;
    // std::cout << i1.GetValue() << std::endl; //<-- this will cause error

    std::cout << "\nCalling TestMove" << std::endl;
    TestMove(std::move<Integer &>(i2)); // no constructor or op called
    std::cout << "\Done TestMove" << std::endl;

    // error: note: candidate: 'void Integer::SetValue(float)' <deleted>
    // i2.SetValue(240.1);

    /*
    OUTPUT:
    Integer(): default cons
    Integer(const Integer&): copy cons
    operator=(const Integer& obj): copy assignment
    ---calling auto n3{CreateNumber(2)};
    Integer(int): parametrized cons
    ---calling n3 = CreateNumber(3);
    Integer(int): parametrized cons
    operator=(Integer&& obj): move assignment
    ~Integer(nullptr): destructor
    ---calling Integer i1(100)
    Integer(int): parametrized cons
    ---calling auto i2 = std::move<Integer&>(i1);
    Integer(Integer&&): move cons
    i2.GetValue(): 5

    Calling TestMove
    TestMove::intObj.GetValue(): 5
    Done TestMove
    ~Integer(5): destructor
    ~Integer(nullptr): destructor
    ~Integer(3): destructor
    ~Integer(0): destructor
    ~Integer(0): destructor
    */
}
