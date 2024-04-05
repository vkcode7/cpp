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

