#include <iostream>
#include <sstream>
int main()
{

    // stringstream use
    int a{5}, b{6};
    int sum = a + b;
    std::stringstream ss;
    ss << "Sum of " << a << " & " << b << " is :" << sum << std::endl;
    std::string s = ss.str();
    std::cout << s << std::endl;
    ss.str("");
    ss << sum;                       // convert int to stringstream
    auto ssum = std::to_string(sum); // int to string
    std::cout << "ssum is " << ssum << ", ss is " << ss.str() << std::endl;

    std::string data = "12 89 21";
    a = 0;
    std::stringstream ss_ints;
    ss_ints.str(data);
    while (ss_ints >> a)
    {
        std::cout << a << std::endl;
    }
    int x = std::stoi("54");

    // string as input
    std::string first;
    std::string last;

    std::cout << "Enter FName ";
    std::getline(std::cin, first);

    std::cout << "\nEnter LName ";
    std::getline(std::cin, last);

    std::string fullname = first + " " + last;
    std::cout << fullname;

    // usig literals
    using namespace std::string_literals;
    auto sname = "Gracie Singh"s; // s in the end is literal

    unsigned int value = 100u; // u is literal

    sname.insert(7, "Kumar ");
    std::cout << "\n"
              << sname;
    sname.erase(7, 6); // sname.clear();
    std::cout << "\n"
              << sname << "\n";

    for (auto &ch : sname)
        std::cout << ch;

    // Search
    auto pos = sname.find("Singh", 0);
    if (pos != std::string::npos)
    {
        // Found
        std::cout << "\nFound at, " << pos << " " << sname.substr(pos);
    }

    return 0;

    /*
    Sum of 5 & 6 is :11

    ssum is 11, ss is 11
    12
    89
    21
    Enter FName Yuvir
    Enter LName Singh
    Yuvir Singh
    Gracie Kumar Singh
    Gracie Singh
    Gracie Singh
    Found at, 7 Singh
    */
}