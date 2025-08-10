## using keyword and function pointers

```c++
#include <iostream>

// Define function pointer type
typedef const char* (*PFN)(int);
//OR use USING keyword as below
using PFN2 = const char* (*)(int);

// Define a function that matches the signature of the function pointer
const char* ErrorFunction(int errorCode) {
    if (errorCode == 0)
        return "No Error";
    else
        return "Unknown Error";
}

int main() {
    // Assign the ErrorFunction to the function pointer
    PFN pfn = ErrorFunction;
    PFN2 pfn2 = ErrorFunction;

    // Call ShowError passing the function pointer
    auto message = pfn(10);
	  std::cout << std::endl << message << std::endl;

    message = pfn2(0);
	  std::cout << std::endl << message << std::endl;
    return 0;
}
```

## 2D Arrays
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

### Union:
Key points about unions:

- Memory sharing: All members occupy the same memory location
- Size: Union size = size of largest member
- Only one member valid: Writing to one member invalidates others

Use cases:

- Memory-constrained environments
- Type reinterpretation/conversion
- Hardware register mapping
- Variant data types

Important notes:

- Undefined behavior: Reading from a member you didn't write to
- No constructors/destructors: For non-trivial types in C++98/03
- Tagged unions: Use enum to track which member is active
- Modern alternative: Consider std::variant in C++17 for type-safe unions

```c++
#include <iostream>
#include <string>
using namespace std;

// EXAMPLE 1: Basic Union - Memory sharing
union BasicUnion {
    int i;
    float f;
    char c;
};

// EXAMPLE 2: Union for type conversion/interpretation
union Converter {
    int asInt;
    float asFloat;
    char bytes[4];
};

// EXAMPLE 3: Tagged Union (Discriminated Union)
enum DataType { INT_TYPE, FLOAT_TYPE, CHAR_TYPE };

struct TaggedUnion {
    DataType type;
    union {
        int i;
        float f;
        char c;
    } data;
    
    // Constructor for int
    TaggedUnion(int value) : type(INT_TYPE) { data.i = value; }
    // Constructor for float  
    TaggedUnion(float value) : type(FLOAT_TYPE) { data.f = value; }
    // Constructor for char
    TaggedUnion(char value) : type(CHAR_TYPE) { data.c = value; }
    
    void print() {
        switch(type) {
            case INT_TYPE: cout << "Int: " << data.i << endl; break;
            case FLOAT_TYPE: cout << "Float: " << data.f << endl; break;
            case CHAR_TYPE: cout << "Char: " << data.c << endl; break;
        }
    }
};

// EXAMPLE 4: Union with struct for bit manipulation
union IPv4Address {
    uint32_t address;
    struct {
        uint8_t octet1;
        uint8_t octet2;
        uint8_t octet3;
        uint8_t octet4;
    } octets;
};

int main() {
    cout << "=== EXAMPLE 1: Basic Union ===\n";
    BasicUnion u1;
    
    u1.i = 65;
    cout << "Set as int 65: " << u1.i << endl;
    cout << "Read as char: " << u1.c << endl;  // 'A' (ASCII 65)
    
    u1.f = 3.14f;
    cout << "Set as float 3.14: " << u1.f << endl;
    cout << "Read as int: " << u1.i << endl;  // Garbage - wrong interpretation
    
    cout << "\nUnion size: " << sizeof(BasicUnion) << " bytes\n";
    cout << "(Size of largest member: int/float = 4 bytes)\n\n";
    
    cout << "=== EXAMPLE 2: Type Conversion ===\n";
    Converter conv;
    conv.asFloat = 3.14159f;
    
    cout << "Float value: " << conv.asFloat << endl;
    cout << "As int (reinterpreted): " << conv.asInt << endl;
    cout << "Byte representation: ";
    for(int i = 0; i < 4; i++) {
        printf("%02X ", (unsigned char)conv.bytes[i]);
    }
    cout << endl << endl;
    
    cout << "=== EXAMPLE 3: Tagged Union ===\n";
    TaggedUnion t1(42);
    TaggedUnion t2(3.14f);
    TaggedUnion t3('A');
    
    t1.print();
    t2.print();
    t3.print();
    cout << endl;
    
    cout << "=== EXAMPLE 4: IP Address Union ===\n";
    IPv4Address ip;
    ip.address = 0xC0A80001;  // 192.168.0.1 in hex
    
    cout << "IP Address: " << (int)ip.octets.octet4 << "."
         << (int)ip.octets.octet3 << "."
         << (int)ip.octets.octet2 << "."
         << (int)ip.octets.octet1 << endl;
    
    cout << "As 32-bit int: 0x" << hex << ip.address << dec << endl;
    
    return 0;
}
```
