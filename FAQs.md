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

## Inheritance - part-of and kind-of

### Why can’t my derived class access private things from my base class?

To protect you from future changes to the base class.

Derived classes do not get access to private members of a base class. This effectively “seals off” the derived class from any changes made to the private members of the base class.

### What is a “virtual member function”?

A virtual function allows derived classes to replace the implementation provided by the base class. The compiler makes sure the replacement is always called whenever the object in question is actually of the derived class, even if the object is accessed by a base pointer rather than a derived pointer. This allows algorithms in the base class to be replaced in the derived class, even if users don’t know about the derived class.

The derived class can either fully replace (“override”) the base class member function, or the derived class can partially replace (“augment”) the base class member function. The latter is accomplished by having the derived class member function call the base class member function, if desired.

### What is a pure virtual function?
A pure virtual function is a function that must be overridden in a derived class and need not be defined. A virtual function is declared to be “pure” using the curious =0 syntax.
```c++
    class Base {
    public:
        void f1();      // not virtual
        virtual void f2();  // virtual, not pure
        virtual void f3() = 0;  // pure virtual
    };
    Base b; // error: pure virtual f3 not overridden
```

In fact, a class with no data and where all functions are pure virtual functions is often called an interface.

### What’s the difference between how virtual and non-virtual member functions are called? 
Non-virtual member functions are resolved statically. That is, the member function is selected statically (at compile-time) based on the type of the pointer (or reference) to the object.

In contrast, virtual member functions are resolved dynamically (at run-time). That is, the member function is selected dynamically (at run-time) based on the type of the object, not the type of the pointer/reference to that object. This is called “dynamic binding.” Most compilers use some variant of the following technique: if the object has one or more virtual functions, the compiler puts a hidden pointer in the object called a “virtual-pointer” or “v-pointer.” This v-pointer points to a global table called the “virtual-table” or “v-table.”

The compiler creates a v-table for each class that has at least one virtual function. For example, if class Circle has virtual functions for draw() and move() and resize(), there would be exactly one v-table associated with class Circle, even if there were a gazillion Circle objects, and the v-pointer of each of those Circle objects would point to the Circle v-table. The v-table itself has pointers to each of the virtual functions in the class. For example, the Circle v-table would have three pointers: a pointer to Circle::draw(), a pointer to Circle::move(), and a pointer to Circle::resize().

During a dispatch of a virtual function, the run-time system follows the object’s v-pointer to the class’s v-table, then follows the appropriate slot in the v-table to the method code.

### What happens in the hardware when I call a virtual function? How many layers of indirection are there? How much overhead is there?
The answer is entirely compiler-dependent, so your mileage may vary, but most C++ compilers use a scheme similar to the one presented here.

Let’s work an example. Suppose class Base has 5 virtual functions: virt0() through virt4().
```c++
// Your original C++ source code
class Base {
public:
  virtual arbitrary_return_type virt0( /*...arbitrary params...*/ );
  virtual arbitrary_return_type virt1( /*...arbitrary params...*/ );
  virtual arbitrary_return_type virt2( /*...arbitrary params...*/ );
  virtual arbitrary_return_type virt3( /*...arbitrary params...*/ );
  virtual arbitrary_return_type virt4( /*...arbitrary params...*/ );
  // ...
};
```

Step #1: the compiler builds a static table containing 5 function-pointers, burying that table into static memory somewhere. Many (not all) compilers define this table while compiling the .cpp that defines Base’s first non-inline virtual function. We call that table the v-table; let’s pretend its technical name is Base::__vtable. If a function pointer fits into one machine word on the target hardware platform, Base::__vtable will end up consuming 5 hidden words of memory. Not 5 per instance, not 5 per function; just 5. It might look something like the following pseudo-code:
```c++
// Pseudo-code (not C++, not C) for a static table defined within file Base.cpp
// Pretend FunctionPtr is a generic pointer to a generic member function
// (Remember: this is pseudo-code, not C++ code)
FunctionPtr Base::__vtable[5] = {
  &Base::virt0, &Base::virt1, &Base::virt2, &Base::virt3, &Base::virt4
};
```

Step #2: the compiler adds a hidden pointer (typically also a machine-word) to each object of class Base. This is called the v-pointer. Think of this hidden pointer as a hidden data member, as if the compiler rewrites your class to something like this:
```c++
// Your original C++ source code
class Base {
public:
  // ...
  FunctionPtr* __vptr;  // Supplied by the compiler, hidden from the programmer
  // ...
};
```

Step #3: the compiler initializes this->__vptr within each constructor. The idea is to cause each object’s v-pointer to point at its class’s v-table, as if it adds the following instruction in each constructor’s init-list:
```c++
Base::Base( /*...arbitrary params...*/ )
  : __vptr(&Base::__vtable[0])  // Supplied by the compiler, hidden from the programmer
  // ...
{
  // ...
}
```
Now let’s work out a derived class. Suppose your C++ code defines class Der that inherits from class Base. The compiler repeats steps #1 and #3 (but not #2). In step #1, the compiler creates a hidden v-table, keeping the same function-pointers as in Base::__vtable but replacing those slots that correspond to overrides. For instance, if Der overrides virt0() through virt2() and inherits the others as-is, Der’s v-table might look something like this (pretend Der doesn’t add any new virtuals):
```c++
// Pseudo-code (not C++, not C) for a static table defined within file Der.cpp
// Pretend FunctionPtr is a generic pointer to a generic member function
// (Remember: this is pseudo-code, not C++ code)
FunctionPtr Der::__vtable[5] = {
  &Der::virt0, &Der::virt1, &Der::virt2, &Base::virt3, &Base::virt4
                                          ↑↑↑↑          ↑↑↑↑ // Inherited as-is
};
```
In step #3, the compiler adds a similar pointer-assignment at the beginning of each of Der’s constructors. The idea is to change each Der object’s v-pointer so it points at its class’s v-table. (This is not a second v-pointer; it’s the same v-pointer that was defined in the base class, Base; remember, the compiler does not repeat step #2 in class Der.)

Finally, let’s see how the compiler implements a call to a virtual function. Your code might look like this:
```c++
// Your original C++ code
void mycode(Base* p)
{
  p->virt3();
}
```
The compiler has no idea whether this is going to call Base::virt3() or Der::virt3() or perhaps the virt3() method of another derived class that doesn’t even exist yet. It only knows for sure that you are calling virt3() which happens to be the function in slot #3 of the v-table. It rewrites that call into something like this:
```c++
// Pseudo-code that the compiler generates from your C++
void mycode(Base* p)
{
  p->__vptr[3](p);
}
```

On typical hardware, the machine-code is two ‘load’s plus a call:

The first load gets the v-pointer, storing it into a register, say r1.
The second load gets the word at r1 + 3*4 (pretend function-pointers are 4-bytes long, so r1 + 12 is the pointer to the right class’s virt3() function). Pretend it puts that word into register r2 (or r1 for that matter).
The third instruction calls the code at location r2.
Conclusions:

Objects of classes with virtual functions have only a small space-overhead compared to those that don’t have virtual functions.
Calling a virtual function is fast — almost as fast as calling a non-virtual function.
You don’t get any additional per-call overhead no matter how deep the inheritance gets. You could have 10 levels of inheritance, but there is no “chaining” — it’s always the same — fetch, fetch, call.

### When should my destructor be virtual? 
When someone will delete a derived-class object via a base-class pointer.

So when should I declare a destructor virtual? Whenever the class has at least one virtual function. Having virtual functions indicate that a class is meant to act as an interface to derived classes, and when it is, an object of a derived class may be destroyed through a pointer to the base. 

```c++
    class Base {
        // ...
        virtual ~Base();
    };
    class Derived : public Base {
        // ...
        ~Derived();
    };
    void f()
    {
        Base* p = new Derived;
        delete p;   // virtual destructor used to ensure that ~Derived is called
    }
```

### Why don’t we have virtual constructors?

A virtual call is a mechanism to get work done given partial information. In particular, virtual allows us to call a function knowing only an interfaces and not the exact type of the object. To create an object you need complete information. In particular, you need to know the exact type of what you want to create. Consequently, a “call to a constructor” cannot be virtual.


### Is an array of Derived a kind-of array of Base?

Nope.. 
```c++
class Base {
public:
  virtual void f();             // 1
};
class Derived : public Base {
public:
  // ...
private:
  int i_;                       // 2
};
void userCode(Base* arrayOfBase)
{
  arrayOfBase[1].f();           // 3
}
int main()
{
  Derived arrayOfDerived[10];   // 4
  userCode(arrayOfDerived);     // 5
  // ...
}
```
The compiler thinks this is perfectly type-safe. Line 5 converts a Derived* to a Base*. But in reality it is horrendously evil: since Derived is larger than Base, the pointer arithmetic done on line 3 is incorrect: the compiler uses sizeof(Base) when computing the address for arrayOfBase[1], yet the array is an array of Derived, which means the address computed on line 3 (and the subsequent invocation of member function f()) isn’t even at the beginning of any object! It’s smack in the middle of a Derived object. 

The root problem is that C++ can’t distinguish between a pointer-to-a-thing and a pointer-to-an-array-of-things. Naturally C++ “inherited” this feature from C.

NOTE: If we had used an array class (e.g., std::array<Derived, 10> from the standard library) instead of using a raw array, this problem would have been properly trapped as an error at compile time rather than a run-time disaster.

### final specifier (since C++11) - How can I set up my class so it won’t be inherited from?

Specifies that a virtual function cannot be overridden in a derived class, or that a class cannot be derived from.

```c++
struct Base
{
    virtual void foo();
};
 
struct A : Base
{
    void foo() final; // Base::foo is overridden and A::foo is the final override
    void bar() final; // Error: bar cannot be final as it is non-virtual
};
 
struct B final : A // struct B is final
{
    void foo() override; // Error: foo cannot be overridden as it is final in A
};
 
struct C : B {}; // Error: B is final
```

But also ask yourself why you want to? There are two common answers:

For efficiency: to avoid your function calls being virtual.
For safety: to ensure that your class is not used as a base class (for example, to be sure that you can copy objects without fear of slicing).

### How are “private inheritance” and “composition” similar? 

private inheritance is a syntactic variant of composition (AKA aggregation and/or has-a).

E.g., the “Car has-a Engine” relationship can be expressed using simple composition:
```c++
class Engine {
public:
  Engine(int numCylinders);
  void start();                 // Starts this Engine
};

class Car {
public:
  Car() : e_(8) { }             // Initializes this Car with 8 cylinders
  void start() { e_.start(); }  // Start this Car by starting its Engine
private:
  Engine e_;                    // Car has-a Engine
};
```

The “Car has-a Engine” relationship can also be expressed using private inheritance:
```c++
class Car : private Engine {    // Car has-a Engine
public:
  Car() : Engine(8) { }         // Initializes this Car with 8 cylinders
  using Engine::start;          // Start this Car by starting its Engine
};
```
There are several similarities between these two variants:

- In both cases there is exactly one Engine member object contained in every Car object
- In neither case can users (outsiders) convert a Car* to an Engine*
- In both cases the Car class has a start() method that calls the start() method on the contained Engine object.
- There are also several distinctions:

The simple-composition variant is needed if you want to contain several Engines per Car
- The private-inheritance variant can introduce unnecessary multiple inheritance
- The private-inheritance variant allows members of Car to convert a Car* to an Engine*
- The private-inheritance variant allows access to the protected members of the base class
- The private-inheritance variant allows Car to override Engine’s virtual functions
- The private-inheritance variant makes it slightly simpler (20 characters compared to 28 characters) to give Car a start() method that simply calls through to the Engine’s start() method

***Use composition when you can, private inheritance when you have to.***

### What are the access rules with private and protected inheritance?  
Take these classes as examples:
```c++
class B                    { /*...*/ };
class D_priv : private   B { /*...*/ };
class D_prot : protected B { /*...*/ };
class D_publ : public    B { /*...*/ };
class UserClass            { B b; /*...*/ };
```
None of the derived classes can access anything that is private in B. In D_priv, the public and protected parts of B are private. In D_prot, the public and protected parts of B are protected. In D_publ, the public parts of B are public and the protected parts of B are protected (D_publ is-a-kind-of-a B). class UserClass can access only the public parts of B, which “seals off” UserClass from B.

To make a public member of B public in D_priv or D_prot, state the name of the member with a B:: prefix. E.g., to make member B::f(int,float) public in D_prot, you would say:
```c++
class D_prot : protected B {
public:
  using B::f;  // Note: Not using B::f(int,float)
};
```

### What is the “dreaded diamond”?  
The “dreaded diamond” refers to a class structure in which a particular class appears more than once in a class’s inheritance hierarchy. For example,

```c++
class Base {
public:
  // ...
protected:
  int data_;
};
class Der1 : public Base { /*...*/ };
class Der2 : public Base { /*...*/ };
class Join : public Der1, public Der2 {
public:
  void method()
  {
     data_ = 1;  // Bad: this is ambiguous; see below
  }
};
int main()
{
  Join* j = new Join();
  Base* b = j;   // Bad: this is ambiguous; see below
}
```
```

                         Base
                         /  \
                        /    \
                       /      \
                    Der1      Der2
                       \      /
                        \    /
                         \  /
                         Join
```
This structure is often called the dreaded diamond, but it really isn’t dreaded; it’s more just something to be aware of.

The key is to realize that Base is inherited twice, which means any data members declared in Base, such as data_ above, will appear twice within a Join object. This can create ambiguities: which data_ did you want to change? For the same reason the conversion from Join* to Base*, or from Join& to Base&, is ambiguous: which Base class subobject did you want?

C++ lets you resolve the ambiguities. For example, instead of saying data_ = 1 you could say Der2::data_ = 1, or you could convert from Join* to a Der1* and then to a Base*.

### Where in a hierarchy should I use virtual inheritance?

Just below the top of the diamond, not at the join-class.

To avoid the duplicated base class subobject that occurs with the “dreaded diamond”, you should use the virtual keyword in the inheritance part of the classes that derive directly from the top of the diamond:
```c++
class Base {
public:
  // ...
protected:
  int data_;
};

class Der1 : public virtual Base {
                    ↑↑↑↑↑↑↑ // This is the key
public:
  // ...
};

class Der2 : public virtual Base {
                    ↑↑↑↑↑↑↑ // This is the key
public:
  // ...
};

class Join : public Der1, public Der2 {
public:
  void method()
  {
     data_ = 1;  // Good: this is now unambiguous
  }
};

int main()
{
  Join* j = new Join();
  Base* b = j;   // Good: this is now unambiguous
}
```
Because of the virtual keyword in the base-class portion of Der1 and Der2, an instance of Join will have only a single Base subobject. This eliminates the ambiguities. This is usually better than using full qualification as described in the previous FAQ.

For emphasis, the virtual keyword goes in the hierarchy above Der1 and Der2. It doesn’t help to put the virtual keyword in the Join class itself. In other words, you have to know that a join class will exist when you are creating class Der1 and Der2.
```
                         Base
                         /  \
                        /    \
               virtual /      \ virtual
                    Der1      Der2
                       \      /
                        \    /
                         \  /
                         Join
```

### What does it mean to “delegate to a sister class” via virtual inheritance?  
Consider the following example:
```c++
class Base {
public:
  virtual void foo() = 0;
  virtual void bar() = 0;
};

class Der1 : public virtual Base {
public:
  virtual void foo();
};

void Der1::foo()
{ bar(); }

class Der2 : public virtual Base {
public:
  virtual void bar();
};

class Join : public Der1, public Der2 {
public:
  // ...
};

int main()
{
  Join* p1 = new Join();
  Der1* p2 = p1;
  Base* p3 = p1;
  p1->foo();
  p2->foo();
  p3->foo();
}
```
Believe it or not, when Der1::foo() calls this->bar(), it ends up calling Der2::bar(). Yes, that’s right: a class that Der1 knows nothing about will supply the override of a virtual function invoked by Der1::foo(). This “cross delegation” can be a powerful technique for customizing the behavior of polymorphic classes.


### What special considerations do I need to know about when I inherit from a class that uses virtual inheritance?  
Initialization list of most-derived-class’s ctor directly invokes the virtual base class’s ctor.

Because a virtual base class subobject occurs only once in an instance, there are special rules to make sure the virtual base class’s constructor and destructor get called exactly once per instance. The C++ rules say that virtual base classes are constructed before all non-virtual base classes. The thing you as a programmer need to know is this: constructors for virtual base classes anywhere in your class’s inheritance hierarchy are called by the “most derived” class’s constructor.

Practically speaking, this means that when you create a concrete class that has a virtual base class, you must be prepared to pass whatever parameters are required to call the virtual base class’s constructor. And, of course, if there are several virtual base classes anywhere in your classes ancestry, you must be prepared to call all their constructors. This might mean that the most-derived class’s constructor needs more parameters than you might otherwise think.

## Templates

### What is a “parameterized type” or What is “genericity”?? 
Another way to say, “class templates.”

A parameterized/genericity type is a type that is parameterized over another type or some value. List<int> is a type (List) parameterized over another type (int).

### Why can’t I separate the definition of my templates class from its declaration and put it inside a .cpp file?  
If all you want to know is how to fix this situation, read the next two FAQs. But in order to understand why things are the way they are, first accept these facts:

A template is not a class or a function. A template is a “pattern” that the compiler uses to generate a family of classes or functions.
In order for the compiler to generate the code, it must see both the template definition (not just declaration) and the specific types/whatever used to “fill in” the template. 

## Containers
### Is the storage for a std::vector<T> or a std::array<T,N> guaranteed to be contiguous?
Yes.

This means the following technique is safe:
```c++
#include <vector>
#include <array>
#include "Foo.h"  /* get class Foo */
// old-style code that wants an array
void f(Foo* array, unsigned numFoos);
void g()
{
  std::vector<Foo> v;
  std::array<Foo, 10> a;
  // ...
  f(v.data(), v.size());  // Safe
  f(a.data(), a.size());  // Safe
}
```

In general, it means you are guaranteed that &v[0] + n == &v[n], where v is a non-empty std::vector<T> or std::array<T,N> and n is an integer in the range 0 .. v.size()-1.

However v.begin() is not guaranteed to be a T*, which means v.begin() is not guaranteed to be the same as &v[0]:
```c++
void g()
{
  std::vector<Foo> v;
  // ...
  f(v.begin(), v.size());  // error, not guaranteed to be the same as &v[0]
    ↑↑↑↑↑↑↑↑↑ // cough, choke, gag; use v.data() instead
}
```
Also, using &v[0] is undefined behavior if the std::vector or std::array is empty, while it is always safe to use the .data() function.


### How do you tell the compiler to make a member function inline?  
The declaration of an inline member function looks just like the declaration of a non-inline member function:
```c++
class Fred {
public:
  void f(int i, char c);
};
```
But when you define an inline member function (the {...} part), you prepend the member function’s definition with the keyword inline, and you (almost always) put the definition into a header file:
```c++
inline void Fred::f(int i, char c)
{
  // ...
}
```
The reason you (almost always) put the definition (the {...} part) of an inline function in a header file is to avoid “unresolved external” errors from the linker. That error will occur if you put the inline function’s definition in a .cpp file and if that function is called from some other .cpp file.

Another way to make member function inline is: define the member function in the class body itself:
```c++
class Fred {
public:
  void f(int i, char c)
    {
      // ...
    }
};
```

## Mermber Functions and Pointers

### Is the type of “pointer-to-member-function” different from “pointer-to-function”?
Yes. Consider the following function:
```
int f(char a, float b);
```
The type of this function is different depending on whether it is an ordinary function or a non-static member function of some class:

- Its type is **“int (*)(char,float)”** if an ordinary function
- Its type is **“int (Fred::*)(char,float)”** if a non-static member function of class Fred
- Note: if it’s a static member function of class Fred, its type is the same as if it were an ordinary function: **“int (*)(char,float)”**.

### Why am I having trouble taking the address of a C++ function?
Non-static member functions have a hidden parameter that corresponds to the this pointer. The this pointer points to the instance data for the object. You must use “normal” functions (non class members) or static member functions when a function pointer is needed to be passed around. C++ introduces a new type of pointer, called a pointer-to-member, which can be invoked only by providing an object.

### How can I avoid syntax errors when calling a member function using a pointer-to-member-function?
If you have access to a compiler and standard library that implements the appropriate parts of the upcoming C++17 standard, use std::invoke. Otherwise, use a #define macro.

```c++
class Fred {
public:
  int f(char x, float y);
  int g(char x, float y);
  int h(char x, float y);
  int i(char x, float y);
  // ...
};

typedef  int (Fred::*FredMemFn)(char x, float y);  // Please do this!
```
use it as:
```c++
void userCode(Fred& fred, FredMemFn p)  // Use a typedef for pointer-to-member types
{
  int ans = std::invoke(p, fred, 'x', 3.14);
  // Would normally be: int ans = (fred.*p)('x', 3.14);
  // ...
}
```
OR
```c++
#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))
//Note: FredMemFn is a typedef for a pointer-to-member type:

void userCode(Fred& fred, FredMemFn p)  // Use a typedef for pointer-to-member types
{
  int ans = CALL_MEMBER_FN(fred,p)('x', 3.14);
  // Would normally be: int ans = (fred.*p)('x', 3.14);
  // ...
}
```

### How do I declare a pointer-to-member-function that points to a const member function?
```c++
class Fred {
public:
  int f(int i) const;
  int g(int i) const;
  int h(int j) const;
  // ...
};
```
Then when you use a typedef to declare the member-function-pointer type, it should look like this:
```c++
// FredMemFn points to a const member-function of Fred that takes (int)
typedef  int (Fred::*FredMemFn)(int) const;
                                     ↑↑↑↑↑ // Points only to member functions decorated with const
```

### Can I convert a pointer-to-member-function to a void*? 
No. It may or may not work. Technical details: pointers to member functions and pointers to data are not necessarily represented in the same way. A pointer to a member function might be a data structure rather than a single pointer. Think about it: if it’s pointing at a virtual function, it might not actually be pointing at a statically resolvable pile of code, so it might not even be a normal address — it might be a different data structure of some sort.

### Can I convert a pointer-to-function to a void*?
No. Might fail as it is undefined benavior.
```c++
int f(char x, float y);
int g(char x, float y);
typedef int(*FunctPtr)(char,float);
int callit(FunctPtr p, char x, float y)
{
  return p(x, y);
}
int main()
{
  FunctPtr p = f;
  void* p2 = (void*)p;              // ← illegal!!
  callit(p, 'x', 3.14f);            // okay
  callit(FunctPtr(p2), 'x', 3.14f); // might fail!!
  // ...
}
```

Technical details: void* pointers are pointers to data, and function pointers point to functions. The language does not require functions and data to be in the same address space, so, by way of example and not limitation, on architectures that have them in different address spaces, the two different pointer types will not be comparable.

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

## c++ 11

### Rvalue references and move semantics

In C++11, we can define “move constructors” and “move assignments” to move rather than copy their argument:
```c++
    template<class T> class vector {
        // ...
        vector(const vector&);          // copy constructor
        vector(vector&&);           // move constructor
        vector& operator=(const vector&);   // copy assignment
        vector& operator=(vector&&);        // move assignment
    };  // note: move constructor and move assignment takes non-const &&
        // they can, and usually do, write to their argument
```
The && indicates an “rvalue reference”. An rvalue reference can bind to an rvalue (but not to an lvalue):
```c++
    X a;
    X f();
    X& r1 = a;      // bind r1 to a (an lvalue)
    X& r2 = f();    // error: f() is an rvalue; can't bind
    X&& rr1 = f();  // fine: bind rr1 to temporary
    X&& rr2 = a;    // error: bind a is an lvalue
```
The idea behind a move assignment is that instead of making a copy, it simply takes the representation from its source and replaces it with a cheap default. 

How do we know whether it’s ok to simply move from a source? We tell the compiler:
```c++
    template<class T> 
    void swap(T& a, T& b)   // "perfect swap" (almost)
    {
        T tmp = move(a);    // could invalidate a
        a = move(b);        // could invalidate b
        b = move(tmp);      // could invalidate tmp
    }
```
move(x) is just a cast that means “you can treat x as an rvalue”. Maybe it would have been better if move() had been called rval(), but by now move() has been used for years. The move() template function can be written in C++11 (see the “brief introduction”) and and uses rvalue references.

Rvalue references can also be used to provide perfect forwarding.

In the C++11 standard library, all containers are provided with move constructors and move assignments, and operations that insert new elements, such as insert() and push_back(), have versions that take rvalue references. The net result is that the standard containers and algorithms quietly – without user intervention – improve in performance because they copy less.

For more details, see: https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n2027.html

### Lambdas

A lambda expression is a mechanism for specifying a function object. The primary use for a lambda is to specify a simple action to be performed by some function. For example:
```c++
    vector<int> v = {50, -10, 20, -30};

    std::sort(v.begin(), v.end(), [](int a, int b) { return abs(a)<abs(b); });
    // now v should be { -10, 20, -30, 50 }
```

If an action is neither common nor simple, consider using a named function object or function. For example, the example above could have been written:
```c++
    void f(vector<Record>& v)
    {
        vector<int> indices(v.size());
        int count = 0;
        generate(indices.begin(),indices.end(),[&](){ return ++count; });
        struct Cmp_names {
            const vector<Record>& vr;
            Cmp_names(const vector<Record>& r) :vr(r) { }
            bool operator()(int a, int b) const { return vr[a].name<vr[b].name; }
        };
        // sort indices in the order determined by the name field of the records:
        std::sort(indices.begin(), indices.end(), Cmp_names(v));
        // ...
    }
```

### noexcept to prevent exception propagation
If a function declared noexcept throws (so that the exception tries to escape the noexcept function) the program is terminated by a call to std::terminate().

It is possible to make a function conditionally noexcept. For example, an algorithm can be specified to be noexcept if (and only if) the operations it uses on a template argument are noexcept:
```c++
    template<class T>
    void do_f(vector<T>& v) noexcept(noexcept(f(v.at(0)))) // can throw if f(v.at(0)) can
    {
        for(int i; i<v.size(); ++i)
            v.at(i) = f(v.at(i));
    }
```
Here, we first use noexcept as an operator: noexcept(f(v.at(0))) is true if f(v.at(0)) can’t throw, that is if the f() and at() used are noexcept.

The noexcept() operator is a constant expression and does not evaluate its operand.

The general form of a noexcept declaration is noexcept(expression) and “plain noexcept” is simply a shorthand for noexcept(true). All declarations of a function must have compatible noexcept specifications.

A destructor shouldn’t throw; a generated destructor is implicitly noexcept (independently of what code is in its body) if all of the members of its class have noexcept destructors (which, ahem, they too will have by default).

It is typically a bad idea to have a move operation throw, so declare those noexcept wherever possible. A generated copy or move operation is implicitly noexcept if all of the copy or move operations it uses on members of its class have noexcept destructors.

noexcept is widely and systematically used in the standard library to improve performance and clarify requirements.

### In-class member initializers

In C++98, only static const members of integral types could be initialized in-class, and the initializer has to be a constant expression. These restrictions ensured that the compiler can do the initialization at compile-time. For example:
```c++
    int var = 7;
    class X {
        static const int m1 = 7;        // ok
        const int m2 = 7;                   // error: not static
        static int m3 = 7;              // error: not const
        static const int m4 = var;          // error: initializer not constant expression
        static const string m5 = "odd"; // error: not integral type
        // ...
    };
```
The basic idea for C++11 was to allow a non-static data member to be initialized where it is declared (in its class). A constructor can then use the initializer when run-time initialization is needed. Consider:
```c++
    class A {
    public:
        int a = 7;
    };
```
This is equivalent to:
```c++
    class A {
    public:
        int a;
        A() : a(7) {}
    };
```

### Thread-local storage  
In C++11 you can use the storage class thread_local to define a variable that should be instantiated once per thread.

Note that using thread_local storage requires care, and in particular does not work well with most parallel algorithms.

### static_assert compile-time assertions  
A static (compile time) assertion consists of a constant expression and a string literal:

    static_assert(expression,string);
The compiler evaluates the expression and writes the string as an error message if the expression is false (i.e., if the assertion failed). For example:
```c++
    static_assert(sizeof(long)>=8, "64-bit code generation required for this library.");
    struct S { X m1; Y m2; };
    static_assert(sizeof(S)==sizeof(X)+sizeof(Y),"unexpected padding in S");
```
A static_assert can be useful to make assumptions about a program and its treatment by a compiler explicit.

## Threads in c++ 11

A thread is launched by constructing a std::thread with a function or a function object (incl. a lambda):

```c++
    #include <thread>
    void f();
    struct F {
        void operator()();
    };
    int main()
    {
        std::thread t1{f};     // f() executes in separate thread
        std::thread t2{F()};   // F()() executes in separate thread

        t1.join();  // wait for t1
        t2.join();  // wait for t2
    }
```

Typically, we’d like to pass some arguments to the task to be executed (here we are calling something executed by a thread a “task”). In general, we’d also like to get a result back from an executed task. With plain tasks, there is no notion of a return value; std::future is the correct default choice for that. Alternatively, we can pass an argument to a task telling it where to put its result: For example:

```c++
    void f(vector<double>&, double* res);   // place result in res
    struct F {
        vector<double>& v;
        double* res;
        F(vector<double>& vv, double* p) :v{vv}, res{p} { }
        void operator()();  // place result in res
    };
    int main()
    {
        double res1;
        double res2;

        //the standard library bind makes a function object of its arguments.
        std::thread t1{std::bind(f,some_vec,&res1)};    // f(some_vec,&res1) executes in separate thread
        std::thread t2{F(some_vec,&res2)};      // F(some_vec,&res2)() executes in separate thread
        t1.join();
        t2.join();
        std::cout << res1 << ' ' << res2 << '\n';
    }
```

### Mutual exclusion 
A mutex is a primitive object used for controlling access in a multi-threaded system. The most basic use is:
```c++
    std::mutex m;
    int sh; // shared data
    // ...
    m.lock();
    // manipulate shared data:
    sh+=1;
    m.unlock();
```

In addition to lock(), a mutex has a try_lock() operation which can be used to try to get into the critical region without the risk of getting blocked:
```c++
    std::mutex m;
    int sh; // shared data
    // ...
    if (m.try_lock()) {
        // manipulate shared data:
        sh+=1;
        m.unlock();
    else {
        // maybe do something else
    }
```

***Timed Mutex***
What if you need to acquire a mutex within the next ten seconds? The timed_mutex class is offered for that. Its operations are specialized versions of try_lock() with an associated time limit:

    std::timed_mutex m;
    int sh; // shared data
    // ...
    if (m.try_lock_for(std::chrono::seconds(10))) {
        // manipulate shared data:
        sh+=1;
        m.unlock();
    }
    else {
        // we didn't get the mutex; do something else
    }

### Locks
A lock is an object that can hold a reference to a mutex and may unlock() the mutex during the lock’s destruction (such as when leaving block scope). A thread may use a lock to aid in managing mutex ownership in an exception safe manner. In other words, a lock implements Resource Acquisition Is Initialization for mutual exclusion. For example:
```c++
    std::mutex m;
    int sh; // shared data
    // ...
    void f()
    {
        // ...
        std::unique_lock lck(m);
        // manipulate shared data: lock will be released even if this code throws an exception
        sh+=1;
    }
```

we can use a unique_lock to do try_lock:
```c++
    std::mutex m;
    int sh; // shared data
    // ...
    void f()
    {
        // ...
        std::unique_lock lck(m,std::defer_lock);    // make a lock, but don't acquire the mutex
        // ...
        if (lck.try_lock()) {
            // manipulate shared data:
            sh+=1;
        }
        else {
            // maybe do something else
        }
    }
```
Similarly, unique_lock supports try_lock_for() and try_lock_until(). What you get from using a lock rather than the mutex directly is exception handling and protection against forgetting to unlock(). In concurrent programming, we need all the help we can get.

### Futures and promises
C++11 offers future and promise for returning a value from a task spawned on a separate thread, and packaged_task to help launch tasks. The important point about future and promise is that they enable a transfer of a value between two tasks without explicit use of a lock; “the system” implements the transfer efficiently. The basic idea is simple: When a task wants to return a value to the thread that launched it, it puts the value into a promise. Somehow, the implementation makes that value appear in the future attached to the promise. 

### async
Here is an example of a way for the programmer to rise above the messy threads-plus-lock level of concurrent programming:
```c++
    template<class T, class V> struct Accum  {  // simple accumulator function object
        T* b;
        T* e;
        V val;
        Accum(T* bb, T* ee, const V& v) : b{bb}, e{ee}, val{vv} {}
        V operator() () { return std::accumulate(b,e,val); }
    };
    double comp(vector<double>& v)
        // spawn many tasks if v is large enough
    {
        if (v.size()<10000) return std::accumulate(v.begin(),v.end(),0.0);
        auto f0 {async(Accum{&v[0],&v[v.size()/4],0.0})};
        auto f1 {async(Accum{&v[v.size()/4],&v[v.size()/2],0.0})};
        auto f2 {async(Accum{&v[v.size()/2],&v[v.size()*3/4],0.0})};
        auto f3 {async(Accum{&v[v.size()*3/4],&v[v.size()],0.0})};
        return f0.get()+f1.get()+f2.get()+f3.get();
    }
```
This is a very simple-minded use of concurrency (note the “magic number”), but note the absence of explicit threads, locks, buffers, etc. The type of the f-variables are determined by the return type of the standard-library function async() which is a future. If necessary, get() on a future waits for a thread to finish. Here, it is async()’s job to spawn threads as needed and the future’s job to join() the threads appropriately. “Simple” is the most important aspect of the async()/future design; futures can also be used with threads in general, but don’t even think of using async() to launch tasks that do I/O, manipulate mutexes, or in other ways interact with other tasks. The idea behind async() is the same as the idea behind the range-for statement: Provide a simple way to handle the simplest, rather common, case and leave the more complex examples to the fully general mechanism.

An async() can be requested to launch in a new thread, in any thread but the caller’s, or to launch in a different thread only if async() “thinks” that it is a good idea. The latter is the simplest from the user’s perspective and potentially the most efficient (for simple tasks only).


But what about errors? What if a task throws an exception? If a task throws an exception and doesn’t catch it itself std::terminate() is called. That typically means that the program finishes. We usually try rather hard to avoid that. A std::future can transmit an exception to the parent/calling thread; that’s one reason to like futures. Otherwise, return some sort of error code.

### virtual simulation using function pointer

```c++
#include <iostream>

// Forward declaration of Base class
class Base;

// Function pointer type for the Print function using the 'using' keyword
using PrintFunction = void (*)(const Base*);

// Base class
class Base {
public:

    Base()
    {
       printFunction = [](const Base*) { 
           std::cout << "Base class" << std::endl; 
       }; 
    }
    // Constructor to initialize the function pointer
    Base(PrintFunction printFunc) : printFunction(printFunc) {}

    // Function to call the Print function through the function pointer
    void Print() const {
        printFunction(this);
    }

private:
    // Function pointer to hold the address of the Print function
    PrintFunction printFunction;
};

// Derived class
class Derived : public Base {
public:
    // Constructor to initialize the base class with the derived class's Print function
    Derived() : Base(&Derived::PrintFunctionImpl) {}

private:
    // Implementation of the Print function for Derived class
    static void PrintFunctionImpl(const Base* base) {
        std::cout << "Derived class" << std::endl;
    }
};

int main() {
    // Create objects of Base and Derived
    Base base;
    Derived derived;

    // Call Print function for both objects
    base.Print();       // Outputs: Base class
    derived.Print();    // Outputs: Derived class

    // Demonstrate polymorphism with a Base* pointing to a Derived object
    Base* polymorphicPtr = new Derived();
    polymorphicPtr->Print();   // Outputs: Derived class

    // Clean up
    delete polymorphicPtr;

    return 0;
}
```

### Using vtables

```c++
#include <iostream>
#include <string>

// Forward declaration of Base class
class Base;

// Function pointer type for the Print function using the 'using' keyword
using PrintFunction = void (*)(const Base*);

// VTable structure for Base class
struct BaseVTable {
    PrintFunction Print;
};

// Base class
class Base {
public:
    // Constructor to initialize the vtable pointer and message
    Base(const BaseVTable* vt = &Base::vtable, const std::string& msg = "Hello base")
        : vtablePtr(vt), message(msg) {}

    // Function to call the Print function through the vtable
    void Print() const {
        vtablePtr->Print(this);
    }

    // Default print function for Base class
    static void PrintFunctionImpl(const Base* base) {
        std::cout << base->message << std::endl;
    }

    // VTable instance for Base class
    static const BaseVTable vtable;

public:
    // Message variable
    std::string message;

private:
    // Pointer to the vtable
    const BaseVTable* vtablePtr;
};

// Definition of the vtable for Base class
const BaseVTable Base::vtable = { &Base::PrintFunctionImpl };

// Derived class
class Derived : public Base {
public:
    // Constructor to initialize the base class with the derived class's vtable and message
    Derived() : Base(&Derived::vtable, "Hello derived") {}

    // Implementation of the Print function for Derived class
    static void PrintFunctionImpl(const Base* base) {
        std::cout << base->message << std::endl;
    }

    // VTable instance for Derived class
    static const BaseVTable vtable;
    
    // Make the Base class a friend of the Derived class to access the message variable
    friend class Base;
};

// Definition of the vtable for Derived class
const BaseVTable Derived::vtable = { &Derived::PrintFunctionImpl };

int main() {
    // Create objects of Base and Derived
    Base base;
    Derived derived;

    // Call Print function for both objects
    base.Print();       // Outputs: Hello base
    derived.Print();    // Outputs: Hello derived

    // Demonstrate polymorphism with a Base* pointing to a Derived object
    Base* polymorphicPtr = new Derived();
    polymorphicPtr->Print();   // Outputs: Hello derived

    // Clean up
    delete polymorphicPtr;

    return 0;
}
```
