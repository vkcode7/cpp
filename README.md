# CPP
## Containers library
The Containers library is a generic collection of class templates and algorithms that allow programmers to easily implement common data structures like queues, lists and stacks. There are two(until C++11)three(since C++11) classes of containers:
sequence containers,
associative containers, and
unordered associative containers,(since C++11)

each of which is designed to support a different set of operations.

## Sequence containers
Sequence containers implement data structures which can be accessed sequentially. - 
array (static contiguous memory), 
vector (dynamic contiguous memory), 
forward_list (singly linked list), 
list (doubly linked list), 
deque (double ended queue)

## Associative containers
Associative containers implement sorted data structures that can be quickly searched (O(log n) complexity).
set - collection of unique keys, sorted by keys
multiset -same as set but multiple keys of same value are allowed
map - collection of key-value pairs, sorted by keys, keys are unique
multimap - same as map but multiple keys of same value are allowed

## Unordered associative containers (since C++11)
Unordered associative containers implement unsorted (hashed) data structures that can be quickly searched (O(1) average, O(n) worst-case complexity).
unordered_set - collection of unique keys, hashed by keys
unordered_multiset -same as set but multiple keys of same value are allowed
unordered_map - collection of key-value pairs, hashed by keys, keys are unique
unordered_multimap - same as map but multiple keys of same value are allowed

## Container adaptors
Container adaptors provide a different interface for sequential containers.
stack: adapts a container to provide stack (LIFO data structure)
queue: adapts a container to provide queue (FIFO data structure)
priority_queue: adapts a container to provide priority queue

flat_set: (C++23): adapts a container to provide a collection of unique keys, sorted by keys
flat_map:(C++23):adapts two containers to provide a collection of key-value pairs, sorted by unique keys
flat_multiset: (C++23): adapts a container to provide a collection of keys, sorted by keys
flat_multimap: (C++23): adapts two containers to provide a collection of key-value pairs, sorted by keys

## C++ Containers and operations
https://www.sandordargo.com/blog/2023/11/15/most-important-complexities

First, let’s see what are the most important containers you’ll likely deal with in a coding interview, what are the underlying data structures and what are the related complexities. My goal is not to give you a deep analysis, just to provide you with the most necessary information, then you can do your own research.

## Sequence containers - array, vector, list, forward_list, deque

### std::array
std::array is a fixed-size array, storing objects in contiguous memory locations.
- accessing the first element: with front() which has a complexity of O(1)
- accessing the last element: with back() which has a complexity of O(1)
- accessing a random element: with at() or with operator[] both have a complexity of O(1)

```c++
#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <string>
 
int main()
{
    // Construction uses aggregate initialization
    std::array<int, 3> a1{{5, 4, 3}}; 
// Double-braces required prior to C++11  
    std::array<int, 3> a2 = {1, 2, 3}; // Double braces never required
 
    // Container operations are supported
    std::sort(a1.begin(), a1.end());
    for (const auto& k : a1)
        std::cout << k << ' ';
    std::cout << '\n';
 
    // Ranged for loop is supported
    std::array<std::string, 2> a3{"E", "\u018E"};
    for (const auto& s : a3)
        std::cout << s << ' ';
    std::cout << '\n';
 
    // Deduction guide for array creation (since C++17)
    [[maybe_unused]] std::array a4{3.0, 1.0, 4.0}; // std::array<double, 3>
 
    // Behavior of unspecified elements is the same as with built-in arrays
    [[maybe_unused]] std::array<int, 2> a5; // No list init, a5[0] and a5[1]
                                            // are default initialized
    [[maybe_unused]] std::array<int, 2> a6{}; // List init, both elements are value
                                              // initialized, a6[0] = a6[1] = 0
    [[maybe_unused]] std::array<int, 2> a7{1}; // List init, unspecified element is value
                                               // initialized, a7[0] = 1, a7[1] = 0
}
```

### std::list
std::list is a container that supports fast insertion and removal, but doesn’t support fast random access. It is usually implemented as a doubly-linked list. std::forward_list is similar, but implemented with a singly-linked list, so it’s more space efficient, but it supports iteration only in one direction
- accessing the first element: with front() which has a complexity of O(1)
- accessing the last element: with back() which has a complexity of O(1) (not supported by std::forward_list)
- accessing a random element: not supported
- inserting at the front: with push_front() which has a complexity of O(1)
- inserting at the back: with push_back() which has a complexity of O(1) (not supported by std::forward_list)
- inserting at a random location: with insert() which has a complexity of O(1) for one element, and complexity of O(n) for multiple elements, where n is the number of elements to be inserted (insert_after for std::forward_list)
- removing an item from the front: with pop_front() which has a complexity of O(1)
- removing an item from the back: with pop_back() which has a complexity of O(1) (not supported by std::forward_list)
- removing an item from a random location: with erase() which has a complexity of O(1) for one element, and a complexity of O(n) for multiple elements, where n is the number of elements to be erased (erase_after for std::forward_list)

```c++
#include <algorithm>
#include <iostream>
#include <list>
 
int main()
{
    // Create a list containing integers
    std::list<int> l = {7, 5, 16, 8};
 
    // Add an integer to the front of the list
    l.push_front(25);
    // Add an integer to the back of the list
    l.push_back(13);
 
    // Insert an integer before 16 by searching
    auto it = std::find(l.begin(), l.end(), 16);
    if (it != l.end())
        l.insert(it, 42);
 
    // Print out the list
    std::cout << "l = { ";
    for (int n : l)
        std::cout << n << ", ";
    std::cout << "};\n";
}
```

### std::forward_list
std::forward_list is a container that supports fast insertion and removal of elements from anywhere in the container. Fast random access is not supported. It is implemented as a singly-linked list. Compared to std::list this container provides more space efficient storage when bidirectional iteration is not needed.
Important functions: front, pop_front, push_front, swap, empty, clear, insert_after, emplace_front, emplace_after

### std::vector
std::vector is a dynamically sized sequence container, where the elements are stored contiguously. Random access is cheap, as well as operations at the end, unless reallocation is required.

- accessing the first element: with front() which has a complexity of O(1)
- accessing the last element: with back() which has a complexity of O(1)
- accessing a random element: with at() or with operator[] both have a complexity of O(1)
- inserting at the front: with insert() which has a complexity of O(n+m) where n is the number of elements to insert and m is the size of the container
- inserting at the back: with push_back() which has a complexity of amortized O(1)
- inserting at a random location: with insert() which has a complexity of O(n+m) where n is the number of elements to insert and m is the distance between the elements to insert and the end of the container
- removing an item from the front: with erase() which has a complexity of O(n+m) where n is the number of elements erased (calls to the destructor) and m is the number of assignments to make - the size of the elements left in the vector
- removing an item from the back: with pop_back() which has a complexity of O(1)
- removing an item from a random location: with erase() which has a complexity of O(n+m) where n is the number of elements erased (calls to the destructor) and m is the number of assignments to make - at least the number of elements after the last erased item, worst the size of the whole container left

```c++
#include <iostream>
#include <vector>
 
int main()
{
    // Create a vector containing integers
    std::vector<int> v = {8, 4, 5, 9};
 
    // Add two more integers to vector
    v.push_back(6);
    v.push_back(9);
 
    // Overwrite element at position 2
    v[2] = -1;
 
    // Print out the vector
    for (int n : v)
        std::cout << n << ' ';
    std::cout << '\n';
}
```

### std::deque
std::deque (double-ended queue) is an indexed sequence container that allows fast insertion and deletion at both its beginning and its end. In addition, insertion and deletion at either end of a deque never invalidates pointers or references to the rest of the elements.
As opposed to std::vector, the elements of a deque are not stored contiguously: typical implementations use a sequence of individually allocated fixed-size arrays, with additional bookkeeping, which means indexed access to deque must perform two pointer dereferences, compared to vector's indexed access which performs only one.
The storage of a deque is automatically expanded and contracted as needed. Expansion of a deque is cheaper than the expansion of a std::vector because it does not involve copying of the existing elements to a new memory location. On the other hand, deques typically have large minimal memory cost; a deque holding just one element has to allocate its full internal array (e.g. 8 times the object size on 64-bit libstdc++; 16 times the object size or 4096 bytes, whichever is larger, on 64-bit libc++).

The complexity (efficiency) of common operations on deques is as follows:
- Random access - constant O(1).
- Insertion or removal of elements at the end or beginning - constant O(1).
- Insertion or removal of elements - linear O(n).

Important methods are front(), back(), pop_front() and pop_back().

```c++
#include <deque>
#include <iostream>
 
int main()
{
    // Create a deque containing integers
    std::deque<int> d = {7, 5, 16, 8};
 
    // Add an integer to the beginning and end of the deque
    d.push_front(13);
    d.push_back(25);
 
    // Iterate and print values of deque
    for (int n : d)
        std::cout << n << ' ';
    std::cout << '\n';
}
```

## Associative containers - set, map, multiset, multimap

### std::set

std::set is an associative container that contains a sorted set of unique objects of type Key. Sorting is done using the key comparison function Compare. Search, removal, and insertion operations have logarithmic complexity. Sets are usually implemented as Red–black trees

Noted functions: empty, size, max_size, count, erase, find, insert, emplace, clear

```c++
#include <set>
#include <iostream>
 
int main()
{
    std::set<int> c = {1, 2, 3, 4, 1, 2, 3, 4};
 
    auto print = [&c]
    {
        std::cout << "c = { ";
        for (int n : c)
            std::cout << n << ' ';
        std::cout << "}\n";
    };
    print();
 
    std::cout << "Erase all odd numbers:\n";
    for (auto it = c.begin(); it != c.end();)
    {
        if (*it % 2 != 0)
            it = c.erase(it);
        else
            ++it;
    }
    print();
 
    std::cout << "Erase 1, erased count: " << c.erase(1) << '\n';
    std::cout << "Erase 2, erased count: " << c.erase(2) << '\n';
    std::cout << "Erase 2, erased count: " << c.erase(2) << '\n';
    print();
}
```

### std::map
std::map is a sorted associative container providing search, removal and insertion at a logarithmic complexity. They are usually implemented as red-black trees.
- accessing an element: with at() or with operator[] both have a complexity of O(log n) where n is the size of the container
- inserting an element at a random location: with insert() or with operator[] both have a complexity of O(log n) where n is the size of the container. With insert() you can insert multiple elements, and then the complexity becomes O(m * log n), where m is the number of elements to insert. insert() can also take a position as a hint where to insert. If the insertion happens there then the complexity is amortized O(1) otherwise O(log n)
- removing an item: with erase() which has a complexity of amortized O(1) if the erasure happens with an iterator, otherwise it’s O(log(n) + m) where n is the size of the container and m is the number of elements to remove
- finding an element: with find() which has a complexity of O(log n) where n is the size of the container

```c++
#include <iostream>
#include <map>
#include <string>
#include <string_view>
 
void print_map(std::string_view comment, const std::map<std::string, int>& m)
{
    std::cout << comment;
    // Iterate using C++17 facilities
    for (const auto& [key, value] : m)
        std::cout << '[' << key << "] = " << value << "; ";
 
// C++11 alternative:
//  for (const auto& n : m)
//      std::cout << n.first << " = " << n.second << "; ";
//
// C++98 alternative:
//  for (std::map<std::string, int>::const_iterator it = m.begin(); it != m.end(); ++it)
//      std::cout << it->first << " = " << it->second << "; ";
 
    std::cout << '\n';
}
 
int main()
{
    // Create a map of three (string, int) pairs
    std::map<std::string, int> m{{"CPU", 10}, {"GPU", 15}, {"RAM", 20}};
 
    print_map("1) Initial map: ", m);
 
    m["CPU"] = 25; // update an existing value
    m["SSD"] = 30; // insert a new value
    print_map("2) Updated map: ", m);
 
    // Using operator[] with non-existent key always performs an insert
    std::cout << "3) m[UPS] = " << m["UPS"] << '\n';
    print_map("4) Updated map: ", m);
 
    m.erase("GPU");
    print_map("5) After erase: ", m);
 
    std::erase_if(m, [](const auto& pair){ return pair.second > 25; });
    print_map("6) After erase: ", m);
    std::cout << "7) m.size() = " << m.size() << '\n';
 
    m.clear();
    std::cout << std::boolalpha << "8) Map is empty: " << m.empty() << '\n';
}
```

### std::multiset
std::multiset is an associative container that contains a sorted set of objects of type Key. Unlike set, multiple keys with equivalent values are allowed. 
```c++
   std::multiset<int> c = {1, 2, 3, 4, 1, 2, 3, 4};
    auto print = [&c]
    {
        std::cout << "c = { ";
        for (int n : c)
            std::cout << n << ' ';
        std::cout << "}\n";
    };
    print();
```
find - Finds an element with key equivalent to key. If there are several elements with the requested key in the container, any of them may be returned.

### std::multimap
std::multimap is an associative container that contains a sorted list of key-value pairs, while permitting multiple entries with the same key. 

## Unordered associative containers (c++11 onwards) - unordered_set, unordered_map, unordered_multiset, unordered_multimap

### std::unordered_set
std::unordered_set is an associative container that contains a set of unique objects of type Key. Search, insertion, and removal have average constant-time complexity.
Internally, the elements are not sorted in any particular order, but organized into buckets. Which bucket an element is placed into depends entirely on the hash of its value. This allows fast access to individual elements, since once a hash is computed, it refers to the exact bucket the element is placed into.
Container elements may not be modified (even by non const iterators) since modification could change an element's hash and corrupt the container.
Apart from usual functions, it also has bucket and hash related functions such as bucket_count (number of buckets), bucket_size (items in a bucket with index n), bucket (bucket for a key), hash_function (function used to hash the key)

### std::unordered_map
std::unordered_map is an unsorted associative container optimized for search, removal and insertion which come at a constant time complexity. std::unordered_map is a hash map internally.
- accessing an element: with at() or with operator[] both have a complexity of O(1) on average and O(n) at worst where n is the size of the container
- inserting an element at a random location: with insert() or with operator[] both have a complexity of O(1) on average and O(n) at worst, where n is the size of the map. If m elements are inserted then the average case is O(m) and the worst case is O(m * n + n)
- removing an item: with erase() which has a complexity of amortized O(1) if the erasure happens with an iterator, otherwise, on average it’s O(m) where m is the number of elements to remove, worst case it’s O(n) where n is the size of the container
- finding an element: with find() it’s O(1) on average and in the worst case it’s O(n) where n is the size of the container

### std::unordered_multiset
std::unordered_multiset is an associative container that contains set of possibly non-unique objects of type Key.

### std::unordered_multimap
std::unordered_multimap is an unordered associative container that supports equivalent keys (an unordered_multimap may contain multiple copies of each key value) and that associates values of another type with the keys. 

## Thread safety
1. All container functions can be called concurrently by different threads on different containers. More generally, the C++ standard library functions do not read objects accessible by other threads unless those objects are directly or indirectly accessible via the function arguments, including the this pointer.
2. All const member functions can be called concurrently by different threads on the same container. In addition, the member functions begin(), end(), rbegin(), rend(), front(), back(), data(), find(), lower_bound(), upper_bound(), equal_range(), at(), and, except in associative containers, operator[], behave as const for the purposes of thread safety (that is, they can also be called concurrently by different threads on the same container). More generally, the C++ standard library functions do not modify objects unless those objects are accessible, directly or indirectly, via the function's non-const arguments, including the this pointer.
3. Different elements in the same container can be modified concurrently by different threads, except for the elements of std::vector<bool> (for example, a vector of std::future objects can be receiving values from multiple threads).
4. Iterator operations (e.g. incrementing an iterator) read, but do not modify the underlying container, and may be executed concurrently with operations on other iterators on the same container, with the const member functions, or reads from the elements. Container operations that invalidate any iterators modify the container and cannot be executed concurrently with any operations on existing iterators even if those iterators are not invalidated.
5. Elements of the same container can be modified concurrently with those member functions that are not specified to access these elements. More generally, the C++ standard library functions do not read objects indirectly accessible through their arguments (including other elements of a container) except when required by its specification.
6. In any case, container operations (as well as algorithms, or any other C++ standard library functions) may be parallelized internally as long as this does not change the user-visible results (e.g. std::transform may be parallelized, but not std::for_each which is specified to visit each element of a sequence in order).
