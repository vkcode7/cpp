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

## Generic Programming
- code resuse
- flexible code
- efficiency

### Key concepts used:
- Templates
- Template specialization
- Type Traits
- STL and Generic Algorithms

```c++
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


### Templates Specialization
Allows you to provide specialized implementations of function templates or class templates for specific types or values. 
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

