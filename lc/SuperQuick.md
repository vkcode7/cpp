## c++
```c++
    std::multiset<int, std::greater<int>> s{8, 2, 0, 9, 5};
    //prints 9 8 5 3 3 2 1 0 
```


### printing dynamic array
```cpp
    template<typename T, size_t N>
    void printArray(T (&arr)[N]) {
        for (size_t i = 0; i < N; ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }

    // Option 1: Traditional approach
    void printArray(int* arr, size_t size);

    // Option 2: Use std::vector
    std::vector<int> arr(10);
    // Works with range-based loops and algorithms

    // Option 3: Wrapper struct
    struct DynamicArray {
        int* data;
        size_t size;
    };
```

### 2D Arrays
```cpp
    int rows = 2;
    int cols = 3;
    
    int ** pM = new int*[rows];
    for(auto i =0; i < cols; i++) {
        pM[i] = new int[cols];
        for(auto j=0; j < cols; j++)
            pM[i][j] = i * j + j;
    }
    cout << endl;
    for(auto i =0; i < cols; i++) {
        for(auto j=0; j < cols; j++)
            cout << pM[i][j] << ", ";
        cout<<endl;
    }
    
        // Deallocate memory for the 2D array
    for (int i = 0; i < rows; ++i) {
        delete[] pM[i];
    }
    
    delete[] pM;
```

```cpp
// Define a type alias for a function pointer
using FuncPtr = void(*)(int);

```

## Tuple ands tie
It's often used as a return type for functions that need to return multiple values, or in algorithms that need to operate on collections of heterogeneous data.

```cpp
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

## function objects: function<R(T1,T2)>
```cpp
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

## Demonstrate Placement New
There are many uses of placement new. The simplest use is to place an object at a particular location in memory. This is done by supplying the place as a pointer parameter to the new part of a new expression.

You are also solely responsible for destructing the placed object. This is done by explicitly calling the destructor [f->~Fred();].

```cpp
    void demonstrateHeapPlacementNew() {
        cout << "\n=== PLACEMENT NEW WITH HEAP MEMORY ===\n";
        
        // Allocate raw memory on heap
        void* rawMemory = malloc(sizeof(MyClass));
        cout << "Raw memory allocated at: " << rawMemory << endl;
        
        // Use placement new to construct object in that memory
        MyClass* obj3 = new (rawMemory) MyClass(200, "HeapPlacement");
        
        obj3->display();
        
        // Manual destructor call
        obj3->~MyClass();
        
        // Free the raw memory
        free(rawMemory);
        cout << "Raw memory freed\n";
    }
```

## PREFIX VS POSTFIX (via dummy param)
```CPP
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

# Friend and Op Overloading
Another good use of friend functions are the binary infix arithmetic operators. E.g., aComplex + aComplex should be defined as a friend rather than a member if you want to allow aFloat + aComplex as well (member functions don’t allow promotion of the left hand argument, since that would change the class of the object that is the recipient of the member function invocation).

### What’s the difference between how virtual and non-virtual member functions are called?
Non-virtual member functions are resolved statically. That is, the member function is selected statically (at compile-time) based on the type of the pointer (or reference) to the object.

In contrast, virtual member functions are resolved dynamically (at run-time). That is, the member function is selected dynamically (at run-time) based on the type of the object, not the type of the pointer/reference to that object. This is called “dynamic binding.”

### final specifier (since C++11) - How can I set up my class so it won’t be inherited from?
Specifies that a virtual function cannot be overridden in a derived class, or that a class cannot be derived from.

```cpp
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
