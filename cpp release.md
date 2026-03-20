## C++ Modern Features by Version

---

### C++11 — The Big Bang (most transformative release)

**Move Semantics & Smart Pointers**
```cpp
// Move semantics — transfer ownership instead of copying
std::vector<int> a = {1, 2, 3};
std::vector<int> b = std::move(a);  // a is now empty, no copy made

// Smart pointers — no more manual delete
std::unique_ptr<int> p = std::make_unique<int>(42);  // sole owner
std::shared_ptr<int> s = std::make_shared<int>(10);  // ref counted
std::weak_ptr<int> w = s;                            // non-owning
```

**Auto & Type Inference**
```cpp
auto x = 42;                          // int
auto v = std::vector<int>{1, 2, 3};  // std::vector<int>
auto it = v.begin();                  // iterator type
```

**Lambda Expressions**
```cpp
auto add = [](int a, int b) { return a + b; };
cout << add(3, 4);  // 7

// Capture variables
int factor = 3;
auto multiply = [factor](int x) { return x * factor; };

// Capture by reference
auto increment = [&factor]() { factor++; };
```

**Range-based for loop**
```cpp
std::vector<int> nums = {1, 2, 3, 4};
for (auto& n : nums) {
    n *= 2;
}
```

**nullptr**
```cpp
// Before C++11
int* p = NULL;   // NULL is just 0, ambiguous

// C++11
int* p = nullptr;  // type-safe null pointer
```

**Variadic Templates**
```cpp
template<typename... Args>
void print(Args... args) {
    (std::cout << ... << args);  // prints all args
}
print(1, "hello", 3.14);  // 1hello3.14
```

**initializer_list**
```cpp
std::vector<int> v = {1, 2, 3, 4, 5};  // brace initialization
std::map<std::string, int> m = {{"a", 1}, {"b", 2}};
```

**Threading support**
```cpp
#include <thread>
#include <mutex>

std::mutex mtx;
void worker(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Thread " << id << "\n";
}

std::thread t1(worker, 1);
std::thread t2(worker, 2);
t1.join();
t2.join();
```

**`enum class` (scoped enums)**
```cpp
// Old enum — pollutes namespace
enum Color { RED, GREEN, BLUE };  // RED is global

// C++11 scoped enum
enum class Direction { NORTH, SOUTH, EAST, WEST };
Direction d = Direction::NORTH;  // must qualify
```

**`constexpr`**
```cpp
constexpr int square(int x) { return x * x; }
constexpr int val = square(5);  // computed at compile time
```

**`static_assert`**
```cpp
static_assert(sizeof(int) == 4, "int must be 4 bytes");  // compile-time check
```

---

### C++14 — Refinements

```cpp
// Generic lambdas
auto add = [](auto a, auto b) { return a + b; };
add(1, 2);        // int
add(1.5, 2.5);    // double

// make_unique (missing from C++11!)
auto p = std::make_unique<int>(42);

// Return type deduction
auto multiply(int a, int b) {  // compiler deduces return type
    return a * b;
}

// Binary literals + digit separators
int x = 0b1010'1010;   // binary
int y = 1'000'000;     // readable million
```

---

### C++17 — Productivity Boost

**Structured Bindings**
```cpp
std::map<std::string, int> scores = {{"Alice", 95}, {"Bob", 87}};

for (auto& [name, score] : scores) {  // unpack key-value
    std::cout << name << ": " << score << "\n";
}

// Works with tuples too
auto [x, y, z] = std::make_tuple(1, 2.0, "hi");
```

**`if` / `switch` with initializer**
```cpp
if (auto it = map.find("key"); it != map.end()) {
    std::cout << it->second;
}  // 'it' not accessible outside if block
```

**`std::optional`**
```cpp
std::optional<std::string> find_user(int id) {
    if (id == 1) return "Alice";
    return std::nullopt;  // no value
}

auto user = find_user(1);
if (user.has_value()) {
    std::cout << user.value();
}
```

**`std::variant` (type-safe union)**
```cpp
std::variant<int, float, std::string> v;
v = 42;
v = "hello";
std::cout << std::get<std::string>(v);  // "hello"
```

**`std::filesystem`**
```cpp
#include <filesystem>
namespace fs = std::filesystem;

fs::path p = "/home/user/docs";
for (auto& entry : fs::directory_iterator(p)) {
    std::cout << entry.path() << "\n";
}
```

**Fold expressions**
```cpp
template<typename... Args>
auto sum(Args... args) {
    return (args + ...);  // fold over +
}
sum(1, 2, 3, 4);  // 10
```

---

### C++20 — The Second Big Bang

**Concepts (constrain templates)**
```cpp
template<typename T>
concept Numeric = std::is_arithmetic_v<T>;

template<Numeric T>
T add(T a, T b) { return a + b; }

add(1, 2);       // ✅ int is Numeric
add("a", "b");   // ❌ compile error — string not Numeric
```

**Ranges**
```cpp
#include <ranges>
#include <algorithm>

std::vector<int> nums = {1, 2, 3, 4, 5, 6};

// Pipeline style — filter evens, square them
auto result = nums
    | std::views::filter([](int n) { return n % 2 == 0; })
    | std::views::transform([](int n) { return n * n; });

// result: 4, 16, 36
```

**Coroutines**
```cpp
#include <coroutine>
#include <generator>  // C++23 but concept is C++20

std::generator<int> fibonacci() {
    int a = 0, b = 1;
    while (true) {
        co_yield a;         // suspend and return value
        std::tie(a, b) = {b, a + b};
    }
}

for (int n : fibonacci() | std::views::take(8)) {
    std::cout << n << " ";  // 0 1 1 2 3 5 8 13
}
```

**Modules (replaces `#include`)**
```cpp
// math.ixx (module file)
export module math;
export int square(int x) { return x * x; }

// main.cpp
import math;
int main() {
    std::cout << square(5);  // 25
}
```

**`std::span` (non-owning view)**
```cpp
void print(std::span<int> data) {  // works with any contiguous container
    for (int x : data) std::cout << x << " ";
}

std::vector<int> v = {1, 2, 3};
int arr[] = {4, 5, 6};
print(v);    // ✅
print(arr);  // ✅
```

**Three-way comparison (`<=>`)**
```cpp
struct Point {
    int x, y;
    auto operator<=>(const Point&) const = default;  // generates all 6 comparisons
};

Point a{1, 2}, b{3, 4};
bool less = a < b;   // ✅ auto-generated
bool eq   = a == b;  // ✅ auto-generated
```

---

### C++23 — Latest

```cpp
// std::print (finally! proper print)
std::print("Hello, {}!\n", "world");   // like Python's print
std::println("Value: {}", 42);         // with newline

// std::expected (better error handling than exceptions)
std::expected<int, std::string> divide(int a, int b) {
    if (b == 0) return std::unexpected("division by zero");
    return a / b;
}

auto result = divide(10, 0);
if (!result) std::cout << result.error();  // "division by zero"

// std::generator (official coroutine generator)
std::generator<int> range(int start, int end) {
    for (int i = start; i < end; i++)
        co_yield i;
}
```

---

### Quick Reference

| Version | Headline Features |
|---|---|
| C++11 | Move semantics, lambdas, smart pointers, threads, `auto`, `nullptr` |
| C++14 | Generic lambdas, `make_unique`, return type deduction |
| C++17 | Structured bindings, `optional`, `variant`, `filesystem`, `if init` |
| C++20 | Concepts, ranges, coroutines, modules, `span`, `<=>` |
| C++23 | `std::print`, `std::expected`, `std::generator` |
