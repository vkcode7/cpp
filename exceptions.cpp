#include <iostream>
#include <memory>
#include <vector>
#include <random>
class Test
{
public:
    Test() { std::cout << "Test():Acquire resources" << std::endl; }
    ~Test() { std::cout << "~Test():Release resources" << std::endl; }
};

void ProcessRecords(int count)
{
    /*
    Compare this code with the code that uses RAII.
    */
    Test *t = new Test;
    if (count < 10)
        throw std::out_of_range("Count should be greater than 10");

    int *p = new int[count];
    int *pArray = (int *)malloc(count * sizeof(int));
    if (pArray == nullptr)
    {
        throw std::runtime_error("Failed to allocate memory");
    }
    // Process the records
    for (int i = 0; i < count; ++i)
    {
        pArray[i] = i;
    }
    // Unreachable code in case of an exception
    free(pArray);
    delete[] p;
    delete t;
}
int main()
{
    try
    {
        // ProcessRecords(std::numeric_limits<int>::max());
        ProcessRecords(5);
    }
    catch (std::runtime_error &ex)
    {
        std::cout << ex.what() << std::endl;
    }
    catch (std::out_of_range &ex)
    {
        std::cout << ex.what() << std::endl;
    }
    catch (std::bad_alloc &ex)
    {
        std::cout << ex.what() << std::endl;
    }

    /*
    std::exception is the base class for all standard
    exception classes. It can be used as a handler if
    the exception handling code is same for all child
    class exception objects. This should be in the last
    or it will catch the derived exceptions
    */
    catch (std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
    }

    /*
    All-catch handler. Avoid as it does not give any
    information about the exception, so it is difficult
    to take any preventative action
    */
    catch (...)
    {
        std::cout << "Exception" << std::endl;
    }
    return 0;
}
