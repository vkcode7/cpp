# C++

C++ is a ***strongly typed langugae*** as every variable is a type that never changes.<br>
Basic/aka Intrinsic types are:<br>
char, short, int, long, long long<br>
unsigned <= unisgned versions of above, with unsigned we can store 2x of signed plus zero<br>
signed <= signed versions, default except for "char"

other types: float, double, long double, bool

char can have -128 to 127 or 0 to 255 (unsigned char)<br>
typically float is 32, double is 64 and long double is 80 bits<br>

Literals can be qualified with a suffix explicitly such as 2, 2u, 2l, 2ul (unisgned long), 2.0 (double), 2.0f, 2.0l (long double)<br>
long is 32 bit on 32 bit platform and 64 on 64-bit platform.

***Narrowing:*** In C++ 11 one can enclose values in {} and they wont be lost in assignment.<br>
```c++
long l = {1234....123}; //either error or OK if supported
int i = {3.14}; //error as truncation not allowed
unsigned u1 = -2; //OK
unisgned u2 = {-2}; //error
```

***Type Modifiers:*** signed/unsigned<br>
***Type Qualifiers:*** const, volatile, static<br>
***Types:***
- char, bool <= 1 byte
- wchar_t, short <= 2 bytes
- int, long, float <= 4 bytes
- long long, double <= 8 bytes

```c++
<climits> or <limit.h> //contain limits such as INT_MIN
<cfloat>/<float.h> //contain floating limits 

//Copy initialization: should be used for primitive types for code clarity<br>
int a = 1;

//Uniform initialization: should be used for user defined types for code clarity<br>
char e1[8] = {"hello"};
char *pei = new char[8]{"hello"};
```

### Limits
<table>
	<tr><td>INT_MIN</td><td>FLT_MIN<td>DBL_MIN</td><td>LDBL_MIN</td></tr>
	<tr><td>INT_MAX</td><td>FLT_MAX<td>DBL_MAX</td><td>LDBL_MAX</td></tr>
</table>

<table>
	<tr><td>CHAR_MIN<td>SCHAR_MIN</td><td>SHRT_MIN</td><td>LONG_MIN</td><td>ULONG_MIN</td><td>LLONG_MIN</td></tr>
</table>

##### Data/Scope Hiding
Variable in inner scope hides the one in outer scope:

```c++
#include <iostream>
using namespace std;
int a = 10;
int main() {
    {
        int a = 5; //a#1
        std::cout << a << endl;
        {
            a = 3; //a#1 assigned
            int a = 4; //a#2
            std::cout << a << endl;
        }
        
        std::cout << a << endl;
    }
    
    std::cout << a << endl;
        
    return 0;
}

Output:
5
4
3
10
```

#### Operators in C++
https://en.wikipedia.org/wiki/Operators_in_C_and_C%2B%2B

#### L-value
An lvalue has an address that your program can access. Examples of lvalue expressions include variable names, including const variables, array elements, function calls that return an lvalue reference, bit-fields, unions, and class members.
```c++
// lvalues_and_rvalues2.cpp
int main()
{
    int i, j, *p;

    // Correct usage: the variable i is an lvalue and the literal 7 is a prvalue.
    i = 7;

    // Incorrect usage: The left operand must be an lvalue (C2106).`j * 4` is a prvalue.
    7 = i; // C2106
    j * 4 = 7; // C2106

    // Correct usage: the dereferenced pointer is an lvalue.
    *p = i;

    // Correct usage: the conditional operator returns an lvalue.
    ((i < 3) ? i : j) = 7;

    // Incorrect usage: the constant ci is a non-modifiable lvalue (C3892).
    const int ci = 7;
    ci = 9; // C3892
}
```

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

    // the initializer may be a braced-init-list
    for (int n : { 0, 1, 2, 3, 4, 5 })
        cout << n << ' ';

    cout << '\n';

    // Iterating over array
    int a[] = { 0, 1, 2, 3, 4, 5 };
    for (int n : a)
        cout << n << ' ';

    cout << '\n';

    // Just running a loop for every array
    // element
    for (int n : a)
        cout << "In loop" << ' ';

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

Using std::begin() and std::end()
```c++
// INTEGER VECTOR EXAMPLE
// CPP program to illustrate
// Implementation of begin() function
#include <iostream>
#include <vector>
using namespace std;

int main()
{
	// declaration of vector container
	vector<int> myvector{ 1, 2, 3, 4, 5 };

	// using begin() to print vector
	for (auto it = myvector.begin();
		it != myvector.end(); ++it)
		cout << ' ' << *it;
	return 0;
}
```

#### assert() macro
If this expression evaluates to 0 or false, this causes an assertion failure that terminates the program. It doesnt go into release so there is no performance penalty in released code.

```c
## assert.h
00031 #ifdef NDEBUG //Non DEBUG Code
00032 # define assert(EX)
00033 #else
00034 # define assert(EX) (void)((EX) || (__assert (#EX, __FILE__, __LINE__),0))
00035 #endif
```
Look at line 34, it implies that if assert() returns false then execute the second condition in OR.

```c++
/* assert example */
#include <stdio.h>      /* printf */
#include <assert.h>     /* assert */

void print_number(int* myInt) {
  assert (myInt!=NULL);
  printf ("%d\n",*myInt);
}

int main ()
{
  int a=10;
  int * b = NULL;
  int * c = NULL;

  b=&a;

  print_number (b);
  print_number (c);

  return 0;
}

output:
10
```

#### C Memory
malloc/realloc/calloc/free are used by C. calloc is same as malloc except that it initializes memory with 0. They return a void pointer.

#### C++ Memory new/delete
new is an operator, it can initialize memory and call constructor.
```c++
int *p = new int;
int *parr = new int[];

delete p;
delete[] parr;
```

#### noexcept c++ 11
if an exception is thrown, program will terminate
```c++
double sqroot(double x) noexcept {}
```

#### static_assert
if a program error is detected at compile time, the error is displayed and compilation will stop.  

### Pointers
Strategies to minimize pointer related errors:
- Use containers - map/vector
- Encapsulate in classes - constructors and destructors. This is called RAII (Resource Acquisition is Instantiation)
- Smart pointers

### Smart Pointers
c++ 11 introduced 3 new types - unique_ptr, shared_ptr and weak_ptr

#### std::unique_ptr
std::unique_ptr is a smart pointer introduced in C++11 that manages the ownership of dynamically allocated objects. Unlike std::shared_ptr, which allows for shared ownership, std::unique_ptr enforces single ownership semantics, meaning only one std::unique_ptr can own the managed object at a time. When the std::unique_ptr is destroyed or reset, it automatically deallocates the managed object, providing a simple and safe way to manage dynamic memory.

Here are some key characteristics and features of std::unique_ptr:

Single Ownership: A std::unique_ptr represents exclusive ownership of the managed object. When a std::unique_ptr is moved to another std::unique_ptr, ownership of the managed object is transferred, and the original std::unique_ptr becomes empty (nullptr).

Automatic Resource Management: When a std::unique_ptr goes out of scope or is explicitly reset, it automatically deallocates the managed object using the destructor of the object type. This helps prevent memory leaks and resource management errors.

Lightweight: std::unique_ptr is a lightweight smart pointer with minimal overhead compared to std::shared_ptr. It typically has the size of a raw pointer and does not require additional control blocks to manage reference counts.

Support for Custom Deleters: std::unique_ptr supports custom deleters, which are callable objects that specify how the managed object should be deallocated. This allows for flexible resource management, such as freeing resources allocated with malloc() or closing file handles.

Move Semantics: std::unique_ptr supports move semantics, allowing for efficient transfer of ownership between std::unique_ptr instances. This enables efficient resource management and avoids unnecessary copying of managed objects.

Copy ctor of a unique_ptr is deleted and therefore a unique_ptr can be passed around as a reference

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
#include <iostream>
#include <memory>

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

#### custom deleter
```c++
#include <iostream>
#include <memory>

// Custom deleter for managing dynamically allocated integers
struct IntDeleter {
    void operator()(int* ptr) const {
        std::cout << "Deleting integer..." << std::endl;
        delete ptr; // Delete the dynamically allocated integer
    }
};

int main() {
    // Create a unique pointer to an integer with a custom deleter
    std::unique_ptr<int, IntDeleter> intPtr(new int(42));

    // Access and modify the integer value
    std::cout << "Original value: " << *intPtr << std::endl;
    *intPtr = 100;
    std::cout << "New value: " << *intPtr << std::endl;

    // The integer will be automatically deleted when intPtr goes out of scope

    return 0;
}
```

#### shared_ptr

std::shared_ptr is a smart pointer provided by the C++ Standard Library. It enables shared ownership of dynamically allocated objects, meaning multiple std::shared_ptr instances can point to the same object. The object is automatically deleted when the last std::shared_ptr pointing to it is destroyed or reset, ensuring proper memory management and preventing memory leaks.<br>
Thread-Safe: Operations on std::shared_ptr instances are thread-safe, meaning multiple threads can safely access and modify them concurrently.

```c++
#include <iostream>
#include <memory>

int main() {
    // Create a shared pointer to an integer with value 42
    std::shared_ptr<int> ptr = std::make_shared<int>(42);
    
    // Create another shared pointer pointing to the same object
    std::shared_ptr<int> ptr2 = ptr;

    // Use the shared pointers
    std::cout << "ptr value: " << *ptr << std::endl; // Output: ptr value: 42
    std::cout << "ptr2 value: " << *ptr2 << std::endl; // Output: ptr2 value: 42
    
    // Reset one of the shared pointers
    ptr.reset();
    
    // Use the remaining shared pointer
    std::cout << "ptr2 value after reset: " << *ptr2 << std::endl; // Output: ptr2 value after reset: 42
    
    return 0;
}
```

#### weak_ptr - resolves cyclical references
std::weak_ptr is another smart pointer provided by the C++ Standard Library, designed to observe objects managed by std::shared_ptr without affecting their lifetimes. Here are the key points about std::weak_ptr:

Non-owning Observation: std::weak_ptr holds a non-owning ("weak") reference to an object managed by std::shared_ptr. It does not contribute to the reference count of the managed object.

Prevents Circular References: Helps prevent circular references among std::shared_ptr instances, which can lead to memory leaks. By using std::weak_ptr, you can break cycles of shared ownership.

Access with lock(): To access the object managed by a std::weak_ptr, you must use the lock() function, which returns a std::shared_ptr. This operation is safe and returns an empty std::shared_ptr if the object has been deleted.

Expired Check: You can check if the object managed by a std::weak_ptr is still valid using the expired() function. If the object has been deleted, expired() returns true; otherwise, it returns false.

Thread Safety: Operations on std::weak_ptr are thread-safe, making it safe to use in multithreaded environments.
```c++
#include <iostream>
#include <memory>

int main() {
    // Create a shared pointer to an integer
    std::shared_ptr<int> sharedPtr = std::make_shared<int>(42);

    // Create a weak pointer from the shared pointer
    std::weak_ptr<int> weakPtr = sharedPtr;

    // Check if the weak pointer is expired
    if (auto lockedPtr = weakPtr.lock()) {
        std::cout << "Weak pointer is not expired. Value: " << *lockedPtr << std::endl;
    } else {
        std::cout << "Weak pointer is expired." << std::endl;
    }

    // Resetting the shared pointer
    sharedPtr.reset();

    // Check if the weak pointer is expired after resetting the shared pointer
    if (weakPtr.expired()) {
        std::cout << "Weak pointer is expired." << std::endl;
    } else {
        std::cout << "Weak pointer is not expired." << std::endl;
    }

    return 0;
}
```

#### make_unique
std::make_unique is a C++11 feature that is used to create a std::unique_ptr with dynamically allocated memory. It provides a safer and more concise way to allocate memory compared to using new directly.

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

### make_shared
std::make_shared is another feature introduced in C++11, and it's used to create a std::shared_ptr with dynamically allocated memory. Like std::make_unique, it provides a safer and more concise way to allocate memory compared to using new directly.

```c++
    // Create a shared pointer to an integer with value 42
    auto ptr = std::make_shared<int>(42);
```

#### reference_wrapper
The main difference between the reference operator (&) and std::reference_wrapper lies in their purpose, flexibility, and usage scenarios.

Purpose:

The reference operator (&) is used to create references to objects in C++. It directly creates a reference to an existing object.
std::reference_wrapper is a class template provided by the C++ Standard Library. It acts as a wrapper around a reference to an object and provides additional functionalities like assignment and comparison.
Flexibility:

References created using the reference operator (&) are fixed and cannot be changed after initialization. Once a reference is created, it always refers to the same object.
std::reference_wrapper provides more flexibility as it allows you to create, copy, and change references dynamically during the program execution. You can also reset or reassign a std::reference_wrapper to refer to a different object.
Usage Scenarios:

The reference operator (&) is commonly used when passing parameters to functions, returning values from functions, and creating aliases for existing objects. It's particularly useful when you want to avoid unnecessary copying of objects.
std::reference_wrapper is often used in situations where you need to store or manipulate references in containers like std::vector or std::map, or when you want to pass references as function arguments to algorithms or function templates that require copyable types.
In summary, while both the reference operator and std::reference_wrapper allow you to work with references in C++, they serve different purposes and offer different levels of flexibility. The reference operator is used to create fixed references to existing objects, while std::reference_wrapper provides a more flexible wrapper around references that can be dynamically managed and manipulated during program execution.

```c++
void increment(int& num) {
    num++;
}

int main() {
    int x = 5;
    int& ref = x; // Creating a reference using the reference operator
    
    std::cout << "Original value of x: " << x << std::endl; // Output: Original value of x: 5
    
    increment(ref); // Pass the reference to a function
    
    std::cout << "Updated value of x: " << x << std::endl; // Output: Updated value of x: 6
    
    return 0;
}
```

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
    
    return 0;
}
```

```c++
    int x = 5, y = 10;
    std::reference_wrapper<int> ref(x); // Create a std::reference_wrapper to x initially

    // Print the initial value using the reference wrapper
    print(ref);

    // Change the reference dynamically to y
    ref = std::ref(y);
```

```c++
#include <iostream>
#include <vector>
#include <map>
#include <functional> // Include for std::reference_wrapper

int main() {
    // Example with std::vector
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::vector<std::reference_wrapper<int>> vec_refs;

    // Store references to elements in the vector
    for (int& elem : vec) {
        vec_refs.push_back(std::ref(elem));
    }

    // Modify the original vector and observe changes through references
    vec[0] = 100;
    std::cout << "Values in vector after modification:" << std::endl;
    for (int& ref : vec_refs) {
        std::cout << ref << " ";
    }
    std::cout << std::endl;

    // Example with std::map
    std::map<std::string, int> myMap = {{"one", 1}, {"two", 2}, {"three", 3}};
    std::map<std::string, std::reference_wrapper<int>> map_refs;

    // Store references to values in the map
    for (auto& pair : myMap) {
        map_refs.emplace(pair.first, std::ref(pair.second));
    }

    // Modify the original map and observe changes through references
    myMap["two"] = 200;
    std::cout << "Values in map after modification:" << std::endl;
    for (const auto& pair : map_refs) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    return 0;
}
```


### Macro Equivalents - they are risky, have no regards to namespaces / scopes
Inline Functions

```c++
// Macro
#define SQUARE(x) ((x) * (x))

// Inline function
inline int square(int x) {
    return x * x;
}
```

const
```c++
// Macro
#define PI 3.14159

// Const variable
const double pi = 3.14159;
```

templates
```c++
// Macro
#define max(a, b) ((a) > (b) ? (a) : (b))

// Template function
template<typename T>
T max(T a, T b) {
    return a > b ? a : b;
}
```

constexpr
```c++
// Macro
#define SQUARE(x) ((x) * (x))

// Constexpr function
constexpr int square(int x) {
    return x * x;
}
```

#### R-Value Reference - '&&'
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
## virtual keyword
In C++, the virtual keyword is used in a base class to declare a member function that can be overridden in derived classes. When a member function is declared as virtual in a base class, it allows derived classes to provide their own implementation of that function.<br>

Here's the basic role of virtual keyword in a base class:<br>

- Polymorphism: It enables polymorphic behavior, which means that the appropriate member function to be called is determined at runtime based on the type of object.
- Dynamic Dispatch: When you call a virtual function through a base class pointer or reference, the function of the most-derived class's type is called.
- Overriding: Derived classes can provide their own implementation of a virtual function. If a derived class provides an implementation for a virtual function declared in the base class, it overrides the base class's implementation.
```c++
#include <iostream>

class Base {
public:
    virtual void show() {
        std::cout << "Base class show()" << std::endl;
    }
};

class Derived : public Base {
public:
    void show() override {
        std::cout << "Derived class show()" << std::endl;
    }
};

int main() {
    Base *basePtr;
    Derived derivedObj;

    basePtr = &derivedObj; // Pointer of Base class points to Derived class object

    // Virtual function call through base class pointer
    basePtr->show(); // Output will be "Derived class show()"

    return 0;
}
```

### virtual destructor
In C++, a virtual destructor is a destructor declared in a base class that can be overridden in derived classes. It's used to ensure proper destruction of objects when they are deleted through a pointer to the base class that points to a derived class object.<br>

Here's why and how you use a virtual destructor:<br>

Proper Cleanup in Inheritance Hierarchies: When you have a base class and one or more derived classes, and you delete an object of a derived class through a pointer to the base class, you want all the destructors in the inheritance hierarchy to be called. If the destructor in the base class is not virtual, only the destructor of the base class will be called, potentially leading to resource leaks in the derived classes. <br>
Dynamic Binding: A virtual destructor enables dynamic binding, allowing the correct destructor to be called based on the object's dynamic type at runtime.
```c++
#include <iostream>

class Base {
public:
    virtual ~Base() {
        std::cout << "Base destructor" << std::endl;
    }
};

class Derived : public Base {
public:
    ~Derived() override {
        std::cout << "Derived destructor" << std::endl;
    }
};

int main() {
    Base* ptr = new Derived();
    delete ptr; // Calls Derived destructor first, then Base destructor
    return 0;
}
```

## A complete class - Rule of 5 [If a class has ownership on pointers or resources, you must provide these 5]
- copy ctor, copy assignment
- move ctor, move assignment
- dtor

Rule of 0: if a class doesnt have any pointer etc, do not cretate these and compiler will provide the default ones.
  
```c++
#include <iostream>

class MyClass {
private:
    int* data;

public:
    // Default constructor
    MyClass() : data(nullptr) {
        std::cout << "Default constructor called." << std::endl;
    }

    // Constructor with an integer parameter
    explicit MyClass(int value) : data(new int(value)) {
        std::cout << "Parameterized constructor called with value: " << *data << std::endl;
    }

    // Copy constructor
    MyClass(const MyClass& other) : data(new int(*other.data)) {
        std::cout << "Copy constructor called. Copied value: " << *data << std::endl;
    }

    // Move constructor
    MyClass(MyClass&& other) noexcept : data(other.data) {
        other.data = nullptr;
        std::cout << "Move constructor called. Moved value: " << *data << std::endl;
    }

    // Destructor
    ~MyClass() {
        if (data != nullptr) {
            std::cout << "Destructor called. Deleting data: " << *data << std::endl;
            delete data;
        }
    }

    // Copy assignment operator
    MyClass& operator=(const MyClass& other) {
        if (this != &other) {
            delete data;
            data = new int(*other.data);
            std::cout << "Copy assignment operator called. Copied value: " << *data << std::endl;
        }
        return *this;
    }

    // Move assignment operator
    MyClass& operator=(MyClass&& other) noexcept {
        if (this != &other) {
            delete data;
            data = other.data;
            other.data = nullptr;
            std::cout << "Move assignment operator called. Moved value: " << *data << std::endl;
        }
        return *this;
    }
};

void Test1(MyClass a){} ////Copy constructor called
void Test2(MyClass &a){}
void Test3(MyClass &&a){}
void Test4(MyClass *pa){}

MyClass Test5(MyClass &a){
    return a;    //Copy constructor called
}

MyClass Test6(MyClass &a){
    return std::move(a);    //Move constructor called
}

MyClass& Test7(MyClass &a){
    return a;    //Copy constructor called
}

MyClass&& Test8(MyClass &a){
    return std::move(a);    //Move constructor called
}

int main() {
    // Test all constructors and assignment operators
    MyClass obj1; // Default constructor
    MyClass obj2(42); // Parameterized constructor
    MyClass obj3(obj2); // Copy constructor
    MyClass obj4 = std::move(obj3); // Move constructor
    MyClass obj5; // Default constructor
    obj5 = obj2; // Copy assignment operator
    MyClass obj6; // Default constructor
    obj6 = std::move(obj5); // Move assignment operator
    
    std::cout << "calling TestX methods" << std::endl;

    Test1(obj2); //Copy constructor called. Copied value: 42
    Test2(obj2);
    Test3(std::move(obj2));
    Test4(&obj2);
    
    std::cout << "calling Test5" << std::endl;
    MyClass obj7 = Test5(obj2); //Copy constructor called
    MyClass obj8 = Test6(obj2); //Move constructor called
    MyClass obj9 = Test7(obj6); //Copy constructor called
    MyClass obj10 = Test8(obj6); //Move constructor called

    return 0;
}

Output:
Default constructor called.
Parameterized constructor called with value: 42
Copy constructor called. Copied value: 42
Move constructor called. Moved value: 42
Default constructor called.
Copy assignment operator called. Copied value: 42
Default constructor called.
Move assignment operator called. Moved value: 42
calling TestX methods
Copy constructor called. Copied value: 42
Destructor called. Deleting data: 42
calling Test5
Copy constructor called. Copied value: 42
Move constructor called. Moved value: 42
Copy constructor called. Copied value: 42
Move constructor called. Moved value: 42
Destructor called. Deleting data: 42
Destructor called. Deleting data: 42
Destructor called. Deleting data: 42
Destructor called. Deleting data: 42
Destructor called. Deleting data: 42
```

#### Delegating Ctor
Delegating constructors are a feature introduced in C++11 that allows one constructor of a class to call another constructor of the same class to perform initialization. Delegating constructors allow you to reuse initialization logic across multiple constructors, leading to cleaner and more maintainable code.

```c++
#include <iostream>

class MyClass {
private:
    int value;

public:
    // Target constructor
    MyClass(int v) : value(v) {
        std::cout << "Target constructor called. Value: " << value << std::endl;
    }

    // Delegating constructor
    MyClass() : MyClass(0) {
        std::cout << "Delegating constructor called." << std::endl;
    }

    // Another delegating constructor
    MyClass(bool b) : MyClass(b ? 1 : 0) {
        std::cout << "Another delegating constructor called." << std::endl;
    }
};

int main() {
    MyClass obj1(42); // Calls target constructor
    MyClass obj2; // Calls delegating constructor
    MyClass obj3(true); // Calls another delegating constructor

    return 0;
}

Output:
Target constructor called. Value: 42
Delegating constructor called.
Target constructor called. Value: 0
Another delegating constructor called.
Target constructor called. Value: 1
```

#### Explicit Ctor - prevents implicit conversions from the constructor's parameter type to the class type.
```c++
#include <iostream>

class MyClass {
private:
    int value;

public:
    // Explicit constructor
    explicit MyClass(int v) : value(v) {
        std::cout << "Explicit constructor called. Value: " << value << std::endl;
    }

    int getValue() const {
        return value;
    }
};

int main() {
    // Implicit conversion prevented due to explicit constructor
    // MyClass obj = 42; // Error: Conversion from 'int' to 'MyClass' is ambiguous
    // MyClass obj = MyClass(42); // OK: Explicitly construct MyClass object

    // Explicit conversion required for explicit constructor
    MyClass obj1(42); // OK: Direct initialization
    MyClass obj2 = MyClass(42); // OK: Explicit constructor called

    std::cout << "Value of obj1: " << obj1.getValue() << std::endl;
    std::cout << "Value of obj2: " << obj2.getValue() << std::endl;

    return 0;
}
```
Note: If a destructor throws an exception and it is not caught within the destructor itself, the std::terminate() function will be called, leading to program termination.

To specify that a destructor is noexcept, you can use the noexcept specifier explicitly in the destructor declaration. 

#### subscript operator (operator[]) 
```c++
#include <iostream>
#include <stdexcept>

class MyArray {
private:
    int* data;
    size_t size;

public:
    // Constructor
    MyArray(size_t size) : size(size) {
        data = new int[size];
    }

    // Destructor
    ~MyArray() {
        delete[] data;
    }

    // Subscript operator
    int& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Const version of subscript operator
    const int& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Getter for size
    size_t getSize() const {
        return size;
    }
};

int main() {
    MyArray arr(5);

    // Assign values using subscript operator
    for (size_t i = 0; i < arr.getSize(); ++i) {
        arr[i] = i * 10;
    }

    // Access and print values using subscript operator
    for (size_t i = 0; i < arr.getSize(); ++i) {
        std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
    }

    return 0;
}
```

## Generic Programming
Generic programming is a programming paradigm aimed at writing reusable, flexible, and efficient code by abstracting from specific types and focusing on general algorithms and data structures. It allows you to write functions and classes that work with any data type, providing flexibility and code reuse.
Here are the key concepts and techniques used in generic programming:
- Templates
- Template specialization
- Type Traits
- STL and Generic Algorithms
By mastering generic programming techniques, you can write flexible and efficient code that adapts to various data types and requirements, promoting code reuse and maintainability.

### Function Templates
```c++
#include <iostream>

// Function template to find the maximum of two values
template<typename T>
T max(T a, T b) {
    return (a > b) ? a : b;
}

int main() {
    int intMax = max<int>(10, 20); // Explicitly specifying the template argument type

    // The compiler can deduce the template argument type from the function arguments
    double doubleMax = max(3.14, 2.71); // Compiler deduces the template argument type - Implicit instantiation

    return 0;
}
```

```c++
#include <iostream>

// Function template to print elements of an array
// When you pass an array to this function template, the compiler deduces the size of the array based on its type.
template<typename T, size_t N>
void printArray(T (&arr)[N]) {
    for (size_t i = 0; i < N; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

/* Above is equivalent too the following but in the one below size have to be passed
template<typename T>
void printArray(const T* arr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}
*/
int main() {
    int intArr[] = {1, 2, 3, 4, 5};
    double doubleArr[] = {3.14, 2.71, 1.618};

    std::cout << "Integer Array: ";
    printArray(intArr); // Print integer array

    std::cout << "Double Array: ";
    printArray(doubleArr); // Print double array

    return 0;
}
```

### Class Templates
Basic Syntax:
```c++
template<typename T>
class ClassName {
public:
    // Member variables, functions, and constructors
};
```

```c++
template<typename T>
class Stack {
private:
    T* elements;
    size_t capacity;
    size_t size;

public:
    // Constructor
    Stack(size_t capacity) : capacity(capacity), size(0) {
        elements = new T[capacity];
    }

    // Destructor
    ~Stack() {
        delete[] elements;
    }

    // Push an element onto the stack
    void push(const T& value) {
        if (size < capacity) {
            elements[size++] = value;
        } else {
            // Handle stack overflow
        }
    }

    // Pop an element from the stack
    T pop() {
        if (size > 0) {
            return elements[--size];
        } else {
            // Handle stack underflow
            // Returning a default value for now
            return T();
        }
    }

    // Get the size of the stack
    size_t getSize() const {
        return size;
    }
};

int main() {
    // Create a stack of integers
    Stack<int> intStack(5);
    intStack.push(10);
    intStack.push(20);
    std::cout << "Size of intStack: " << intStack.getSize() << std::endl;

    // Create a stack of doubles
    Stack<double> doubleStack(3);
    doubleStack.push(3.14);
    doubleStack.push(2.71);
    std::cout << "Size of doubleStack: " << doubleStack.getSize() << std::endl;

    return 0;
}
```

```c++
template<typename Key, typename Value>
class KeyValue {
private:
    Key key;
    Value value;

public:
    // Constructor
    KeyValue(const Key& k, const Value& v) : key(k), value(v) {}

    // Getter for key
    Key getKey() const {
        return key;
    }

    // Getter for value
    Value getValue() const {
        return value;
    }

    // Setter for value
    void setValue(const Value& v) {
        value = v;
    }
};

int main() {
    // Create a KeyValue instance with string key and int value
    KeyValue<std::string, int> pair1("age", 30);
    std::cout << "Key: " << pair1.getKey() << ", Value: " << pair1.getValue() << std::endl;

    // Create a KeyValue instance with char key and double value
    KeyValue<char, double> pair2('x', 3.14);
    std::cout << "Key: " << pair2.getKey() << ", Value: " << pair2.getValue() << std::endl;

    return 0;
}
```

### Templates Specialization
allows you to provide specialized implementations of function templates or class templates for specific types or values. 
```c++
#include <iostream>

// Generic template function
template<typename T>
void print(T value) {
    std::cout << "Generic template: " << value << std::endl;
}

// Explicit specialization for int type
template<>
void print<int>(int value) {
    std::cout << "Specialized for int: " << value << std::endl;
}

int main() {
    print("Hello"); // Calls generic template
    print(10);      // Calls specialized version for int
    return 0;
}
```

### type traits
Type traits in C++ provide a way to query and manipulate properties of types at compile time. They are commonly used in template metaprogramming to enable conditional behavior based on type properties. C++ provides the <type_traits> header, which contains a collection of type traits.

Here are some common type traits and their usage:
```c++
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    
    // 1. std::is_integral<T>
    // Determines if the type T is an integral type (bool, char, int, etc.).
    std::cout << "int is integral: " << std::is_integral<int>::value << std::endl;
    std::cout << "double is integral: " << std::is_integral<double>::value << std::endl;
    
    //2. std::is_pointer<T>
    // Determines if the type T is a pointer type.
    std::cout << "int* is a pointer: " << std::is_pointer<int*>::value << std::endl;
    std::cout << "double* is a pointer: " << std::is_pointer<double*>::value << std::endl;
 
    // 3. std::is_same<T, U>
    // Determines if the types T and U are the same.
    std::cout << "int and double are the same: " << std::is_same<int, double>::value << std::endl;
    std::cout << "int and int are the same: " << std::is_same<int, int>::value << std::endl;

    // 4. std::remove_const<T>
    // Removes the const qualifier from the type T.
    std::cout << "Before removal: const int" << std::endl;
    std::cout << "After removal: " << typeid(std::remove_const<const int>::type).name() << std::endl;

    // 5. std::conditional<condition, T, U>
    // Selects between types T and U based on the boolean condition.
    std::cout << "Result type is: " << typeid(std::conditional<true, int, double>::type).name() << std::endl;
    std::cout << "Result type is: " << typeid(std::conditional<false, int, double>::type).name() << std::endl;
    
    return 0;
}

Output:
int is integral: true
double is integral: false
int* is a pointer: true
double* is a pointer: true
int and double are the same: false
int and int are the same: true
Before removal: const int
After removal: i
Result type is: i
Result type is: d
```

#### Return Type deductions - c++ 14 onwards using auto
```c++
#include <iostream>

// Function template with return type deduction
template<typename T, typename U>
auto add(T a, U b) {
    return a + b; // Compiler deduces return type based on the expression
}

int main() {
    auto result1 = add(10, 20); // Compiler deduces return type to be int
    auto result2 = add(3.14, 2.71); // Compiler deduces return type to be double

    std::cout << "Result 1: " << result1 << std::endl;
    std::cout << "Result 2: " << result2 << std::endl;

    return 0;
}
```

#### Namespace Alias
Namespace aliases provide a way to create shorter or more descriptive names for namespaces
```c++
namespace alias_name = namespace_name;
```

```c++
// Outer namespace
namespace Outer {
    // Inner namespace
    namespace Inner {
        void foo() {
            std::cout << "Inside Outer::Inner::foo()" << std::endl;
        }
    }
}

// Create an alias for the nested namespace
namespace NI = Outer::Inner;

int main() {
    NI::foo();
    return 0;
}
```

#### ADL => Argument-Dependent Name Lookup
ADL is a mechanism in C++ that allows functions to be found via argument types
```c++
#include <iostream>

namespace MyNamespace {
    struct MyType {};

    void myFunction(MyType) {
        std::cout << "Inside MyNamespace::myFunction" << std::endl;
    }
}

int main() {
    MyNamespace::MyType obj;
    myFunction(obj); // ADL finds MyNamespace::myFunction
    return 0;
}
```

#### decltype - allows you to obtain the type of an expression or a variable without actually evaluating it.
```c++
#include <iostream>

int main() {
    int x = 5;
    decltype(x) y = 10; // y has the same type as x, which is int

    std::cout << "y: " << y << std::endl;

    return 0;
}
```

#### using
using simplifies the syntax for defining function pointers, and function objects. Can NOT be used with lambdas.
```c++
#include <iostream>
#include <functional> // Include this header for std::function

// Define a type alias for a function pointer
using FuncPtr = void(*)(int);

int main() {
    // Use the type alias for function pointers
    FuncPtr ptr = [](int x) { std::cout << "Function pointer: " << x << std::endl; };
    ptr(10);

    // Define a lambda function directly using auto or std::function
    auto lambda = [](int x) { return x * x; };
    std::cout << "Lambda: " << lambda(5) << std::endl;

    return 0;
}
```

#### chrono - for handling time-related operations.
```c++
#include <iostream>
#include <chrono>

// Function to simulate some time-consuming operation
void timeConsumingOperation() {
    for (int i = 0; i < 1000000; ++i) {
        // Simulate computation
        volatile int x = i * i;
    }
}

int main() {
    // Start measuring time
    auto start = std::chrono::high_resolution_clock::now();

    // Perform time-consuming operation
    timeConsumingOperation();

    // Stop measuring time
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate duration
    std::chrono::duration<double> duration = end - start;

    // Output the duration in seconds
    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl; //0.00485 seconds

    return 0;
}
```

#### Functors aka Function Objects
A functor in C++ is an object that acts like a function. It's a type that can be called as if it were a function, typically by using the function call operator operator(). Functors provide a way to encapsulate behavior and pass it around as a first-class citizen, similar to function pointers or lambda expressions.
```c++
#include <iostream>

// Functor class
class MyFunctor {
public:
    void operator()(int x) const {
        std::cout << "Value passed to functor: " << x << std::endl;
    }
};

int main() {
    MyFunctor functor; // Create an instance of the functor

    // Call the functor as if it were a function
    functor(42);

    return 0;
}
```

#### <tuple>
<tuple> is a standard header file in C++ that provides the std::tuple class template, introduced in C++11. It's part of the Standard Template Library (STL) and is used for creating heterogeneous collections of elements. A tuple is similar to an array or struct but can hold elements of different types, making it a versatile container for storing related but different types of data.

It's often used as a return type for functions that need to return multiple values, or in algorithms that need to operate on collections of heterogeneous data.

```c++
#include <iostream>
#include <tuple>

int main() {
    // Creating a tuple with three elements of different types
    std::tuple<int, double, std::string> myTuple(42, 3.14, "Hello");

    // Creating a tuple using std::make_tuple
    auto myTuple2 = std::make_tuple(42, 3.14, "Hello");

    // Accessing elements by index
    std::cout << "First element: " << std::get<0>(myTuple) << std::endl;
    std::cout << "Second element: " << std::get<1>(myTuple) << std::endl;
    std::cout << "Third element: " << std::get<2>(myTuple) << std::endl;

    // Accessing elements by type
    std::cout << "Element with type int: " << std::get<int>(myTuple) << std::endl;
    std::cout << "Element with type double: " << std::get<double>(myTuple) << std::endl;
    std::cout << "Element with type string: " << std::get<std::string>(myTuple) << std::endl;

    return 0;
}

output:
First element: 42
Second element: 3.14
Third element: Hello
Element with type int: 42
Element with type double: 3.14
Element with type string: Hello
```

tie example
```c++
#include <iostream>
#include <tuple>

// Function that returns a tuple
std::tuple<int, double, std::string> getValues() {
    return std::make_tuple(42, 3.14, "Hello");
}

int main() {
    // Call the function and unpack the returned tuple into variables
    int intValue;
    double doubleValue;
    std::string stringValue;
    
    std::tie(intValue, doubleValue, stringValue) = getValues();

    // Output the unpacked values
    std::cout << "Int value: " << intValue << std::endl;
    std::cout << "Double value: " << doubleValue << std::endl;
    std::cout << "String value: " << stringValue << std::endl;

    return 0;
}
```

#### constexpr
constexpr is a keyword introduced in C++11 (and further expanded in later standards) that indicates that a function or object's value can be computed at compile time. It stands for "constant expression". constexpr can be applied to variables, functions, and constructors, enabling compile-time evaluation and optimization. Can be applied to constructors as well to create objects at compile time.
```c++
constexpr int SIZE = 10; // Compile-time constant

constexpr int square(int x) {
    return x * x;
}

constexpr int result = square(5); // Compile-time evaluation

class MyClass {
public:
    constexpr MyClass(int x) : value(x) {}

    int getValue() const { return value; }

private:
    int value;
};

constexpr MyClass obj(42); // Compile-time object construction

```

#### friend
In C++, the friend keyword is used to grant access to private or protected members of a class to functions or other classes that are not members of that class. It allows designated external functions or classes to access the private and protected members of a class as if they were their own members.
```c++
class MyClass {
private:
    int privateMember;

public:
    // Declare an external function as a friend
    friend void externalFunction(MyClass& obj);

    // Declare an entire class as a friend
    friend class FriendClass;
};

// Define the friend function
void externalFunction(MyClass& obj) {
    std::cout << "Value of private member accessed by friend function: " << obj.privateMember << std::endl;
}
```


## Operator Overloading
```c++
#include <iostream>

class Complex {
private:
    double real;
    double imaginary;

public:
    Complex(double real = 0.0, double imaginary = 0.0) : real(real), imaginary(imaginary) {}

    // Overload the + operator for adding two complex numbers
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imaginary + other.imaginary);
    }

    // Overload the << operator for outputting Complex objects
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.real << " + " << c.imaginary << "i";
        return os;
    }
};

int main() {
    Complex c1(2.0, 3.0);
    Complex c2(1.0, 4.0);

    Complex result = c1 + c2; // Using overloaded + operator
    std::cout << "Result: " << result << std::endl; // Using overloaded << operator

    return 0;
}
```
internally resolved as ***c1.operator+(c2);***

Overloading ->
```c++
#include <iostream>

class MyClass {
private:
    int value;

public:
    MyClass(int val) : value(val) {}

    int getValue() const {
        return value;
    }

    // Overload the -> operator
    MyClass* operator->() {
        return this;
    }
};

int main() {
    MyClass obj(42);
    
    // Accessing member through the overloaded ->
    std::cout << "Value accessed through overloaded ->: " << obj->getValue() << std::endl;

    return 0;
}
```

In C++, there are certain operators that cannot be overloaded. These operators are:

- Scope Resolution Operator (::): Used to qualify names in namespaces, classes, and enumerations.
- Member Selection Operator (.): Used to access members of objects and structures directly.
- Member Pointer Operator (.*): Used to access members of objects through pointers to members.
- Conditional Operator (?:): Used for conditional expressions.
- Sizeof Operator (sizeof): Used to determine the size of objects and data types.
- Alignment Operator (alignof): Used to determine the alignment requirement of a type.
- Ellipsis Operator (...): Used to define variadic functions.

#### Variadic Functions (...)
```c++
#include <iostream>
#include <cstdarg> // Required for va_list, va_start, and va_end

// Variadic function that calculates the sum of its arguments
int sum(int count, ...) {
    int total = 0;
    va_list args; // Variable argument list
    va_start(args, count); // Initialize argument list

    // Iterate over the variable arguments
    for (int i = 0; i < count; ++i) {
        total += va_arg(args, int); // Access each argument
    }

    va_end(args); // Clean up argument list
    return total;
}

int main() {
    std::cout << "Sum of 3, 5, and 7: " << sum(3, 3, 5, 7) << std::endl;
    std::cout << "Sum of 1, 2, 3, 4, and 5: " << sum(5, 1, 2, 3, 4, 5) << std::endl;

    return 0;
}
```

### Casts
Static Cast (static_cast): Used for conversions that are well-defined and checked at compile-time.
Dynamic Cast (dynamic_cast): Used for converting pointers and references to polymorphic types. primarily used in inheritance hierarchies to perform downcasting.
Const Cast (const_cast): Used to add or remove const or volatile qualifiers from a variable.
Reinterpret Cast (reinterpret_cast): Used for low-level, type-unsafe conversions between unrelated types.
c-style: traditional

```c++
//static
double d = 3.14;
int i = static_cast<int>(d); // Convert double to int

//dynamic
class Base {
public:
    virtual ~Base() {}
};

class Derived : public Base {};

Base* basePtr = new Derived();
Derived* derivedPtr = dynamic_cast<Derived*>(basePtr); // Downcasting
if (derivedPtr) {
    // Conversion succeeded
} else {
    // Conversion failed
}

//const
const int x = 10;
int* ptr = const_cast<int*>(&x); // Remove const qualifier
*ptr = 20; // Modifying a const object

//add const-ness
int x = 42;
int* ptr = &x;

// Add const qualifier to the pointer
const int* constPtr = const_cast<const int*>(ptr);

// Now you cannot modify the value through constPtr
// *constPtr = 10; // Error: assignment of read-only location

// Add volatile qualifier to the pointer
volatile int* volatilePtr = const_cast<volatile int*>(ptr);

// Now you can treat volatilePtr as a pointer to a volatile variable
// *volatilePtr = 10; // OK

//reinterpret
int* ptr = reinterpret_cast<int*>(0x1000); // Convert integer to pointer
uintptr_t addr = reinterpret_cast<uintptr_t>(ptr); // Convert pointer to integer

//c-style
float f = 3.14;
int i = (int)f; // C-style cast
```

### 2D Arrays
```c++
#include <iostream>
using namespace std;

int main() {
    // Define the dimensions of the 2D array
    const int rows = 3;
    const int cols = 4;

    // Dynamically allocate memory for the 2D array
    int** array2D = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        array2D[i] = new int[cols];
    }

    // Fill the 2D array with values
    int counter = 1;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            array2D[i][j] = counter++;
        }
    }

    // Print the 2D array
    cout << "2D Array:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << array2D[i][j] << " ";
        }
        cout << endl;
    }

    // Deallocate memory for the 2D array
    for (int i = 0; i < rows; ++i) {
        delete[] array2D[i];
    }
    delete[] array2D;

    return 0;
}
```

# CPP - Containers and Algorithms

## STL consists of
- Containers - Hold objects
- Iterators - Manipulates STL elements
- Algorithms - Perform common manipulations

## Containers library
The Containers library is a generic collection of class templates and algorithms that allow programmers to easily implement common data structures like queues, lists and stacks. There are two(until C++11)three(since C++11) classes of containers:<br>
sequence containers, <br>
associative containers, and<br>
unordered associative containers,(since C++11)<br>

each of which is designed to support a different set of operations.

## Sequence containers (Linear Data Structures)
Sequence containers implement data structures which can be accessed sequentially.
- array (static contiguous memory), 
- vector (dynamic contiguous memory), 
- forward_list (singly linked list), 
- list (doubly linked list), 
- deque (double ended queue)

## Associative containers (Non Linear)
Associative containers implement sorted data structures that can be quickly searched (O(log n) complexity).
- set - collection of unique keys, sorted by keys
- multiset -same as set but multiple keys of same value are allowed
- map - collection of key-value pairs, sorted by keys, keys are unique
- multimap - same as map but multiple keys of same value are allowed

## Unordered associative containers (since C++11)
Unordered associative containers implement unsorted (hashed) data structures that can be quickly searched (O(1) average, O(n) worst-case complexity).
- unordered_set - collection of unique keys, hashed by keys
- unordered_multiset -same as set but multiple keys of same value are allowed
- unordered_map - collection of key-value pairs, hashed by keys, keys are unique
- unordered_multimap - same as map but multiple keys of same value are allowed

## Container adaptors
Container adaptors provide a different interface for sequential containers.
- stack: adapts a container to provide stack (LIFO data structure)
- queue: adapts a container to provide queue (FIFO data structure)
- priority_queue: adapts a container to provide priority queue

- flat_set: (C++23): adapts a container to provide a collection of unique keys, sorted by keys
- flat_map:(C++23):adapts two containers to provide a collection of key-value pairs, sorted by unique keys
- flat_multiset: (C++23): adapts a container to provide a collection of keys, sorted by keys
- flat_multimap: (C++23): adapts two containers to provide a collection of key-value pairs, sorted by keys

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

## User defined DataTypes and map/set/unordered_map/uo_set 

For user defined types we need to implement certain extra operators and a hash function as in example below:

In this example:

The MyClass class represents objects with an id and a name.<br>
The < operator is overloaded to define a strict weak ordering, required for elements in std::set and std::map.<br>
The == operator is overloaded to check equality, required for elements in std::unordered_set and std::unordered_map.<br>
A custom hash function Hash is provided for objects of MyClass, required for hashing elements in std::unordered_set and std::unordered_map.<br>
This class can be used as keys in std::set, std::unordered_set, std::map, and std::unordered_map.<br>

```c++
#include <iostream>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <string>

class MyClass {
private:
    int id;
    std::string name;

public:
    MyClass(int _id, const std::string& _name) : id(_id), name(_name) {}

    // Overloading < operator for std::set and std::map
    bool operator<(const MyClass& other) const {
        return id < other.id;
    }

    // Overloading == operator for std::unordered_set and std::unordered_map
    bool operator==(const MyClass& other) const {
        return id == other.id && name == other.name;
    }

    // Hash function for std::unordered_set and std::unordered_map
    struct Hash {
        std::size_t operator()(const MyClass& obj) const {
            return std::hash<int>()(obj.id) ^ (std::hash<std::string>()(obj.name) << 1);
        }
    };
};

int main() {
    std::set<MyClass> mySet;
    std::unordered_set<MyClass, MyClass::Hash> myUnorderedSet;
    std::map<MyClass, int> myMap;
    std::unordered_map<MyClass, int, MyClass::Hash> myUnorderedMap;

    MyClass obj1(1, "Object 1");
    MyClass obj2(2, "Object 2");
    MyClass obj3(1, "Object 1"); // Duplicate of obj1

    mySet.insert(obj1);
    mySet.insert(obj2);
    mySet.insert(obj3); // Duplicate, won't be inserted

    myUnorderedSet.insert(obj1);
    myUnorderedSet.insert(obj2);
    myUnorderedSet.insert(obj3); // Duplicate, won't be inserted

    myMap[obj1] = 10;
    myMap[obj2] = 20;
    myMap[obj3] = 30; // Duplicate, will overwrite

    myUnorderedMap[obj1] = 100;
    myUnorderedMap[obj2] = 200;
    myUnorderedMap[obj3] = 300; // Duplicate, will overwrite

    // Displaying elements of std::set
    std::cout << "Elements of set:" << std::endl;
    for (const auto& elem : mySet) {
        std::cout << elem.id << ": " << elem.name << std::endl;
    }

    // Displaying elements of std::unordered_set
    std::cout << "\nElements of unordered_set:" << std::endl;
    for (const auto& elem : myUnorderedSet) {
        std::cout << elem.id << ": " << elem.name << std::endl;
    }

    // Displaying elements of std::map
    std::cout << "\nElements of map:" << std::endl;
    for (const auto& pair : myMap) {
        std::cout << pair.first.id << ": " << pair.first.name << " -> " << pair.second << std::endl;
    }

    // Displaying elements of std::unordered_map
    std::cout << "\nElements of unordered_map:" << std::endl;
    for (const auto& pair : myUnorderedMap) {
        std::cout << pair.first.id << ": " << pair.first.name << " -> " << pair.second << std::endl;
    }

    return 0;
}

```


## Thread safety
1. All container functions can be called concurrently by different threads on different containers. More generally, the C++ standard library functions do not read objects accessible by other threads unless those objects are directly or indirectly accessible via the function arguments, including the this pointer.
2. All const member functions can be called concurrently by different threads on the same container. In addition, the member functions begin(), end(), rbegin(), rend(), front(), back(), data(), find(), lower_bound(), upper_bound(), equal_range(), at(), and, except in associative containers, operator[], behave as const for the purposes of thread safety (that is, they can also be called concurrently by different threads on the same container). More generally, the C++ standard library functions do not modify objects unless those objects are accessible, directly or indirectly, via the function's non-const arguments, including the this pointer.
3. Different elements in the same container can be modified concurrently by different threads, except for the elements of std::vector<bool> (for example, a vector of std::future objects can be receiving values from multiple threads).
4. Iterator operations (e.g. incrementing an iterator) read, but do not modify the underlying container, and may be executed concurrently with operations on other iterators on the same container, with the const member functions, or reads from the elements. Container operations that invalidate any iterators modify the container and cannot be executed concurrently with any operations on existing iterators even if those iterators are not invalidated.
5. Elements of the same container can be modified concurrently with those member functions that are not specified to access these elements. More generally, the C++ standard library functions do not read objects indirectly accessible through their arguments (including other elements of a container) except when required by its specification.
6. In any case, container operations (as well as algorithms, or any other C++ standard library functions) may be parallelized internally as long as this does not change the user-visible results (e.g. std::transform may be parallelized, but not std::for_each which is specified to visit each element of a sequence in order).

## Algorithms - operates on container elements only indirectly thru iterators
If you use raw loops and you understand the containers, you don’t have to deal with these. A surprising “advantage” of using raw loops - please, prefer algorithms!
Otherwise, most probably you understand what standard algorithms do. Think about them and you’ll be able to come up with their complexities in most cases. Let’s have a look at some algorithms:
- ***all_of/ any_of / none_of*** have at most O(n) complexity where n is the size of the range the algorithm is applied on
- ***count_if*** has a complexity of O(n) where n is the size of the range the algorithm is applied on
- ***find / find_if*** have a complexity of O(n). They need at most n applications of operator== or a predicate where n is the length of the range passed in
- ***replace / replace_if*** have a complexity of O(n). They need n applications of operator== or of a predicate where n is the length of the range passed in and at most n assignments
- ***copy / copy_if*** have a complexity of O(n). copy does n assignments where n is the length of the passed-in range, for copy_if we also have to think about the application of the predicate, while the number of assignments might be smaller.
- ***transform*** also has a complexity of O(n). It performs exactly n applications of the operation, where n is the length of the passed-in range.
- ***generate*** has a complexity of O(n) as it invokes n times the generator function and also performs the same amount of assignments.
- ***remove_if*** has a complexity of O(n) as it performs n applications of operator== or of a predicate where n is the length of the range passed in.
- ***swap*** has a complexity of O(1) if applied on single values and O(n) if applied on arrays where n is the size of the arrays to be swapped
- ***reverse*** performs exactly half as many swaps as the size of the range to be reversed, therefore the complexity is O(n)
- ***rotate*** also has a complexity of O(n).

Quite boring, right? But boredom brings simplicity to your calculations. Algos are of 2 types - Mutating (swap, fill..) and Non-mutating (find, count...).

### adjacent_find
Searches for two adjacent elements that are either equal or satisfy a specified condition.

```c++
// alg_adj_fnd.cpp
// compile with: /EHsc
#include <list>
#include <algorithm>
#include <iostream>

// Returns whether second element is twice the first
bool twice (int elem1, int elem2 )
{
    return elem1 * 2 == elem2;
}

int main()
{
    using namespace std;
    list<int> L;
    list<int>::iterator Iter;
    list<int>::iterator result1, result2;

    L.push_back( 50 );
    L.push_back( 40 );
    L.push_back( 10 );
    L.push_back( 20 );
    L.push_back( 20 );

    result2 = adjacent_find( L.begin( ), L.end( ), twice );
    if ( result2 == L.end( ) )
        cout << "There are not two adjacent elements where the "
            << "second is twice the first." << endl;
    else
    {
        cout << "There are two adjacent elements where "
            << "the second is twice the first.\n"
            << "They have values of " << *(result2++)
            << " & " << *result2 << "." << endl;
    }
}
```

### all_of
Returns true when a condition is present at each element in the given range.
```c++
int main()
{
    using namespace std;

    list<int> li { 50, 40, 10, 20, 20 };
    list<int>::iterator iter;

    cout << "li = ( ";
    for (iter = li.begin(); iter != li.end(); iter++)
        cout << *iter << " ";
    cout << ")" << endl;

    // Check if all elements in li are even.
    auto is_even = [](int elem){ return !(elem % 2); };
    if (all_of(li.begin(), li.end(), is_even))
        cout << "All the elements are even numbers.\n";
    else
        cout << "Not all the elements are even numbers.\n";
}
```

### any_of
Returns true when a condition is present at least once in the specified range of elements.
```c++
   // Check if there's an even element in li.
    auto is_even = [](int const elem){ return !(elem % 2); };
    if (any_of(li.begin(), li.end(), is_even))
        cout << "There's an even element in li.\n";
```

### binary_search
Tests whether there's an element in a sorted range that is equal to a specified value or that is equivalent to it in a sense specified by a binary predicate.
```c++
   list<int> List1;

    List1.push_back( 50 );
    List1.push_back( 10 );
    List1.push_back( 30 );
    List1.push_back( 20 );
    List1.push_back( 25 );
    List1.push_back( 5 );

    List1.sort();

   // default binary search for 10
    if ( binary_search(List1.begin(), List1.end(), 10) )
        cout << "There is an element in list with a value equal to 10."
```
      
### copy
Assigns the values of elements from a source range to a destination range, iterating through the source sequence of elements and assigning them new positions in a forward direction.
```c++
    vector<int> v1, v2; //v2 has 11 elements

    // To copy the first 3 elements of v1 into the middle of v2
    copy( v1.begin( ), v1.begin( ) + 3, v2.begin( ) + 4 );
```

 ### copy_backward
Assigns the values of elements from a source range to a destination range, iterating through the source sequence of elements and assigning them new positions in a backward direction.
```c++
   // To copy_backward the first 3 elements of v1 into the middle of v2
    copy_backward( v1.begin( ), v1.begin( ) + 3, v2.begin( ) + 7 );
```

### copy_if
In a range of elements, copies the elements that are true for the specified condition.
```c++
   list<int> li{ 46, 59, 88, 72, 79, 71, 60, 5, 40, 84 };
   list<int> lo(li.size()); // lo = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

   // is_odd checks if the element is odd.
    auto is_odd = [](int const elem) { return (elem % 2); };
    // use copy_if to select only odd elements from li
    // and copy them to lo, starting from lo's begin position
    auto oc = copy_if(li.begin(), li.end(), lo.begin(), is_odd);
    lo.resize(std::distance(lo.begin(), oc));  // shrink lo to new size
```

### copy_n
Copies a specified number of elements.
```c++
int main()
{
    using namespace std;
    string s1{"dandelion"};
    string s2{"badger"};

    cout << s1 << " + " << s2 << " = ";

    // Copy the first 3 letters from s1
    // to the first 3 positions in s2
    copy_n(s1.begin(), 3, s2.begin());

    cout << s2 << endl;
}
```

### count
Returns the number of elements in a range whose values match a specified value.
```c++
    vector<int>::iterator::difference_type result;
    result = count(v1.begin(), v1.end(), 10);
    cout << "The number of 10s in v2 is: " << result << "." << endl;
```

### count_if
Returns the number of elements in a range whose values satisfy a specified condition.
```c++
    vector<int>::iterator::difference_type result1;
    result1 = count_if(v1.begin(), v1.end(), [](auto x) {return x > 10;});
    cout << "The number of elements in v1 greater than 10 is: "
         << result1 << "." << endl;
```

### equal
Compares two ranges element by element for equality or equivalence in a sense specified by a binary predicate.
```c++
bool   b = equal(v1.begin(), v1.end(), v3.begin(), v3.end());
```

### fill
Assigns the same new value to every element in a specified range.
```c++
   // Fill the last 5 positions with a value of 2
    fill( v1.begin( ) + 5, v1.end( ), 2 );
```

### fill_n
Assigns a new value to a specified number of elements in a range beginning with a particular element.
```c++
   // Fill the first 3 positions with a value of 1, saving position.
    auto pos = fill_n( v.begin(), 3, 1 );
```

### find
Locates the position of the first occurrence of an element in a range that has a specified value.

### find_first_of
Searches for the first occurrence of any of several values within a target range.
```c++
   // Searching v1 for a match to L1 under the binary predicate twice
    vector<int>::iterator result2;
    vector<int> v1, v2;
    result2 = find_first_of ( v1.begin( ), v1.end( ), v2.begin( ), v2.end(), twice );
   
    // Return whether second element is twice the first
    bool twice ( int elem1, int elem2 )
    {
        return 2 * elem1 == elem2;
    }
```

### find_if
Locates the position of the first occurrence of an element in a range that satisfies a specified condition.
```c++
   // Function to use as the UnaryPredicate argument to find_if() in this example
   bool is_odd_int(int i) {
       return ((i % 2) != 0);
   }

   // call <algorithm> std::find_if()
    auto p = find_if(first, last, is_odd_int);
```

### for_each
Applies a specified function object to each element in a forward order within a range and returns the function object.
```c++
#include <vector>
#include <algorithm>
#include <iostream>

// The function object multiplies an element by a Factor
template <class Type>
class MultValue
{
private:
    Type Factor;   // The value to multiply by
public:
    // Constructor initializes the value to multiply by
    MultValue ( const Type& value ) : Factor ( value ) {
    }

    // The function call for the element to be multiplied
    void operator( ) ( Type& elem ) const
    {
        elem *= Factor;
    }
};

int main()
{
    using namespace std;
    vector<int> v1;
    vector<int>::iterator Iter1;

    // Constructing vector v1
    int i;
    for ( i = -4 ; i <= 2 ; i++ )
    {
        v1.push_back( i );
    }

    cout << "Original vector v1 = ( " ;
    for ( Iter1 = v1.begin( ) ; Iter1 != v1.end( ) ; Iter1++ )
        cout << *Iter1 << " ";
    cout << ")." << endl;

    // Using for_each to multiply each element by a Factor
    //for_each ( v1.begin( ), v1.end( ), MultValue<int> ( -2 ) );
    for_each ( v1.begin( ), v1.end( ), [](int& k) { k = k * -2;} );
    
    cout << "Multiplying the elements of the vector v1\n "
            << "by the factor -2 gives:\n v1mod1 = ( " ;
    for ( Iter1 = v1.begin( ) ; Iter1 != v1.end( ) ; Iter1++ )
        cout << *Iter1 << " ";
    cout << ")." << endl;
}

/*
Original vector v1 = ( -4 -3 -2 -1 0 1 2 ).
Multiplying the elements of the vector v1
 by the factor -2 gives:
 v1mod1 = ( 8 6 4 2 0 -2 -4 ).
*/
```

### generate
Assigns the values generated by a function object to each element in a range.
The function object is invoked for each element in the range and doesn't need to return the same value each time it's called. It is called with no arguments to generate the values to be assigned to each of the elements in the range.
```c++
#include <vector>
#include <algorithm>
#include <iostream>

int main()
{
    using namespace std;

    // Assigning random values to vector integer elements
    vector<int> v1 ( 5 );
    vector<int>::iterator Iter1;

    generate ( v1.begin( ), v1.end( ), rand );

    cout << "Vector v1 is ( " ;
    for ( Iter1 = v1.begin( ) ; Iter1 != v1.end( ) ; Iter1++ )
        cout << *Iter1 << " ";
    cout << ")." << endl;
}
```

### is_sorted
Returns true if the elements in the specified range are in sorted order.

### remove
Eliminates a specified value from a given range without disturbing the order of the remaining elements. Returns the end of a new range free of the specified value.
```c++
   // Remove elements with a value of 7
    auto new_end = remove ( v1.begin( ), v1.end( ), 7 );

    // To change the sequence size, use erase
    v1.erase (new_end, v1.end( ) );
```
Always use erase() after remove() to resize.

### replace/replace_if
Examines each element in a range and replaces it if it matches a specified value.
```c++
   replace_if(v.begin(), v.end(), [](int k){ return k > 6; }, 70);
```

### reverse
Reverses the order of the elements within a range.
```c++
   // Reverse the elements in the vector
    reverse (v1.begin( ), v1.end( ) );
```

### sort
Arranges the elements in a specified range into a nondescending order or according to an ordering criterion specified by a binary predicate.
```c++
    // To sort in descending order. specify binary predicate
    sort( v1.begin( ), v1.end( ), greater<int>( ) );

    // Return whether first element is greater than the second
    bool UDgreater ( int elem1, int elem2 )
    {
        return elem1 > elem2;
    }

    // A user-defined (UD) binary predicate can also be used
    //sorts in Desc order as above
    sort( v1.begin( ), v1.end( ), UDgreater );
```

### swap
This exchanges the values of two objects. = swap( v1, v2 );

### transform
Applies a specified function object to each element in a source range or to a pair of elements from two source ranges. Then, it copies the return values of the function object into a destination range.
```c++
   // Using transform to multiply each element by a factor of 5
   transform ( v1.begin( ), v1.end( ), v2.begin( ), MultValue<int> ( 5 ) );
```

### unique
Removes duplicate elements that are next to each other in a specified range.

## Conclusion
In this article, we talked about the complexity analysis of operations on containers and of algorithms which are so often make important part of a software developer job interview. We discussed some hints on how to approach such questions if you neglected complexity analysis during most of your preparation for interviews. Finally, we quickly went through the most important complexities of C++ containers and standard algorithms so that you can have the most basic characteristics that you’d need at a job interview. Good luck!


# Lambdas
https://learn.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp?view=msvc-170
```c++
//(1)   (2)  (3)      (4)      (5)
//===   ===  =======  ======   =======
  [=]   ()   mutable  throw()   -> int
  { //<== lambda body starts here (6)
    int n = x+y;
    x = y;
    y = n;
    return n;
  } //<== lambda body ends here
```
1. capture clause (Also known as the lambda-introducer in the C++ specification.) [&, =]
2. parameter list Optional. (Also known as the lambda declarator)
3. mutable specification Optional.
4. exception-specification Optional.
5. trailing-return-type Optional.
6. lambda body.

```c++
struct S { void f(int i); };

void S::f(int i) {
    [&, i]{};      // OK
    [&, &i]{};     // ERROR: i preceded by & when & is the default
    [=, this]{};   // ERROR: this when = is the default
    [=, *this]{ }; // OK: captures this by value. See below.
    [i, i]{};      // ERROR: i repeated
}
```

A capture followed by an ellipsis is a pack expansion, as shown in this variadic template example:
```c++
template<class... Args>
void f(Args... args) {
    auto x = [args...] { return g(args...); };
    x();
}
```

To use lambda expressions in the body of a class member function, pass the this pointer to the capture clause to provide access to the member functions and data members of the enclosing class.

When you use the capture clause, we recommend that you keep these points in mind, particularly when you use lambdas with multi-threading:
- Reference captures can be used to modify variables outside, but value captures can't. (mutable allows copies to be modified, but not originals.)
- Reference captures reflect updates to variables outside, but value captures don't.
- Reference captures introduce a lifetime dependency, but value captures have no lifetime dependencies. It's especially important when the lambda runs asynchronously. If you capture a local by reference in an async lambda, that local could easily be gone by the time the lambda runs. Your code could cause an access violation at run time.

##$ Generalized capture (C++14)
In C++14, you can introduce and initialize new variables in the capture clause, without the need to have those variables exist in the lambda function's enclosing scope. The initialization can be expressed as any arbitrary expression; the type of the new variable is deduced from the type produced by the expression. This feature lets you capture move-only variables (such as std::unique_ptr) from the surrounding scope and use them in a lambda.
```c++
pNums = make_unique<vector<int>>(nums);
//...
      auto a = [ptr = move(pNums)]()
        {
           // use ptr
        };
```

Examples:
```c++
// declaring_lambda_expressions1.cpp
// compile with: /EHsc /W4
#include <functional>
#include <iostream>

int main()
{
    using namespace std;

    // Assign the lambda expression that adds two numbers to an auto variable.
    auto f1 = [](int x, int y) { return x + y; };

    cout << f1(2, 3) << endl;

    // Assign the same lambda expression to a function object.
    function<int(int, int)> f2 = [](int x, int y) { return x + y; };

    cout << f2(3, 4) << endl;
}
```

The Microsoft C++ compiler binds a lambda expression to its captured variables when the expression is declared instead of when the expression is called. 
```c++
// declaring_lambda_expressions2.cpp
// compile with: /EHsc /W4
#include <functional>
#include <iostream>

int main()
{
   using namespace std;

   int i = 3;
   int j = 5;

   // The following lambda expression captures i by value and
   // j by reference.
   function<int (void)> f = [i, &j] { return i + j; };

   // Change the values of i and j.
   i = 22;
   j = 44;

   // Call f and print its result.
   cout << f() << endl;
}
```
Output is: 47 <<<< 3 + 44

This example declares a lambda expression that returns the sum of two integers and calls the expression immediately with the arguments 5 and 4:
```c++
// calling_lambda_expressions1.cpp
// compile with: /EHsc
#include <iostream>

int main()
{
   using namespace std;
   int n = [] (int x, int y) { return x + y; }(5, 4);
   cout << n << endl;
}
```

This example passes a lambda expression as an argument to the find_if function. The lambda expression returns true if its parameter is an even number.
```c++
// calling_lambda_expressions2.cpp
// compile with: /EHsc /W4
#include <list>
#include <algorithm>
#include <iostream>

int main()
{
    using namespace std;

    // Create a list of integers with a few initial elements.
    list<int> numbers;
    numbers.push_back(13);
    numbers.push_back(17);
    numbers.push_back(42);
    numbers.push_back(46);
    numbers.push_back(99);

    // Use the find_if function and a lambda expression to find the
    // first even number in the list.
    const list<int>::const_iterator result =
        find_if(numbers.begin(), numbers.end(),[](int n) { return (n % 2) == 0; });

    // Print the result.
    if (result != numbers.end()) {
        cout << "The first even number in the list is " << *result << "." << endl;
    } else {
        cout << "The list contains no even numbers." << endl;
    }
}
```
Output: The first even number in the list is 42.


#### Nested Lambda
You can nest a lambda expression inside another one, as shown in this example. The inner lambda expression multiplies its argument by 2 and returns the result. The outer lambda expression calls the inner lambda expression with its argument and adds 3 to the result.
```c++
// nesting_lambda_expressions.cpp
// compile with: /EHsc /W4
#include <iostream>

int main()
{
    using namespace std;

    // The following lambda expression contains a nested lambda
    // expression.
    int timestwoplusthree = [](int x) { return [](int y) { return y * 2; }(x) + 3; }(5);

    // Print the result.
    cout << timestwoplusthree << endl;
}
```

#### Higher order Lambda Functions
Many programming languages support the concept of a higher-order function. A higher-order function is a lambda expression that takes another lambda expression as its argument or returns a lambda expression. You can use the function class to enable a C++ lambda expression to behave like a higher-order function. The following example shows a lambda expression that returns a function object and a lambda expression that takes a function object as its argument.
```c++
// higher_order_lambda_expression.cpp
// compile with: /EHsc /W4
#include <iostream>
#include <functional>

int main()
{
    using namespace std;

    // The following code declares a lambda expression that returns
    // another lambda expression that adds two numbers.
    // The returned lambda expression captures parameter x by value.
    auto addtwointegers = [](int x) -> function<int(int)> {
        return [=](int y) { return x + y; };
    };

    // The following code declares a lambda expression that takes another
    // lambda expression as its argument.
    // The lambda expression applies the argument z to the function f
    // and multiplies by 2.
    auto higherorder = [](const function<int(int)>& f, int z) {
        return f(z) * 2;
    };

    // Call the lambda expression that is bound to higherorder.
    auto answer = higherorder(addtwointegers(7), 8);

    // Print the result, which is (7+8)*2.
    cout << answer << endl;
}
```

#### Lambda in a Function
You can use lambda expressions in the body of a function. The lambda expression can access any function or data member that the enclosing function can access. You can explicitly or implicitly capture the this pointer to provide access to functions and data members of the enclosing class.
```c++
// capture "this" by reference
void ApplyScale(const vector<int>& v) const
{
   for_each(v.begin(), v.end(),
      [this](int n) { cout << n * _scale << endl; });
}

// capture "this" by value (Visual Studio 2017 version 15.3 and later)
void ApplyScale2(const vector<int>& v) const
{
   for_each(v.begin(), v.end(),
      [*this](int n) { cout << n * _scale << endl; });
}

// capture "this" implicitly
void ApplyScale(const vector<int>& v) const
{
   for_each(v.begin(), v.end(),
      [=](int n) { cout << n * _scale << endl; });
}

// function_lambda_expression.cpp
// compile with: /EHsc /W4
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Scale
{
public:
    // The constructor.
    explicit Scale(int scale) : _scale(scale) {}

    // Prints the product of each element in a vector object
    // and the scale value to the console.
    void ApplyScale(const vector<int>& v) const
    {
        for_each(v.begin(), v.end(), [=](int n) { cout << n * _scale << endl; });
    }

private:
    int _scale;
};

int main()
{
    vector<int> values;
    values.push_back(1);
    values.push_back(2);
    values.push_back(3);
    values.push_back(4);

    // Create a Scale object that scales elements by 3 and apply
    // it to the vector object. Does not modify the vector.
    Scale s(3);
    s.ApplyScale(values);
}
```

#### Using Lambda with templates
Because lambda expressions are typed, you can use them with C++ templates. The following example shows the negate_all and print_all functions. The negate_all function applies the unary operator- to each element in the vector object. The print_all function prints each element in the vector object to the console.
```c++
// template_lambda_expression.cpp
// compile with: /EHsc
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// Negates each element in the vector object. Assumes signed data type.
template <typename T>
void negate_all(vector<T>& v)
{
    for_each(v.begin(), v.end(), [](T& n) { n = -n; });
}

// Prints to the console each element in the vector object.
template <typename T>
void print_all(const vector<T>& v)
{
    for_each(v.begin(), v.end(), [](const T& n) { cout << n << endl; });
}

int main()
{
    // Create a vector of signed integers with a few elements.
    vector<int> v;
    v.push_back(34);
    v.push_back(-43);
    v.push_back(56);

    print_all(v);
    negate_all(v);
    cout << "After negate_all():" << endl;
    print_all(v);
}

Output:
34
-43
56
After negate_all():
-34
43
-56
```

#### Handling Exceptions
The body of a lambda expression follows the rules for both structured exception handling (SEH) and C++ exception handling. You can handle a raised exception in the body of a lambda expression or defer exception handling to the enclosing scope. The following example uses the for_each function and a lambda expression to fill a vector object with the values of another one. It uses a try/catch block to handle invalid access to the first vector.
```c++
// eh_lambda_expression.cpp
// compile with: /EHsc /W4
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int main()
{
    // Create a vector that contains 3 elements.
    vector<int> elements(3);

    // Create another vector that contains index values.
    vector<int> indices(3);
    indices[0] = 0;
    indices[1] = -1; // This is not a valid subscript. It will trigger an exception.
    indices[2] = 2;

    // Use the values from the vector of index values to
    // fill the elements vector. This example uses a
    // try/catch block to handle invalid access to the
    // elements vector.
    try
    {
        for_each(indices.begin(), indices.end(), [&](int index) {
            elements.at(index) = index;
        });
    }
    catch (const out_of_range& e)
    {
        cerr << "Caught '" << e.what() << "'." << endl;
    };
}
```

#### Managed C++/CLI
The capture clause of a lambda expression cannot contain a variable that has a managed type. However, you can pass an argument that has a managed type to the parameter list of a lambda expression. The following example contains a lambda expression that captures the local unmanaged variable ch by value and takes a System.String object as its parameter.
```c++
// managed_lambda_expression.cpp
// compile with: /clr
using namespace System;

int main()
{
    char ch = '!'; // a local unmanaged variable

    // The following lambda expression captures local variables
    // by value and takes a managed String object as its parameter.
    [=](String ^s) {
        Console::WriteLine(s + Convert::ToChar(ch));
    }("Hello");
}
```

#### Function Objects vs. Lambdas
When you write code, you probably use function pointers and function objects to solve problems and perform calculations, especially when you use C++ Standard Library algorithms. Function pointers and function objects each have advantages and disadvantages—for example, function pointers have minimal syntactic overhead but do not retain state within a scope, and function objects can maintain state but require the syntactic overhead of a class definition.

A lambda combines the benefits of function pointers and function objects and avoids their disadvantages. Like a function object, a lambda is flexible and can maintain state, but unlike a function object, its compact syntax doesn't require an explicit class definition. By using lambdas, you can write code that's less cumbersome and less prone to errors than the code for an equivalent function object.

The following examples compare the use of a lambda to the use of a function object. The first example uses a lambda to print to the console whether each element in a vector object is even or odd. The second example uses a function object to accomplish the same task.

***Example 1: Using a Lambda***<br>
This example passes a lambda to the for_each function. The lambda prints a result that states whether each element in a vector object is even or odd.

```c++
// even_lambda.cpp
// compile with: cl /EHsc /nologo /W4 /MTd
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
   // Create a vector object that contains 9 elements.
   vector<int> v;
   for (int i = 1; i < 10; ++i) {
      v.push_back(i);
   }

   // Count the number of even numbers in the vector by
   // using the for_each function and a lambda.
   int evenCount = 0;
   for_each(v.begin(), v.end(), [&evenCount] (int n) {
      cout << n;
      if (n % 2 == 0) {
         cout << " is even " << endl;
         ++evenCount;
      } else {
         cout << " is odd " << endl;
      }
   });

   // Print the count of even numbers to the console.
   cout << "There are " << evenCount
        << " even numbers in the vector." << endl;
}

Output:
1 is odd
2 is even
3 is odd
4 is even
5 is odd
6 is even
7 is odd
8 is even
9 is odd
There are 4 even numbers in the vector.
```

***Comments***<br>
In the example, the third argument to the for_each function is a lambda. The [&evenCount] part specifies the capture clause of the expression, (int n) specifies the parameter list, and remaining part specifies the body of the expression.

***Example 2: Using a Function Object***<br>
Sometimes a lambda would be too unwieldy to extend much further than the previous example. The next example uses a function object instead of a lambda, together with the for_each function, to produce the same results as Example 1. Both examples store the count of even numbers in a vector object. To maintain the state of the operation, the FunctorClass class stores the m_evenCount variable by reference as a member variable. To perform the operation, FunctorClass implements the function-call operator, operator(). The Microsoft C++ compiler generates code that is comparable in size and performance to the lambda code in Example 1. For a basic problem like the one in this article, the simpler lambda design is probably better than the function-object design. However, if you think that the functionality might require significant expansion in the future, then use a function object design so that code maintenance will be easier.

For more information about the operator(), see Function Call. For more information about the for_each function, see for_each.
```c++
// even_functor.cpp
// compile with: /EHsc
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class FunctorClass
{
public:
    // The required constructor for this example.
    explicit FunctorClass(int& evenCount)
        : m_evenCount(evenCount) { }

    // The function-call operator prints whether the number is
    // even or odd. If the number is even, this method updates
    // the counter.
    void operator()(int n) const {
        cout << n;

        if (n % 2 == 0) {
            cout << " is even " << endl;
            ++m_evenCount;
        } else {
            cout << " is odd " << endl;
        }
    }

private:
    // Default assignment operator to silence warning C4512.
    FunctorClass& operator=(const FunctorClass&);

    int& m_evenCount; // the number of even variables in the vector.
};

int main()
{
    // Create a vector object that contains 9 elements.
    vector<int> v;
    for (int i = 1; i < 10; ++i) {
        v.push_back(i);
    }

    // Count the number of even numbers in the vector by
    // using the for_each function and a function object.
    int evenCount = 0;
    for_each(v.begin(), v.end(), FunctorClass(evenCount));

    // Print the count of even numbers to the console.
    cout << "There are " << evenCount
        << " even numbers in the vector." << endl;
}

Output:
1 is odd
2 is even
3 is odd
4 is even
5 is odd
6 is even
7 is odd
8 is even
9 is odd
There are 4 even numbers in the vector.
```

## Links
https://github.com/Loki-Astari?tab=repositories

