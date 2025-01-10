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

#### unique_ptr
```c++
#include <iostream>
#include <memory>

int main() {
    // Create a unique pointer to an integer with value 42
    std::unique_ptr<int> ptr(new int(42));
    
    // Access the managed object
    std::cout << "Value: " << *ptr << std::endl;
    
    // Modify the managed object
    *ptr = 100;
    std::cout << "New value: " << *ptr << std::endl;
    
    // Release ownership and deallocate the managed object
    ptr.reset();
    
    return 0;
}
```

To get the raw pointer use
```c++
    // Get the raw pointer
    int *rawPtr = ptr.get();
```
   
Array version
```c++
int main() {
    // Create a unique pointer to an array of integers with 5 elements
    std::unique_ptr<int[]> arrayPtr(new int[5]);

    // Initialize elements of the array
    for (int i = 0; i < 5; ++i) {
        arrayPtr[i] = i * 10;
    }

    // Access and print elements of the array
    for (int i = 0; i < 5; ++i) {
        std::cout << "Element " << i << ": " << arrayPtr[i] << std::endl;
    }

    // Get the raw pointer
    int *rawPtr = arrayPtr.get();

    // Use the raw pointer to modify an element
    rawPtr[2] = 100;

    // Access and print elements of the array again
    for (int i = 0; i < 5; ++i) {
        std::cout << "Element " << i << ": " << arrayPtr[i] << std::endl;
    }

    return 0;
}
```

**make_unique:**
```c++
    // Create a unique pointer to an integer with value 42
    auto ptr = std::make_unique<int>(42);
    
    // Use the unique pointer
    std::cout << *ptr << std::endl; // Output: 42

    // Create a unique pointer to a MyClass object
    auto ptr = std::make_unique<MyClass>(10, 15, 20); //constructor takes 3 int values

    // Create a unique pointer to an array of integers
    auto ptr = std::make_unique<int[]>(5);
    
    // Initialize elements of the array
    for (int i = 0; i < 5; ++i) {
        ptr[i] = i;
    }
```

#### shared_ptr
```c++
    // Create a shared pointer to an integer with value 42
    std::shared_ptr<int> ptr = std::make_shared<int>(42);
    
    // Create another shared pointer pointing to the same object
    std::shared_ptr<int> ptr2 = ptr;
```

#### reference_wrapper
std::reference_wrapper is a class template provided by the C++ Standard Library. It acts as a wrapper around a reference to an object and provides additional functionalities like assignment and comparison. Flexibility:

std::reference_wrapper is often used in situations where you need to store or manipulate references in containers like std::vector or std::map, or when you want to pass references as function arguments to algorithms or function templates that require copyable types. 

```c++
#include <iostream>
#include <functional> // Include for std::reference_wrapper

void increment(std::reference_wrapper<int> numRef) {
    numRef.get()++;
}

int main() {
    int x = 5;
    std::reference_wrapper<int> ref(x); // Creating a std::reference_wrapper
    
    std::cout << "Original value of x: " << x << std::endl; // Output: Original value of x: 5
    
    increment(ref); // Pass the reference wrapper to a function
    
    std::cout << "Updated value of x: " << x << std::endl; // Output: Updated value of x: 6

    int y = 10;
    // Change the reference dynamically to y
    ref = std::ref(y);

    // Example with std::vector
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::vector<std::reference_wrapper<int>> vec_refs;

    // Store references to elements in the vector
    for (int& elem : vec) {
        vec_refs.push_back(std::ref(elem));
    }

    // Modify the original vector and observe changes through references
    vec[0] = 100;

    return 0;
}
```

R-Value Reference - '&&'
An rvalue reference is a reference that can bind to temporary objects or to objects that are about to be moved. It's a feature introduced in C++11 to enable move semantics and perfect forwarding.
```c++
#include <iostream>

void foo(int&& x) {
    std::cout << "Received rvalue reference: " << x << std::endl;
    x = 100;
}

int main() {
    int a = 10; // 'a' is an lvalue
    //foo(a); <= Error: expects an rvalue for 1st argument
    foo(5); // 5 is an rvalue, it's a temporary object
    foo(std::move(a)); // 'a' is explicitly cast to an rvalue using std::move
    std::cout << "a is now: " << a << std::endl;

    return 0;
}

Output:
Received rvalue reference: 5
Received rvalue reference: 10
a is now: 100
```
This is what happens at low level:

- A temporary variable of type int is created on the stack of main. It's assigned with value 5.
- The address of the temporary is passed to fn.
- fn writes 100 by that address, changing the value of the temporary.
- The function exits, the temporary dies at the end of the full expression involving the call.
