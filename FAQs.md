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

