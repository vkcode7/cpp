# Quick Notes

### Rule of 5
- copy ctor, copy assignment
- move ctor, move assignment
- dtor

```c++
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
```

### unique_ptr
```c++
// Create a unique pointer to an integer with value 42
auto ptr = std::make_unique<int>(42);

// Use the unique pointer
std::cout << *ptr << std::endl; // Output: 42

// Create a unique pointer to a MyClass object
auto ptr = std::make_unique<MyClass>(10, 15, 20); //constructor takes 3 int values

// Create a shared pointer to an integer with value 42
auto ptr = std::make_shared<int>(42);
```

### Function template to find the maximum of two values
```c++
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

### Function template to print elements of an array
```c++
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

### class templates
```c++
template<typename T>
class ClassName {
public:
    // Member variables, functions, and constructors
};

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

### Namespace alias
```c++
namespace alias_name = namespace_name;
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

### decltype - allows you to obtain the type of an expression or a variable without actually evaluating it.
```c++
int main() {
    int x = 5;
    decltype(x) y = 10; // y has the same type as x, which is int

    std::cout << "y: " << y << std::endl;

    return 0;
}
```

### using
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

### Functors aka Function Objects
A functor in C++ is an object that acts like a function. It's a type that can be called as if it were a function, typically by using the function call operator operator(). Functors provide a way to encapsulate behavior and pass it around as a first-class citizen, similar to function pointers or lambda expressions.

```c++
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

### Tuple ands tie
It's often used as a return type for functions that need to return multiple values, or in algorithms that need to operate on collections of heterogeneous data.
```c++
// Creating a tuple with three elements of different types
std::tuple<int, double, std::string> myTuple(42, 3.14, "Hello");

// Creating a tuple using std::make_tuple
auto myTuple2 = std::make_tuple(42, 3.14, "Hello");
auto [a,b,c] = myTuple2;

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
}
```

### constexpr
constexpr is a keyword introduced in C++11 (and further expanded in later standards) that indicates that a function or object's value can be computed at compile time.
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
internally resolved as c1.operator+(c2);

### Overload the -> operator
MyClass* operator->() {
    return this;
}

### Subscript operator
```c++
int& operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}
```

### Casts
- Static Cast (static_cast): Used for conversions that are well-defined and checked at compile-time.
- Dynamic Cast (dynamic_cast): Used for converting pointers and references to polymorphic types, primarily used in inheritance hierarchies to perform downcasting.
- Const Cast (const_cast): Used to add or remove const or volatile qualifiers from a variable.
- Reinterpret Cast (reinterpret_cast): Used for low-level, type-unsafe conversions between unrelated types.
- c-style: traditional

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

### CPP - Containers and Algorithms
STL consists of:
- Containers - Hold objects<br>
- Iterators - Manipulates STL elements<br>
- Algorithms - Perform common manipulations<br>

Containers library:<br>
The Containers library is a generic collection of class templates and algorithms that allow programmers to easily implement common data structures like queues, lists and stacks. There are two(until C++11), three(since C++11) classes of containers:<br>
- sequence containers - array, vector, list, forward_list, deque
- associative containers - set, map, multiset, multimap
- unordered associative containers - unordered_set, unordered_map, unordered_multiset, unordered_multimap,(since C++11)

each of which is designed to support a different set of operations.

Container adaptors - Container adaptors provide a different interface for sequential containers.<br>
- stack (LIFO), queue (FIFO), priority_queue

### Lambdas
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


# FAQs

## Big Picture

### What is so great about classes
Classes are there to help you organize your code and to reason about your programs. You could roughly equivalently say that classes are there to help you avoid making mistakes and to help you find bugs after you do make a mistake. In this way, classes significantly help maintenance.

A class is the representation of an idea, a concept, in the code. An object of a class represents a particular example of the idea in the code. Without classes, a reader of the code would have to guess about the relationships among data items and functions – classes make such relationships explicit and “understood” by compilers. With classes, more of the high-level structure of your program is reflected in the code, not just in the comments.

A well-designed class presents a clean and simple interface to its users, hiding its representation and saving its users from having to know about that representation.

### What’s the big deal with OO?
Object-oriented techniques using classes and virtual functions are an important way to develop large, complex software applications and systems. So are generic programming techniques using templates. Both are important ways to express polymorphism – at run time and at compile time, respectively. OO is a style relying on encapsulation, inheritance, and polymorphism, it means programming using class hierarchies and virtual functions to allow manipulation of objects of a variety of types through well-defined interfaces and to allow a program to be extended incrementally through derivation.

### What’s the big deal with generic programming?
Generic programming techniques using templates are an important way to develop large, complex software applications and systems. So are object oriented techniques. Both are important ways to express polymorphism – at compile time and at run time, respectively. And they work great together in C++.

C++ supports generic programming. Generic programming is a way of developing software that maximizes code reuse in a way that does not sacrifice performance.

Generic programming is programming based on parameterization: You can parameterize a type with another (such as a vector with its element types) and an algorithm with another (such as a sort function with a comparison function). 

A common term used to describe generic programming is “parametric polymorphism”, with “ad hoc polymorphism” being the corresponding term for object-oriented programming. In the context of C++, generic programming resolves all names at compile time; it does not involve dynamic (run-time) dispatch. This has led generic programming to become dominant in areas where run-time performance is important.

### What’s the point of the L, U and f suffixes on numeric literals?
You should use these suffixes when you need to force the compiler to treat the numeric literal as if it were the specified type. For example, if x is of type float, the expression x + 5.7 is of type double: it first promotes the value of x to a double, then performs the arithmetic using double-precision instructions. If that is what you want, fine; but if you really wanted it to do the arithmetic using single-precision instructions, you can change that code to x + 5.7f. 

### Is !(a < b) logically the same as a >= b? NO.
Example: if a is a floating point NaN, then both a < b and a >= b will be false. That means !(a < b) will be true and a >= b will be false.

If your compiler produces a NaN, it has the unusual property that it is not equal to any value, including itself. For example, if a is NaN, then a == a is false. In fact, if a is NaN, then a will be neither less than, equal to, nor greater than any value including itself. In other words, regardless of the value of b, a < b, a <= b, a > b, a >= b, and a == b will all return false.

```c++
#include <cmath>
void funct(double x)
{
  if (isnan(x)) {   // Though see caveat below
    // x is NaN
    // ...
  } else {
    // x is a normal value
    // ...
  }
}
```

### Why is floating point so inaccurate? Why doesn’t this print 0.43?
```c++
#include <iostream>
int main()
{
  float a = 1000.43;
  float b = 1000.0;
  std::cout << a - b << '\n';
  // ...
}
```
(On one C++ implementation, this prints 0.429993)

Disclaimer: Frustration with rounding/truncation/approximation isn’t really a C++ issue; it’s a computer science issue. However, people keep asking about it on comp.lang.c++, so what follows is a nominal answer.

Answer: Floating point is an approximation. The IEEE standard for 32 bit float supports 1 bit of sign, 8 bits of exponent, and 23 bits of mantissa. Since a normalized binary-point mantissa always has the form 1.xxxxx… the leading 1 is dropped and you get effectively 24 bits of mantissa. The number 1000.43 (and many, many others, including some really common ones like 0.1) is not exactly representable in float or double format. 1000.43 is actually represented as the following bitpattern (the “s” shows the position of the sign bit, the “e“s show the positions of the exponent bits, and the “m“s show the positions of the mantissa bits):
```
    seeeeeeeemmmmmmmmmmmmmmmmmmmmmmm
    01000100011110100001101110000101
```
The shifted mantissa is 1111101000.01101110000101 or 1000 + 7045/16384. The fractional part is 0.429992675781. With 24 bits of mantissa you only get about 1 part in 16M of precision for float. The double type provides more precision (53 bits of mantissa).

## Mixing C and C++
### How do I call a C function from C++?
Just declare the C function extern "C" (in your C++ code) and call it (from your C or C++ code). For example:
```c++
    // C++ code
    extern "C" void f(int); // one way
    extern "C" {    // another way
        int g(double);
        double h();
    };
    void code(int i, double d)
    {
        f(i);
        int ii = g(d);
        double dd = h();
        // ...
    }
```

### How do I call a C++ function from C?
Just declare the C++ function extern "C" (in your C++ code) and call it (from your C or C++ code). For example:
```c++
// C++ code:
extern "C" void f(int);
void f(int i)
{
    // ...
}

///Now f() can be used like this:

/* C code: */
void f(int);
void cc(int i)
{
    f(i);
    /* ... */
}
```

Naturally, this works only for non-member functions. If you want to call member functions (incl. virtual functions) from C, you need to provide a simple wrapper in C++ code that calls the class method.
```c++
// C++ code:
    class C {
        // ...
        virtual double f(int);
    };
    extern "C" double call_C_f(C* p, int i) // wrapper function
    {
        return p->f(i);
    }

//C code will use struct
    /* C code: */
    double call_C_f(struct C* p, int i);
    void ccc(struct C* p, int i)
    {
        double d = call_C_f(p,i);
        /* ... */
    }
```

If you want to call overloaded functions from C, you must provide wrappers with distinct names for the C code to use.
```c++
    // C++ code:
    void f(int);
    void f(double);
    extern "C" void f_i(int i) { f(i); }
    extern "C" void f_d(double d) { f(d); }
```

## General
### How can I tell if an integer is a power of two without looping?
```c++
inline bool isPowerOf2(int i)
{
  return i > 0 && (i & (i - 1)) == 0;
}
```

### What’s the difference between “const X* p”, “X* const p” and “const X* const p”?
Read the pointer declarations right-to-left.

- const X* p means “p points to an X that is const”: the X object can’t be changed via p.
- X* const p means “p is a const pointer to an X that is non-const”: you can’t change the pointer p itself, but you can change the X object via p.
- const X* const p means “p is a const pointer to an X that is const”: you can’t change the pointer p itself, nor can you change the X object via p.

### When should I use references, and when should I use pointers?
Use references when you can, and pointers when you have to.

### Should I use call-by-value or call-by-reference?
That depends on what you are trying to achieve:

- If you want to change the object passed, call by reference or use a pointer; e.g., void f(X&); or void f(X*);.
- If you don’t want to change the object passed and it is big, call by const reference; e.g., void f(const X&);.
- Otherwise, call by value; e.g. void f(X);.

### What are the two steps that happen when I say delete p?
delete p is a two-step process: it calls the destructor, then releases the memory.
```c++
// Original code: delete p;
if (p) {    // or "if (p != nullptr)"
  p->~Fred();
  operator delete(p);
}
```

### In p = new Fred(), does the Fred memory “leak” if the Fred constructor throws an exception? 
No.

If an exception occurs during the Fred constructor of p = new Fred(), the C++ language guarantees that the memory sizeof(Fred) bytes that were allocated will automagically be released back to the heap.

This is what it looks like internally:
```c++
// Original code: Fred* p = new Fred();
Fred* p;
void* tmp = operator new(sizeof(Fred));
try {
  new(tmp) Fred();  // Placement new - calls the Fred constructor. 
  p = (Fred*)tmp;   // The pointer is assigned only if the ctor succeeds; p becomes this pointer
}
catch (...) {
  operator delete(tmp);  // Deallocate the memory
  throw;                 // Re-throw the exception
}
```

### Is it legal (and moral) for a member function to say delete this?
As long as you’re careful, it’s okay (not evil) for an object to commit suicide (delete this).

Here’s how I define “careful”:

- You must be absolutely 100% positively sure that this object was allocated via new (not by new[], nor by placement new, nor a local object on the stack, nor a namespace-scope / global, nor a member of another object; but by plain ordinary new).
- You must be absolutely 100% positively sure that your member function will be the last member function invoked on this object.
- You must be absolutely 100% positively sure that the rest of your member function (after the delete this line) doesn’t touch any piece of this object (including calling any other member functions or touching any data members). This includes code that will run in destructors for any objects allocated on the stack that are still alive.
- You must be absolutely 100% positively sure that no one even touches the this pointer itself after the delete this line. 

### How can I force objects of my class to always be created via new rather than as local, namespace-scope, global, or static?
Make ctors private as in code:
```c++
class Fred {
public:
  // The create() methods are the "named constructors":
  static Fred* create()                 { return new Fred();     }
  static Fred* create(int i)            { return new Fred(i);    }
  static Fred* create(const Fred& fred) { return new Fred(fred); }
  // ...
private:
  // The constructors themselves are private or protected:
  Fred();
  Fred(int i);
  Fred(const Fred& fred);
  // ...
};
```

## OOPS
### What is encapsulation?
Preventing unauthorized access to some piece of information or functionality. In other words hiding implementation level details. Encapsulation doesn’t prevent people from knowing about the inside of a class; it prevents the code they write from becoming dependent on the insides of the class. Encapsulation != security. Encapsulation prevents mistakes, not espionage.

### Should my constructors use “initialization lists” or “assignment”?
Initialization lists. In fact, constructors should initialize as a rule all member objects in the initialization list. That is more efficient.

### Should you use the this pointer in the constructor? 

You can use this in the constructor (in the {body} and even in the initialization list) if you are careful.

Here is something that always works: the {body} of a constructor (or a function called from the constructor) can reliably access the data members declared in a base class and/or the data members declared in the constructor’s own class. This is because all those data members are guaranteed to have been fully constructed by the time the constructor’s {body} starts executing.

### What is the “Named Constructor Idiom”?
With the Named Constructor Idiom, you declare all the class’s constructors in the private or protected sections, and you provide public static methods that return an object. These static methods are the so-called “Named Constructors.” In general there is one such static method for each different way to construct an object.

The Named Constructor Idiom can also be used to make sure your objects are always created via new.

Note that the Named Constructor Idiom, at least as implemented above, is just as fast as directly calling a constructor — modern compilers will not make any extra copies of your object.

### Does return-by-value mean extra copies and extra overhead?

Not necessarily.

All(?) commercial-grade compilers optimize away the extra copy wherever possible.

```c++
class Foo { /*...*/ };

Foo rbv()
{
  // ...
  return Foo(42, 73);  // Suppose Foo has a ctor Foo::Foo(int a, int b)
}

void caller()
{
  Foo x = rbv();  // The return-value of rbv() goes into x
  // ...
}
```

The optimization is done by code similar to below:
```c++
// Pseudo-code
void rbv(void* put_result_here)  // Original C++ code: Foo rbv()
{
  // ...code that initializes (not assigns to) the variable pointed to by put_result_here
}

// Pseudo-code
void caller()
{
  // Original C++ code: Foo x = rbv()
  struct Foo x;  // Note: x does not get initialized prior to calling rbv()
  rbv(&x);       // Note: rbv() initializes a local variable defined in caller()
  // ...
}
```

So the  ingredient in the secret sauce is that the compiler (usually) transforms return-by-value into pass-by-pointer. This means that commercial-grade compilers don’t bother creating a temporary: they directly construct the returned object in the location pointed to by put_result_here.


### What’s the “static initialization order ‘fiasco’ (problem)”?  
A subtle way to crash your program.

The static initialization order problem is a very subtle and commonly misunderstood aspect of C++. Unfortunately it’s very hard to detect — the errors often occur before main() begins.

In short, suppose you have two static objects x and y which exist in separate source files, say x.cpp and y.cpp. Suppose further that the initialization for the y object (typically the y object’s constructor) calls some method on the x object.

That’s it. It’s that simple.

The tough part is that you have a 50%-50% chance of corrupting the program. If the compilation unit for x.cpp happens to get initialized first, all is well. But if the compilation unit for y.cpp get initialized first, then y’s initialization will get run before x’s initialization, and you’re toast. E.g., y’s constructor could call a method on the x object, yet the x object hasn’t yet been constructed.

### How do I prevent the “static initialization order problem” discussed above?

To prevent the static initialization order problem, use the Construct On First Use Idiom, described below.

```c++
// File x.cpp
#include "Fred.h"
Fred& x()
{
  static Fred* ans = new Fred();
  return *ans;
}

// File Barney.cpp
#include "Barney.h"
Barney::Barney()
{
  // ...
  x().goBowling();
  // ...
}
```

Since static local objects are constructed the first time control flows over their declaration (only), the above new Fred() statement will only happen once: the first time x() is called. Every subsequent call will return the same Fred object (the one pointed to by ans). Then all you do is change your usages of x to x():

The downside of this approach is that the Fred object is never destructed. If the Fred object has a destructor with important side effects, there is another technique that answers this concern; but it needs to be used with care since it creates the possibility of another (equally nasty) problem. Problem is that this Fred object cant be used by other statics in their destructors.

```c++
// File x.cpp
#include "Fred.h"
Fred& x()
{
  static Fred ans;  // was static Fred* ans = new Fred();
  return ans;       // was return *ans;
}
```

### What is “placement new” and why would I use it? 
There are many uses of placement new. The simplest use is to place an object at a particular location in memory. This is done by supplying the place as a pointer parameter to the new part of a new expression.

You are also solely responsible for destructing the placed object. This is done by explicitly calling the destructor [f->~Fred();].

### I’m creating a derived class; should my assignment operators call my base class’s assignment operators?

Yes (if you need to define assignment operators in the first place).

If you define your own assignment operators, the compiler will not automatically call your base class’s assignment operators for you. Unless your base class’s assignment operators themselves are broken, you should call them explicitly from your derived class’s assignment operators (again, assuming you create them in the first place).

However if you do not create your own assignment operators, the ones that the compiler create for you will automatically call your base class’s assignment operators.
```c++
class Base {
  // ...
};
class Derived : public Base {
public:
  // ...
  Derived& operator= (const Derived& d);
  Derived& operator= (Derived&& d);
  // ...
};
Derived& Derived::operator= (const Derived& d)
{
  // Make sure self-assignment is benign
  Base::operator= (d);
  // Do the rest of your assignment operator here...
  return *this;
}
Derived& Derived::operator= (Derived&& d)
{
  // self-assignment is not allowed in move assignment
  Base::operator= (std::move(d));
  // Do the rest of your assignment operator here...
  return *this;
}
```

### What are some guidelines / “rules of thumb” for overloading operators?
- If you provide constructive operators, they should return their result by value. For example, x + y should return its result by value. If it returns by reference, you will probably run into lots of problems figuring out who owns the referent and when the referent will get destructed. Doesn’t matter if returning by reference is more efficient; it is probably wrong. See the next bullet for more on this point.
- If you provide constructive operators, they should not change their operands. For example, x + y should not change x.
- If you provide constructive operators, they should allow promotion of the left-hand operand (at least in the case where the class has a single-parameter ctor that is not marked with the explicit keyword). For example, if your class Fraction supports promotion from int to Fraction (via the non-explicit ctor Fraction::Fraction(int)), and if you allow x - y for two Fraction objects, you should also allow 42 - y. In practice that simply means that your operator-() should not be a member function of Fraction. Typically you will make it a friend, if for no other reason than to force it into the public: part of the class, but even if it is not a friend, it should not be a member.
- If you define x++ and ++x, maintain the usual identities. For example, x++ and ++x should have the same observable effect on x, and should differ only in what they return. ++x should return x by reference; x++ should either return a copy (by value) of the original state of x or should have a void return-type. You’re usually better off returning a copy of the original state of x by value, especially if your class will be used in generic algorithms. The easy way to do that is to implement x++ using three lines: make a local copy of *this, call ++x (i.e., this->operator++()), then return the local copy. Similar comments for x-- and --x.
- Avoid overloading short-circuiting operators: x || y or x && y. The overloaded versions of these do not short-circuit — they evaluate both operands even if the left-hand operand “determines” the outcome, so that confuses users.

### How can I overload the prefix and postfix forms of operators ++ and --?
Via a dummy parameter.

Since the prefix and postfix ++ operators can have two definitions, the C++ language gives us two different signatures. Both are called operator++(), but the prefix version takes no parameters and the postfix version takes a dummy int. 

```c++
Number& Number::operator++ () //prefix <-- this is faster as local copy is not made
{
  // ...
  return *this;
}
Number Number::operator++ (int) //postfix
{
  Number ans = *this;
  ++(*this);  // or just call operator++()
  return ans;
}
```

### Do friends violate encapsulation?
No! If they’re used properly, they enhance encapsulation.

“Friend” is an explicit mechanism for granting access, just like membership. You cannot (in a standard conforming program) grant yourself access to a class without modifying its source. For example:

```c++
class X {
    int i;
public:
    void m();       // grant X::m() access
    friend void f(X&);  // grant f(X&) access
    // ...
};
void X::m() { i++; /* X::m() can access X::i */ }
void f(X& x) { x.i++; /* f(X&) can access X::i */ }
```

They provide a degree of freedom in the interface design options.

Member functions and friend functions are equally privileged (100% vested). The major difference is that a friend function is called like f(x), while a member function is called like x.f(). Thus the ability to choose between member functions (x.f()) and friend functions (f(x)) allows a designer to select the syntax that is deemed most readable, which lowers maintenance costs.

The major disadvantage of friend functions is that they require an extra line of code when you want dynamic binding. To get the effect of a virtual friend, the friend function should call a hidden (usually protected) virtual member function. This is called the Virtual Friend Function Idiom. For example:

```c++
class Base {
public:
  friend void f(Base& b);
  // ...
protected:
  virtual void do_f();
  // ...
};
inline void f(Base& b)
{
  b.do_f();
}
class Derived : public Base {
public:
  // ...
protected:
  virtual void do_f();  // "Override" the behavior of f(Base& b)
  // ...
};
void userCode(Base& b)
{
  f(b);
}
```

Another good use of friend functions are the binary infix arithmetic operators. E.g., aComplex + aComplex should be defined as a friend rather than a member if you want to allow aFloat + aComplex as well (member functions don’t allow promotion of the left hand argument, since that would change the class of the object that is the recipient of the member function invocation).






## Exceptions

### Can I throw an exception from a constructor? From a destructor?
For constructors, yes: You should throw an exception from a constructor whenever you cannot properly initialize (construct) an object. There is no really satisfactory alternative to exiting a constructor by a throw. If a constructor throws an exception, the object’s destructor is not run. If your object has already done something that needs to be undone (such as allocating some memory, opening a file, or locking a semaphore), this “stuff that needs to be undone” must be remembered by a data member inside the object.

For destructors, not really: You can throw an exception in a destructor, but that exception must not leave the destructor; if a destructor exits by emitting an exception, all kinds of bad things are likely to happen because the basic rules of the standard library and the language itself will be violated. Don’t do it.

### How can I handle a destructor that fails?  
Write a message to a log-file. Terminate the process. Or call Aunt Tilda. But do not throw an exception!

Here’s why (buckle your seat-belts):

The C++ rule is that you must never throw an exception from a destructor that is being called during the “stack unwinding” process of another exception. For example, if someone says throw Foo(), the stack will be unwound so all the stack frames between the
```c++
    throw Foo()
```
and the
```c++
  }
  catch (Foo e)
  {
```
will get popped. This is called stack unwinding.

During stack unwinding, all the local objects in all those stack frames are destructed. If one of those destructors throws an exception (say it throws a Bar object), the C++ runtime system is in a no-win situation: should it ignore the Bar and end up in the
```c++
  }
  catch (Foo e)
  {
```
where it was originally headed? Should it ignore the Foo and look for a
```c++
  }
  catch (Bar e)
  {
```
handler? There is no good answer — either choice loses information.

So the C++ language guarantees that it will call terminate() at this point, and terminate() kills the process. Bang you’re dead.

The easy way to prevent this is never throw an exception from a destructor. But if you really want to be clever, you can say never throw an exception from a destructor while processing another exception. But in this second case, you’re in a difficult situation: the destructor itself needs code to handle both throwing an exception and doing “something else”, and the caller has no guarantees as to what might happen when the destructor detects an error (it might throw an exception, it might do “something else”). So the whole solution is harder to write. So the easy thing to do is always do “something else”. That is, never throw an exception from a destructor.

Of course the word never should be “in quotes” since there is always some situation somewhere where the rule won’t hold. But certainly at least 99% of the time this is a good rule of thumb.

### What should I throw?  
C++, unlike just about every other language with exceptions, is very accomodating when it comes to what you can throw. In fact, you can throw anything you like. That begs the question then, what should you throw?

Generally, it’s best to throw objects, not built-ins. If possible, you should throw instances of classes that derive (ultimately) from the std::exception class. By making your exception class inherit (ultimately) from the standard exception base-class, you are making life easier for your users (they have the option of catching most things via std::exception), plus you are probably providing them with more information (such as the fact that your particular exception might be a refinement of std::runtime_error or whatever).

The most common practice is to throw a temporary:
```c++
#include <stdexcept>
class MyException : public std::runtime_error {
public:
  MyException() : std::runtime_error("MyException") { }
};
void f()
{
   // ...
   throw MyException();
}
```
Here, a temporary of type MyException is created and thrown. Class MyException inherits from class std::runtime_error which (ultimately) inherits from class std::exception.

### What should I catch?  
In keeping with the C++ tradition of “there’s more than one way to do that” (translation: “give programmers options and tradeoffs so they can decide what’s best for them in their situation”), C++ allows you a variety of options for catching.

You can catch by value.
You can catch by reference.
You can catch by pointer.
In fact, you have all the flexibility that you have in declaring function parameters, and the rules for whether a particular exception matches (i.e., will be caught by) a particular catch clause are almost exactly the same as the rules for parameter compatibility when calling a function.

Given all this flexibility, how do you decide what to catch? Simple: unless there’s a good reason not to, catch by reference. Avoid catching by value, since that causes a copy to be made and the copy can have different behavior from what was thrown. Only under very special circumstances should you catch by pointer.

### How do I throw polymorphically?  
Sometimes people write code like:
```c++
class MyExceptionBase { };
class MyExceptionDerived : public MyExceptionBase { };
void f(MyExceptionBase& e)
{
  // ...
  throw e;
}
void g()
{
  MyExceptionDerived e;
  try {
    f(e);
  }
  catch (MyExceptionDerived& e) {
    // ...code to handle MyExceptionDerived...
  }
  catch (...) {
    // ...code to handle other exceptions...
  }
}
```
If you try this, you might be surprised at run-time when your catch (...) clause is entered, and not your catch (MyExceptionDerived&) clause. This happens because you didn’t throw polymorphically. In function f(), the statement throw e; throws an object with the same type as the static type of the expression e. In other words, it throws an instance of MyExceptionBase. The throw statement behaves as-if the thrown object is copied, as opposed to making a “virtual copy”.

Fortunately it’s relatively easy to correct:
```c++
class MyExceptionBase {
public:
  virtual void raise();
};
void MyExceptionBase::raise()
{ throw *this; }
class MyExceptionDerived : public MyExceptionBase {
public:
  virtual void raise();
};
void MyExceptionDerived::raise()
{ throw *this; }
void f(MyExceptionBase& e)
{
  // ...
  e.raise();
}
void g()
{
  MyExceptionDerived e;
  try {
    f(e);
  }
  catch (MyExceptionDerived& e) {
    // ...code to handle MyExceptionDerived...
  }
  catch (...) {
    // ...code to handle other exceptions...
  }
}
```
Note that the throw statement has been moved into a virtual function. The statement e.raise() will exhibit polymorphic behavior, since raise() is declared virtual and e was passed by reference. As before, the thrown object will be of the static type of the argument in the throw statement, but within MyExceptionDerived::raise(), that static type is MyExceptionDerived, not MyExceptionBase.

## Why doesn’t C++ provide a “finally” construct?  
Because C++ supports an alternative that is almost always better: The “resource acquisition is initialization” technique. The basic idea is to represent a resource by a local object, so that the local object’s destructor will release the resource. That way, the programmer cannot forget to release the resource.

