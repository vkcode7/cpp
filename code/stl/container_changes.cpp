#include <iostream>
#include <deque>
#include <vector>
#include <fstream>
#include <filesystem>
#include <list>
#include <set>

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
    Integer(Integer &&obj) noexcept;
    int GetValue() const;
    void SetValue(int value);
    ~Integer();
    Integer &operator++();
    Integer operator++(int);
    bool operator==(const Integer &a) const;

    // Copy assignment
    Integer &operator=(const Integer &a);
    // Move assignment
    Integer &operator=(Integer &&a) noexcept;
    Integer operator+(const Integer &a) const;

    void operator()();
};
Integer operator+(int x, const Integer &y);
std::ostream &operator<<(std::ostream &out, const Integer &a);
std::istream &operator>>(std::istream &input, Integer &a);

void Emplace()
{
    std::vector<Integer> vInt;
    Integer val{5};
    // vInt.push_back(val) ;
    vInt.emplace_back(val);

    std::vector<std::pair<int, std::string>> data;
    data.push_back(std::pair<int, std::string>{100, "C++"});

    data.emplace_back(100, "C++");
}
void Shrink()
{
    std::vector<int> vInt;
    for (size_t i = 0; i < 100; ++i)
    {
        vInt.emplace_back(i);
    }
    std::cout << "Size:" << vInt.size() << '\n';
    std::cout << "Capacity:" << vInt.capacity() << '\n';
    vInt.erase(vInt.begin(), vInt.end() - 10);
    std::cout << "After erase & shrink_to_fit\n";
    vInt.shrink_to_fit();
    std::cout << "Size:" << vInt.size() << '\n';
    std::cout << "Capacity:" << vInt.capacity() << '\n';
}

void VectorFunctions()
{
/*
    //need c++17
    std::ifstream input{"main.cpp"};
    if (!input)
    {
        std::cout << "Could not open file\n";
        return;
    }
    auto size = std::filesystem::file_size("main.cpp");
    // std::vector<char> buffer ;
    std::string buffer;
    buffer.resize(size);
    // char * buff = new char[size]{};
    input.read(buffer.data(), size);
    std::cout << buffer.data() << '\n';
    // delete []buff ;
*/
}

template <typename Container>
void Print(const Container &cont, const char *msg = "")
{
    std::cout << msg << '\n';
    for (auto a : cont)
    {
        std::cout << a << '\n';
    }
}
void Erase()
{
    std::vector<int> vInt{1, 2, 3, 4, 2};
    std::list<int> lstInt{1, 2, 3, 4, 2};
    std::deque<int> deqInt{1, 2, 3, 4, 2};

    /* c++ 20
    std::erase(vInt, 2);
    std::erase(lstInt, 2);
    std::erase(deqInt, 2);
    */
    Print(vInt, "vector");
    Print(lstInt, "list");
    Print(deqInt, "deque");
}

int main()
{
    std::set<int> data{1,2,6,3} ;
    data.emplace_hint(data.begin(),0) ;
    auto it = data.find(6) ;
    if(it != data.end()) {
        std::cout << "Found\n" ;
    }
    auto found = data.contains(6) ;
    if(found){
        std::cout << "Found\n" ;
    }

    std::set<std::string> names{"Omar", "Ayaan", "Raihaan"};
    auto it = names.find("Omar");
    auto name = *it;
    name[0] = 'U';
    names.erase(it);
    names.insert(name);

    //auto node = names.extract(it); //c++17
    //node.value()[0] = 'U';
    //names.insert(std::move(node));

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

Integer::Integer(Integer &&obj) noexcept
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
    std::cout << "operator=(const Integer &)" << std::endl;
    if (this != &a)
    {
        delete m_pInt;
        m_pInt = new int(*a.m_pInt);
    }
    return *this;
}

Integer &Integer::operator=(Integer &&a) noexcept
{
    std::cout << "operator=(Integer &&)" << std::endl;
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