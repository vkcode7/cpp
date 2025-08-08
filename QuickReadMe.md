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

```bash
These three remain the foundational smart pointers in modern C++.
However, there were some related additions and improvements:
C++14:
======
std::make_unique was added (surprisingly, this was missing from C++11)
Improved std::make_shared with better exception safety

// C++11 - had to use new directly
std::unique_ptr<int> ptr1(new int(42));

// C++14 - added make_unique for consistency and exception safety
auto ptr2 = std::make_unique<int>(42);

C++17:
======
std::shared_ptr gained support for arrays (e.g., shared_ptr<int[]>)
std::weak_ptr also gained array support

// C++17 - shared_ptr can now manage arrays
std::shared_ptr<int[]> arr_ptr = std::shared_ptr<int[]>(new int[10]);

// weak_ptr with arrays too
std::weak_ptr<int[]> weak_arr = arr_ptr;

C++20:
=====
std::make_shared and std::make_unique gained support for arrays
std::atomic<std::shared_ptr> and std::atomic<std::weak_ptr> were added for better concurrent programming

The original trio of smart pointers covers the fundamental ownership patterns so well that no replacements have been needed:

unique_ptr for exclusive ownership
shared_ptr for shared ownership with reference counting
weak_ptr for non-owning references that can detect when the object is destroyed

// C++20 - make_unique for arrays
auto unique_arr = std::make_unique<int[]>(10);  // Creates array of 10 ints
auto unique_arr2 = std::make_unique<int[]>(5, 42);  // 5 ints, all initialized to 42

// C++20 - make_shared for arrays  
auto shared_arr = std::make_shared<int[]>(10);  // Creates array of 10 ints

// C++20 - atomic operations on shared_ptr
std::atomic<std::shared_ptr<int>> atomic_ptr;
```

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

### using
using simplifies the syntax for defining function pointers, and function objects. Can NOT be used with lambdas.

```c++
#include <iostream>
#include <functional> // Include this header for std::function

// Define a type alias for a function pointer
using FuncPtr = void(*)(int);
//typedef void(*FunctPtr)(int);

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

### Functors aka Function Objects
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

### tuple
"tuple" is a standard header file in C++ that provides the std::tuple class template, introduced in C++11. It's part of the Standard Template Library (STL) and is used for creating heterogeneous collections of elements. A tuple is similar to an array or struct but can hold elements of different types, making it a versatile container for storing related but different types of data.

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

### tie example
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

### constexpr
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

### friend
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

### Operator Overloading

```c++
    // Overload the + operator for adding two complex numbers
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imaginary + other.imaginary);
    }
```
usage:
```c++
    Complex c1(2.0, 3.0);
    Complex c2(1.0, 4.0);

    Complex result = c1 + c2; // Using overloaded + operator
```

**internally resolved as c1.operator+(c2);**

```c++
    // Overload the -> operator
    MyClass* operator->() {
        return this;
    }

    int getValue() const {
        return value;
    }

    //usage
    MyClass obj(42);
    auto v = obj->getValue();
```

### Casts
- Static Cast (static_cast): Used for conversions that are well-defined and checked at compile-time.
- Dynamic Cast (dynamic_cast): Used for converting pointers and references to polymorphic types. primarily used in inheritance hierarchies to perform downcasting.
- Const Cast (const_cast): Used to add or remove const or volatile qualifiers from a variable.
- Reinterpret Cast (reinterpret_cast): Used for low-level, type-unsafe conversions between unrelated types.
- C-style: traditional

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
