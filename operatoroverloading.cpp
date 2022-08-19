#include <iostream>
#include <memory>

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
    Integer &operator++();
    Integer operator++(int);
    bool operator==(const Integer &a) const;

    // Copy assignment
    Integer &operator=(const Integer &a);
    // Move assignment
    Integer &operator=(Integer &&a);
    Integer operator+(const Integer &a) const;

    void operator()();
};

Integer operator+(int x, const Integer &y);
std::ostream &operator<<(std::ostream &out, const Integer &a);
std::istream &operator>>(std::istream &input, Integer &a);

class IntPtr
{
    Integer *m_p;

public:
    IntPtr(Integer *p) : m_p(p)
    {
    }
    ~IntPtr()
    {
        delete m_p;
    }
    Integer *operator->()
    {
        return m_p;
    }
    Integer &operator*()
    {
        return *m_p;
    }
};
void CreateInteger()
{
    std::unique_ptr<Integer> p(new Integer);
    // auto p2(p);
    (*p).SetValue(3);
    // std::cout << p->GetValue() << std::endl;
}
void Process(Integer val)
{
}

int main()
{
    using namespace std;
    Integer a(3);
    auto b(std::move(a));
    // std::cout << a << std::endl;
    Process(std::move(a));
    cout << "End of Program\n";
    return 0;
}

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

Integer &Integer::operator++()
{
    ++(*m_pInt);
    return *this;
    // TODO: insert return statement here
}

Integer Integer::operator++(int)
{
    Integer temp(*this);
    ++(*m_pInt);
    return temp;
}

bool Integer::operator==(const Integer &a) const
{
    return *m_pInt == *a.m_pInt;
}

Integer &Integer::operator=(const Integer &a)
{
    if (this != &a)
    {
        delete m_pInt;
        m_pInt = new int(*a.m_pInt);
    }
    return *this;
}

Integer &Integer::operator=(Integer &&a)
{
    if (this != &a)
    {
        delete m_pInt;
        m_pInt = a.m_pInt;
        a.m_pInt = nullptr;
    }
    return *this;
}

Integer Integer::operator+(const Integer &a) const
{
    Integer temp;
    *temp.m_pInt = *m_pInt + *a.m_pInt;
    return temp;
}

void Integer::operator()()
{
    std::cout << *m_pInt << std::endl;
}

Integer operator+(int x, const Integer &y)
{
    Integer temp;
    temp.SetValue(x + y.GetValue());
    return temp;
}
std::ostream &operator<<(std::ostream &out, const Integer &a)
{
    out << a.GetValue();
    return out;
}
std::istream &operator>>(std::istream &input, Integer &a)
{
    int x;
    input >> x;
    a.SetValue(x);
    return input;
}
