#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void EndMessage()
{
    std::cout << std::endl
              << R"(End of Program)" << std::endl;
}

int main()
{
    using namespace std;
    atexit(EndMessage); // EndMessage will execute at end of program
    char buff[512];
    // cout << "What is your name?";
    // cin.getline(buff, 64, '\n');
    // cout << "Your name is:" << buff << endl;

    // range based for loop
    cout << endl;
    int arr[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    for (const auto &x : arr)
    {
        cout << x << " ";
    }
    cout << endl;
    for (auto x : {1, 2, 3, 4, 5})
    {
        cout << x << " ";
    }

    // auto
    auto x = 10;
    const auto var = x;
    // Deduced to reference
    auto &var1 = x;

    // Deduced to a pointer. * is not necessary
    auto *ptr1 = &x;
    auto ptr2 = &x;
    cout << "\n"
         << "ptr1 points to " << *ptr1 << endl;
    cout << "\n"
         << "ptr2 points to " << *ptr2 << endl;

    // malloc and calloc, calloc inits memory with 0s
    // int *p = (int*)calloc(5, sizeof(int));
    int *p = (int *)malloc(5 * sizeof(int));
    if (p == NULL)
    {
        printf("Failed to allocate memory\n");
        return 0;
    }
    *p = 5;
    printf("%d\n", *p);
    free(p);

    // new arrays
    int *pA = new int[5];
    for (int i = 0; i < 5; ++i)
    {
        pA[i] = i;
        cout << pA[i] << " ";
    }
    delete[] pA;

    // strings
    char *pS = new char[40];
    strncpy(pS, "C++", 4);
    std::cout << endl
              << pS << std::endl;
    delete[] pS;

    // 2 Dimesnional Array
    auto TwoDArray = []()
    {
        int *p1 = new int[3];
        int *p2 = new int[3];

        int **pData = new int *[2];
        pData[0] = p1;
        pData[1] = p2;

        pData[0][1] = 2;
        cout << "pData[0][1]: " << pData[0][1] << endl;
        delete[] p1; // delete []pData[0]
        delete[] p2; // delete []pData[1]

        delete[] pData;
    };
    TwoDArray();

    int data[2][3] = {
        1, 2, 3,
        4, 5, 6}; // 1,2,3,4,5,6

    for (auto row : {0, 1})
    {
        cout << endl;
        for (auto x : data[row])
            cout << x << " ";
    }

    // r-value reference
    int &lref = x;    // this is lvalue reference as x is l-value
    int &&rref = 100; // this is r-value ref to a temp data
    rref = 200;
    cout << "rref: " << rref;

    return 0;
}