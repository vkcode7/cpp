C++ is a ***strongly typed langugae*** as every variable is a type that never changes.<br>
Basic/aka Intrinsic types are:<br>
<mark>char, short, int, long, long long</mark><br>
unsigned <= unisgned versions of above, with unsigned we can store 2x of signed plus zero<br>
signed <= signed versions, default except for "char"

other types: float (32b), double (64b), long double (80 bits), bool

#### RANGE BASED for loop

```c++
// Illustration of range-for loop
// using CPP code
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

// Driver
int main()
{
    // Iterating over whole array
    vector<int> v = { 0, 1, 2, 3, 4, 5 };
    for (auto i : v)
        cout << i << ' ';

    cout << '\n';

    // Printing string characters
    string str = "Geeks";
    for (char c : str)
        cout << c << ' ';

    cout << '\n';

    // Printing keys and values of a map
    map<int, int> MAP({ { 1, 1 }, { 2, 2 }, { 3, 3 } });
    for (auto i : MAP)
        cout << '{' << i.first << ", " << i.second << "}\n";
}
```

c++ 17 or higher
```c++
for (auto& [key, value]: myMap) {
    cout << key << " has value " << value << std::endl;
}
```

#### assert() macro (only works in Debug mode; ignored in Release)
If this expression evaluates to 0 or false, this causes an assertion failure that terminates the program. It doesnt go into release so there is no performance penalty in released code.

#### static_assert
if a program error is detected at compile time, the error is displayed and compilation will stop.  

#### C++ Memory new/delete
new is an operator, it can initialize memory and call constructor.
```c++
int *p = new int;
int *parr = new int[10];

delete p;
delete[] parr;
```

### Smart Pointers
c++ 11 introduced 3 new types - unique_ptr, shared_ptr and weak_ptr
