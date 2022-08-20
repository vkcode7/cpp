#include <iostream>
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>

/*
The Containers library is a generic collection of class templates and algorithms that allow programmers to easily implement common data structures like queues, lists and stacks. 
There are two (until C++11), three (since C++11) classes of containers:
- sequence containers (array, vector, deque, list, forward_list),
- associative container (map, set, multimap, multiset), and
- unordered associative containers, (since C++11) (unordered_map, _set, _multimap, _multiset)

The following containers are defined in the current revision of the C++ standard: array, vector, list, forward_list, deque. Each of these containers implements different algorithms for data storage, which means that they have different speed guarantees for different operations:[1]

array - implements a compile-time non-resizable array.
vector - implements an array with fast random access and an ability to automatically resize when appending elements.
deque - implements a double-ended queue with comparatively fast random access.
list - implements a doubly linked list.
forward_list - implements a singly linked list.

Container adaptors
- stack - LIFO
- queue - FIFO
- priority queue 
*/

void Array()
{
    std::array<int, 5> arr{3, 1, 8, 5, 9};
    for (int i = 0; i < arr.size(); ++i)
    {
        arr[i] = i;
    }
    auto itr = arr.begin();
    for (auto x : arr)
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    arr.data();
}

void Vector()
{
    std::vector<int> coll{1, 2, 3, 4};
    for (int i = 0; i < 5; ++i)
    {
        coll.push_back(i * 10);
        std::cout << coll.size() << std::endl;
    }
    coll[0] = 100;
    // for (int i = 0; i< coll.size(); ++i) {
    //	std::cout << coll[i] << " ";
    // }
    auto itr = coll.begin();
    while (itr != coll.end())
    {
        std::cout << *itr++ << " ";
    }
    coll.insert(coll.begin(), 700);
    coll.erase(coll.end() - 5);
    coll.pop_back();
}

void Deque()
{
    std::deque<int> coll;
    for (int i = 0; i < 5; ++i)
    {
        coll.push_back(i * 10);
    }
    for (int i = 0; i < 5; ++i)
    {
        coll.push_front(i * 10);
    }
    coll[0] = 100;
    // for (int i = 0; i< coll.size(); ++i) {
    //	std::cout << coll[i] << " ";
    // }
    auto itr = coll.begin();
    while (itr != coll.end())
    {
        std::cout << *itr++ << " ";
    }
    coll.insert(coll.begin(), 700);
    coll.erase(coll.end() - 5);
    coll.pop_back();
    coll.pop_front();
}

void List()
{
    std::list<int> coll;
    for (int i = 0; i < 5; ++i)
    {
        coll.push_back(i * 10);
    }
    auto itr = coll.begin();
    while (itr != coll.end())
    {
        std::cout << *itr++ << " ";
    }
    itr = coll.begin();
    coll.insert(itr, 800);
    coll.erase(itr);
}

void ForwardList()
{
    std::forward_list<int> coll;
    for (int i = 0; i < 10; ++i)
    {
        coll.push_front(i);
    }
    for (auto x : coll)
    {
        std::cout << x << " ";
    }
    coll.insert_after(coll.begin(), 10);
    coll.erase_after(coll.begin());
}

int main()
{
    Array();
    Vector();
    Deque();
    List();
    ForwardList();
    return 0;
}