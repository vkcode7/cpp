Here's a clear and complete guide on **how to create and run tasks using `std::thread`** in modern C++.

import pandas as pd
import numpy as np
from sklearn.cluster import KMeans
from sklearn.metrics import silhouette_score, completeness_score


def cluster_customers(data_train, data_test):
    """
    Implements the cluster_customers function as specified in the Codility task.
    Returns the exact dictionary required by the task.
    """
    # Identify the 12 feature columns (account_1 to account_12)
    feature_cols = [f'account_{i}' for i in range(1, 13)]

    # Step 1: Standardize the 12 variables
    # Compute mean and std (pandas default ddof=1) from data_train only
    train_mean = data_train[feature_cols].mean()
    train_std = data_train[feature_cols].std()

    # Standardize train features and round to 3 decimal places
    sd_train_features = (data_train[feature_cols] - train_mean) / train_std
    sd_train_features = sd_train_features.round(3)

    # Build sd_train: keep 'cluster' column unchanged, replace features
    sd_train = data_train.copy()
    sd_train[feature_cols] = sd_train_features

    # Standardize test features using the same train statistics and round
    sd_test_features = (data_test[feature_cols] - train_mean) / train_std
    sd_test_features = sd_test_features.round(3)

    # Build sd_test: keep 'cluster' column unchanged, replace features
    sd_test = data_test.copy()
    sd_test[feature_cols] = sd_test_features

    # Step 2: Find optimal number of clusters (elbow method with WCSS)
    wcss = []
    for i in range(2, 11):
        kmeans_i = KMeans(
            n_clusters=i,
            init="k-means++",
            max_iter=50,
            n_init=10,
            random_state=0,
            tol=0.05
        )
        kmeans_i.fit(sd_train[feature_cols])
        wcss.append(kmeans_i.inertia_)

    # Find opt_cluster: smallest k where wcss[k] - wcss[k+1] < 20
    # (default to 10 if the decrease never drops below 20)
    opt_cluster = 10
    for idx in range(len(wcss) - 1):
        diff = wcss[idx] - wcss[idx + 1]
        if diff < 20:
            opt_cluster = idx + 2
            break

    # Step 3: Build the two required KMeans models with identical parameters
    # Optimal model
    kmeans_opt = KMeans(
        n_clusters=opt_cluster,
        init="k-means++",
        max_iter=50,
        n_init=10,
        random_state=0,
        tol=0.05
    )
    kmeans_opt.fit(sd_train[feature_cols])

    # 4-cluster model (previous manual clusters)
    kmeans_4 = KMeans(
        n_clusters=4,
        init="k-means++",
        max_iter=50,
        n_init=10,
        random_state=0,
        tol=0.05
    )
    kmeans_4.fit(sd_train[feature_cols])

    # Silhouette score (on sd_train with optimal clustering)
    silhouette = silhouette_score(sd_train[feature_cols], kmeans_opt.labels_)

    # Completeness scores (tuple)
    # Train completeness
    completeness_train = completeness_score(sd_train["cluster"], kmeans_4.labels_)
    # Test completeness
    pred_test_4 = kmeans_4.predict(sd_test[feature_cols])
    completeness_test = completeness_score(sd_test["cluster"], pred_test_4)
    completeness = (completeness_train, completeness_test)

    # Predicted labels on sd_test using optimal model
    labels_predicted = list(kmeans_opt.predict(sd_test[feature_cols]))

    # max_opt: cluster indices sorted by descending Euclidean distance
    # from the first observation in sd_test to each cluster center
    first_obs = sd_test[feature_cols].iloc[0].values
    centers = kmeans_opt.cluster_centers_
    distances = np.linalg.norm(centers - first_obs, axis=1)
    # Sort cluster indices (0 to opt_cluster-1) by descending distance
    max_opt = list(np.argsort(distances)[::-1])

    # Return the exact dictionary required by the task
    return {
        "sd_train": sd_train,
        "sd_test": sd_test,
        "wcss": wcss,
        "kmeans_opt": kmeans_opt,
        "silhouette": silhouette,
        "completeness": completeness,
        "labels_predicted": labels_predicted,
        "max_opt": max_opt
    }

### 1. Basic Task Creation with `std::thread`

```cpp
#include <iostream>
#include <thread>

void task() {
    std::cout << "Task running in thread: " 
              << std::this_thread::get_id() << '\n';
}

int main() {
    std::thread t(task);        // Create and start the thread
    
    std::cout << "Main thread: " << std::this_thread::get_id() << '\n';

    t.join();                   // Wait for the thread to finish
    return 0;
}
```

### 2. Most Common & Recommended Ways (C++11 and later)

#### a) Free Function
```cpp
void doWork(int id, std::string name) {
    std::cout << "Worker " << id << " (" << name << ") running\n";
}

int main() {
    std::thread t1(doWork, 1, "Alice");
    std::thread t2(doWork, 2, "Bob");

    t1.join();
    t2.join();
}
```

#### b) Lambda (most popular for simple tasks)
```cpp
int main() {
    int value = 42;

    std::thread t([value]() {
        std::cout << "Task received value: " << value << '\n';
        // Do heavy work here...
    });

    t.join();
}
```

#### c) Member Function
```cpp
class Worker {
public:
    void run(int taskId) {
        std::cout << "Worker running task " << taskId << '\n';
    }
};

int main() {
    Worker w;

    std::thread t(&Worker::run, &w, 100);   // pass object + arguments
    // or with smart pointer: std::thread t(&Worker::run, std::ref(w), 100);

    t.join();
}
```

#### d) Using `std::bind` (less common now)
```cpp
#include <functional>

void process(int a, double b) { ... }

int main() {
    std::thread t(std::bind(process, 10, 3.14));
    t.join();
}
```

### 3. Passing Arguments by Reference

Be careful! By default, arguments are **copied**.

```cpp
void increment(int& x) {
    ++x;
}

int main() {
    int counter = 0;

    std::thread t(increment, std::ref(counter));   // use std::ref()

    t.join();
    std::cout << "Counter = " << counter << '\n';  // 1
}
```

### 4. Modern & Recommended Pattern: Task + `std::future` (C++11+)

For real "tasks" (fire-and-forget or get result back), people often combine `std::thread` with `std::promise`/`std::future`, or better, use `std::async`:

```cpp
#include <future>

int compute(int x) {
    return x * x;
}

int main() {
    // High-level way (recommended)
    auto future = std::async(std::launch::async, compute, 7);
    
    std::cout << "Result: " << future.get() << '\n';
}
```

But if you specifically want to use raw `std::thread`:

```cpp
#include <future>

int main() {
    std::promise<int> promise;
    std::future<int>  future = promise.get_future();

    std::thread t([](std::promise<int> p, int val) {
        p.set_value(val * val);
    }, std::move(promise), 8);

    std::cout << "Result: " << future.get() << '\n';

    t.join();
}
```

### 5. Important Rules

- Always call **`join()`** or **`detach()`** on a `std::thread`, otherwise `std::terminate()` is called in destructor.
- Prefer **`join()`** in most cases.
- Use **`detach()`** only when you truly want fire-and-forget (rare).
- Capture variables carefully in lambdas (use `std::ref` or copy).
- For many tasks, consider using **thread pools** instead of creating/destroying threads repeatedly.

### 6. Simple Thread Pool Example (C++17+ style)

Would you like me to show you a clean, reusable task-based thread pool using `std::thread`, `std::queue`, and `std::condition_variable`?

Just say the word and I'll give you a production-ready version.

Would you like:
1. More examples (detached threads, exception handling in threads, etc.)
2. A full thread pool implementation
3. Comparison between `std::thread` vs `std::async` vs executors (C++23+)

## Comparison between `std::thread` vs `std::async` vs executors (C++23+)

Here's a clear, up-to-date comparison between **`std::thread`** and **`std::async`** in modern C++ (C++11 through C++23/26 as of 2026).

### Quick Overview

- **`std::thread`**: Low-level thread management. You create and control actual OS threads directly.
- **`std::async`**: High-level **task-based** abstraction. You launch a *task* (function/callable), and it returns a **`std::future`** for the result. The implementation may or may not create a new thread.

### Detailed Comparison Table

| Aspect                        | `std::thread`                                      | `std::async`                                                                 |
|-------------------------------|----------------------------------------------------|------------------------------------------------------------------------------|
| **Abstraction Level**        | Low-level (thread-centric)                        | Higher-level (task-centric)                                                 |
| **Return Value**             | None (use shared variables, mutex, or `std::promise`) | Built-in via `std::future<T>`                                               |
| **Exception Handling**       | Exceptions propagate to `std::terminate()` if not caught inside the thread | Exceptions are automatically stored in the future and rethrown on `.get()` |
| **Thread Creation**          | Always creates a new thread (unless you detach/join carefully) | Depends on launch policy:<br>• `std::launch::async` → usually new thread<br>• `std::launch::deferred` → runs lazily on `.get()` in calling thread<br>• Default (no policy) → implementation-defined (often async + deferred fallback) |
| **Lifetime Management**      | You **must** call `join()` or `detach()` or program terminates | Automatic: the future's destructor blocks if needed (for `async` policy)   |
| **Overhead**                 | Direct OS thread cost (stack, context switch, etc.) | Similar or higher in naive implementations (some std libs create new thread every time) |
| **Thread Pooling**           | You control it (or implement your own pool)       | **Not guaranteed** — many implementations do **not** use a thread pool (this is a common criticism) |
| **Fine-grained Tasks**       | Good (if you use a custom pool)                   | Poor — creating many short tasks can be expensive                           |
| **Code Simplicity**          | More boilerplate (especially for results + exceptions) | Very clean and concise                                                      |
| **Control**                  | Full control (affinity, priority, etc.)           | Limited control                                                             |
| **When Task Finishes**       | You decide (join/detach)                          | `.get()` or future destruction                                              |

### Code Examples Side-by-Side

**Using `std::thread` (manual):**

```cpp
#include <thread>
#include <future>   // for promise/future

int compute(int x) {
    if (x == 0) throw std::runtime_error("zero!");
    return x * x;
}

int main() {
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();

    std::thread t([&prom, x=7]() {
        try {
            prom.set_value(compute(x));
        } catch (...) {
            prom.set_exception(std::current_exception());
        }
    });

    // Do other work...

    try {
        std::cout << "Result: " << fut.get() << '\n';
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << '\n';
    }

    t.join();
}
```

**Using `std::async` (much cleaner):**

```cpp
#include <future>

int main() {
    auto fut = std::async(std::launch::async, compute, 7);

    // Do other work...

    try {
        std::cout << "Result: " << fut.get() << '\n';   // blocks if not ready
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << '\n';
    }
}
```

### When to Use Which?

**Use `std::thread` when you need:**
- Full control over threads (scheduling, affinity, custom thread pools).
- Long-running background workers or server threads.
- A custom thread pool for high-frequency or fine-grained tasks.
- Maximum performance with many short tasks (combined with a pool).
- Low-level synchronization patterns.

**Use `std::async` when you need:**
- Simple "fire a task and get result later" (one-off computations).
- Easy return values and automatic exception propagation.
- Cleaner, less error-prone code for occasional parallelism.
- Long-running computations or I/O-bound tasks in small-to-medium programs.

**Recommendation from many experts (still valid in 2026):**
- For most everyday use → Prefer **`std::async(std::launch::async, ...)`** over raw `std::thread`.
- For performance-critical or many tasks → Build or use a **thread pool** (based on `std::thread` + queue + condition_variable) or third-party libraries (TBB, Taskflow, dispenso, etc.).
- Never rely on the **default launch policy** of `std::async` (it can run deferred).

### Modern Alternatives (C++20/23/26)

- **Parallel Algorithms** (`<execution>`): `std::execution::par` for data-parallel loops.
- **Coroutines** (C++20): Great for I/O-heavy async code (co_await).
- **Executors / `std::execution`** (C++26 proposal, with reference impls like stdexec): The future direction for composable, efficient task graphs and schedulers.

Would you like me to show:
- A complete reusable thread pool example using `std::thread`?
- How exception handling differs in more detail?
- Performance comparison tips or benchmarks?
- How to combine both (`std::async` + custom pool)?

Just tell me what you'd like to dive into next!


## Exception handling in threads
Here's a clear and practical guide to **exception handling in C++ threads** (updated for C++11–C++26 as of 2026).

### 1. The Core Problem with `std::thread`

Exceptions **do not propagate** across threads automatically.

- If an exception is thrown inside a `std::thread` and is **not caught inside that thread**, the program calls **`std::terminate()`** → immediate crash (no stack unwinding in other threads).
- This is by design: each thread has its own stack and exception context.

**Bad example (crashes):**

```cpp
void bad_task() {
    throw std::runtime_error("Something went wrong in thread!");
}

int main() {
    std::thread t(bad_task);
    t.join();        // Program terminates here if exception escapes
}
```

### 2. Proper Exception Handling with `std::thread`

You must **catch all exceptions inside the thread** and transport them manually.

The standard way uses **`std::promise`** + **`std::future`** + **`std::exception_ptr`**.

```cpp
#include <iostream>
#include <thread>
#include <future>
#include <exception>

void task(std::promise<int> prom) {
    try {
        // Your real work here
        if (/* error condition */) {
            throw std::runtime_error("Task failed!");
        }
        if (/* another error */) {
            throw std::logic_error("Invalid argument");
        }
        prom.set_value(42);               // Success
    }
    catch (...) {
        prom.set_exception(std::current_exception());  // Capture and store any exception
    }
}

int main() {
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();

    std::thread t(task, std::move(prom));

    try {
        int result = fut.get();           // Blocks until thread finishes
        std::cout << "Result: " << result << '\n';
    }
    catch (const std::exception& e) {
        std::cout << "Exception from thread: " << e.what() << '\n';
    }
    catch (...) {
        std::cout << "Unknown exception from thread\n";
    }

    t.join();
}
```

This is the **most robust and portable** pattern.

### 3. Cleaner Alternative: `std::async` (Recommended for Most Cases)

`std::async` handles exception propagation **automatically** via `std::future`.

```cpp
#include <future>

int compute(int x) {
    if (x < 0) throw std::invalid_argument("Negative value!");
    return x * x;
}

int main() {
    auto fut = std::async(std::launch::async, compute, -5);

    try {
        int res = fut.get();          // Exception is rethrown here automatically
        std::cout << "Result: " << res << '\n';
    }
    catch (const std::exception& e) {
        std::cout << "Caught in main: " << e.what() << '\n';
    }
}
```

**Advantages of `std::async`**:
- Much less boilerplate.
- Exceptions are stored in the future and rethrown on `.get()`.
- Works with any exception type (not just `std::exception`).

**Note**: Use `std::launch::async` explicitly if you want a real thread. The default policy is implementation-defined.

### 4. Comparison: `std::thread` vs `std::async` for Exceptions

| Feature                        | `std::thread` + `promise`                          | `std::async`                                      |
|--------------------------------|----------------------------------------------------|---------------------------------------------------|
| Exception propagation          | Manual (`set_exception`)                           | Automatic (via `future::get()`)                   |
| Code verbosity                 | High                                               | Very low                                          |
| Flexibility                    | Full control                                       | Limited (but sufficient for most tasks)           |
| Performance overhead           | Similar                                            | Similar (or slightly higher in some libs)         |
| Best for                       | Custom thread pools, long-running workers          | One-off tasks, simple parallelism                 |

**Rule of thumb in 2026**:
- Simple tasks or when you need a result/exception → **prefer `std::async`**.
- High-performance / many tasks / custom scheduling → use `std::thread` + thread pool with the promise pattern.

### 5. Advanced / Modern Tips (C++23 / C++26)

- **C++23 `std::stacktrace`**: You can capture a stack trace when throwing and store it inside a custom exception for better debugging across threads.
- Use **custom exception types** derived from `std::exception` (or `std::runtime_error`) to carry extra context.
- In thread pools: Catch once at the task wrapper level and forward via a central error queue or per-task future.
- Consider `std::expected<T, E>` (C++23) for **exception-free** error handling in performance-critical paths (avoids exception overhead entirely).

### 6. Best Practices Summary

1. Never let exceptions escape a thread → always catch inside.
2. Use `std::async` whenever possible for simplicity.
3. For raw `std::thread`, always use `std::promise`/`std::future` + `std::current_exception()`.
4. Join (or detach carefully) every thread.
5. Prefer RAII (`std::jthread` from C++20) to avoid forgetting `join()`.
6. In large systems, build a thread pool that handles exceptions centrally.

Would you like me to show you:

- A complete reusable **thread pool** with automatic exception handling?
- How to use `std::exception_ptr` directly with `std::rethrow_exception`?
- Examples with custom exceptions + `std::stacktrace` (C++23)?
- Exception handling in detached threads?

Just tell me which direction you'd like to explore next!


