
#include <iostream>
#include <set>
#include <functional>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <string>

/*
Associative containers implement sorted data structures that can be quickly searched (O(log n) complexity).
    - asso containers are: set, map, multiset, multimap
    set: collection of unique keys, sorted by keys
    map: collection of key-value pairs, sorted by keys, keys are unique
    multiset: collection of keys, sorted by keys
    multimap: collection of key-value pairs, sorted by keys

Unordered associative containers (since c++11) implement unsorted (hashed) data structures that can be quickly searched (O(1) amortized, O(n) worst-case complexity).
    - unordered asso containers are: unordered_set, _map, _multiset and _multimap
    unordered_set: collection of unique keys, hashed by keys
    unordered_map: collection of key-value pairs, hashed by keys, keys are unique
    unordered_multiset: collection of keys, hashed by keys
    unordered_multimap: collection of key-value pairs, hashed by keys
*/

// in a set the keys must be unique, while a multiset permits duplicate keys
void MultiSet()
{
    std::multiset<int, std::greater<int>> s{8, 2, 0, 9, 5};
    // No push_back, only insert as elements are ordered automatically
    s.insert(1);

    // Only multiset allows duplicates
    s.insert(3);
    s.insert(3);
    s.insert(3);

    auto itr = s.begin();
    //*itr = 3;
    while (itr != s.end())
    {
        std::cout << *itr++ << " ";
    }
    std::cout << std::endl;

    // Erase by key or position
    s.erase(0);
    s.erase(s.begin());
    itr = s.find(9);
    if (itr != s.end())
    {
        std::cout << "Element found" << std::endl;
    }
    else
    {
        std::cout << "Not found" << std::endl;
    }
    auto found = s.equal_range(3);
    while (found.first != found.second)
    {
        std::cout << *found.first++ << " ";
    }
}

// in a map the keys must be unique, while a multimap permits duplicate keys

void MultiMap()
{
    std::multimap<int, std::string> m{
        {1, "Superman"},
        {2, "Batman"},
        {3, "Green Lantern"}};
    m.insert(std::pair<int, std::string>(8, "Aquaman"));
    m.insert(std::make_pair(6, "Wonder Woman"));
    m.insert(std::make_pair(6, "Powergirl"));

    // Only map support [] operator
    /*m[0] = "Flash";
    m[0] = "Kid Flash";*/
    auto itr = m.begin();
    m.erase(0);
    // returns a pair that contains begin & end of the range.
    auto found = m.equal_range(6);
    while (found.first != found.second)
    {
        std::cout << found.first->first << ":" << found.first->second << std::endl;
        found.first++;
    }

    // std::cout << itr->first << ":" << itr->second << std::endl;

    // Avoid using [] for searching as it will insert an empty element if a key cannot be found
    // std::cout << "10:" << m[10] << std::endl;

    /*for (const auto &x : m) {
        std::cout << x.first << ":" << x.second << std::endl;
    }*/

    // Lookup by key
    /*itr = m.find(1);
    if (itr != m.end()) {
        std::cout << "Found:" << itr->second << std::endl;
    }
    else {
        std::cout << "Not found" << std::endl;
    }*/
}

void UnMultiSet()
{
    std::unordered_multiset<std::string> coll;
    // elements are stored based on the hash, but in unspecified order,
    coll.insert("Hulk");
    coll.insert("Batman");
    coll.insert("Green Lantern");
    coll.insert("The Flash");
    coll.insert("Wonder Woman");
    coll.insert("Iron man");
    coll.insert("Iron man");
    coll.insert("Iron man");
    coll.insert("Wolverine");
    coll.insert("Dr. Strange");
    coll.insert("Hawkman");

    for (const auto x : coll)
    {
        std::cout << "Bucket #:" << coll.bucket(x) << " contains :" << x << std::endl;
    }
    std::cout << "Bucket count:" << coll.bucket_count() << std::endl;
    std::cout << "Number of elements:" << coll.size() << std::endl;
    std::cout << "Load factor:" << coll.load_factor() << std::endl;
}

void UnMultiMap()
{
    std::unordered_multimap<std::string, std::string> coll;
    // Only unordered_map support [] operator
    /*coll["Batman"] = "Brue Wayne";
    coll["Superman"] = "Clark Kent";
    coll["Hulk"] = "Bruce Banner";*/
    coll.insert(std::make_pair("Batman", "Bruce Wayne"));
    coll.insert(std::make_pair("Batman", "Matches Malone"));
    coll.insert(std::make_pair("Superman", "Clark Kent"));
    coll.insert(std::make_pair("Hulk", "Bruce Banner"));

    for (const auto &x : coll)
    {
        std::cout << "Bucket #:" << coll.bucket(x.first) << " ->" << x.first << ":" << x.second << std::endl;
    }
}

class Employee
{
    std::string m_Name;
    int m_Id;

public:
    Employee(const std::string &n, int id) : m_Name(n), m_Id(id)
    {
    }
    const std::string &GetName() const
    {
        return m_Name;
    }
    int GetId() const
    {
        return m_Id;
    }
};

// Custom hash function
struct EmployeeHash
{
    size_t operator()(const Employee &emp) const
    {
        auto s1 = std::hash<std::string>{}(emp.GetName());
        auto s2 = std::hash<int>{}(emp.GetId());
        return s1 ^ s2;
    }
};
// Custom function object for equality
struct EmpEquality
{
    bool operator()(const Employee &e1, const Employee e2) const
    {
        return e1.GetId() == e2.GetId();
    }
};

void Hashes()
{
    std::hash<std::string> h;
    // Hash is computed by the function object
    std::cout << "Hash:" << h("Hello") << std::endl;

    std::unordered_set<Employee, EmployeeHash, EmpEquality> coll;
    coll.insert(Employee("Umar", 123));
    coll.insert(Employee("Bob", 678));
    coll.insert(Employee("Joey", 612));

    for (const auto &x : coll)
    {
        std::cout << x.GetId() << ":" << x.GetName() << std::endl;
    }
}

int main()
{
    MultiSet();
    MultiMap();
    UnMultiSet();
    UnMultiMap();
    Hashes();
    return 0;
}