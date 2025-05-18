#include <iostream>
#include <vector>
int main()
{
    int arr[10];
    int *ptr = new int[10];
    for (int i = 0; i < 10; ++i)
    {
        ptr[i] = i * 10;
    }

    std::vector<int> data{1, 2, 3};
    for (int i = 0; i < 5; ++i)
    {
        data.push_back(i * 10);
    }
    // Access
    data[0] = 100;
    std::cout << data[0] << "<-- data[0]\n";
    //}
    for (auto x : data)
    {
        std::cout << x << " ";
    }

    auto it = data.begin();
    std::cout << "\n data.begin() --> " << *it << std::endl;

    ++it;

    --it;
    it = it + 5;
    // Delete
    it = data.begin();
    data.erase(it); //<-- erase the first element 100
    std::cout << std::endl;
    for (auto x : data)
    {
        std::cout << x << " ";
    }
    // Insert
    it = data.begin() + 5;
    data.insert(it, 500);
    std::cout << std::endl;
    for (auto x : data)
    {
        std::cout << x << " ";
    }

    /*
    100<-- data[0]
    100 2 3 0 10 20 30 40
     data.begin() --> 100

    2 3 0 10 20 30 40
    2 3 0 10 20 500 30 40
    */
    return 0;
}