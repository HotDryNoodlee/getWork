

## lock_guard, unique_lock, shared_lock, 和 scoped_lock

`lock_guard`, `unique_lock`, `shared_lock`, 和 `scoped_lock` 是C++标准库中用于管理互斥锁的RAII（Resource Acquisition Is Initialization）类，帮助开发者更好地控制多线程环境下对共享资源的访问。以下是它们的详细介绍和使用场景：

### 1. `lock_guard`
- **定义**：`lock_guard` 是一个简单的RAII类型的锁管理器。在构造时自动锁定互斥体，在析构时自动解锁互斥体。
- **特性**：
  - 构造时自动锁定，析构时自动解锁。
  - 不允许显式的解锁或重新锁定。
  - 非常适合用于简单的临界区保护。

- **用法**：

```cpp
std::mutex mtx;
{
    std::lock_guard<std::mutex> lock(mtx);  // 自动加锁
    // 临界区
}  // 作用域结束，自动解锁
```

### 2. `unique_lock`
- **定义**：`unique_lock` 是一种更灵活的锁管理器。它允许手动锁定和解锁，支持延迟锁定和条件变量等高级特性。
- **特性**：
  - 支持延迟锁定、手动解锁和重新锁定。
  - 适用于需要复杂锁管理的场景，例如与条件变量配合使用时。
  - 可以在构造时选择是否立即锁定互斥体。

- **用法**：

```cpp
std::mutex mtx;
{
    std::unique_lock<std::mutex> lock(mtx);  // 自动加锁
    // 你可以手动解锁和重新加锁
    lock.unlock();
    // 非临界区操作
    lock.lock();
    // 临界区
}  // 作用域结束，自动解锁
```

### 3. `shared_lock`
- **定义**：`shared_lock` 是用于共享锁（`std::shared_mutex`）的RAII类型锁管理器。多个线程可以同时持有共享锁来进行只读操作。
- **特性**：
  - 允许多个线程同时持有同一共享锁，以进行并发的读操作。
  - 只适用于 `std::shared_mutex`，适合读写锁场景下的读锁。

- **用法**：

```cpp
std::shared_mutex sharedMtx;
{
    std::shared_lock<std::shared_mutex> lock(sharedMtx);  // 获取共享锁
    // 只读操作
}  // 作用域结束，自动解锁
```

### 4. `scoped_lock`
- **定义**：`scoped_lock` 是C++17引入的RAII类型的锁管理器，设计用于同时锁定多个互斥体，从而简化并发编程中的死锁管理。
- **特性**：
  - 支持同时锁定多个互斥体，保证锁的顺序一致以防止死锁。
  - 适用于需要在同一作用域内锁定多个互斥体的场景。
  - 在构造时锁定互斥体，在析构时解锁。
  
- **用法**：

```cpp
std::mutex mtx1, mtx2;
{
    std::scoped_lock lock(mtx1, mtx2);  // 同时锁定多个互斥体
    // 临界区
}  // 作用域结束，自动解锁
```

### 总结
- **`lock_guard`**: 适用于简单的临界区保护，构造即锁定，析构即解锁。
- **`unique_lock`**: 更灵活，支持延迟锁定、手动解锁和重新锁定，适用于更复杂的锁管理场景。
- **`shared_lock`**: 用于共享锁，支持并发读操作，适合读者-写者场景。
- **`scoped_lock`**: 用于同时锁定多个互斥体，防止死锁，适合需要锁定多个资源的场景。

这些工具提供了不同级别的锁定控制，适用于多种并发编程需求。

## mutex
在C++标准库中，`mutex` 是用于线程间同步的基本工具，它们确保多个线程在访问共享资源时能够正确地进行互斥控制。C++标准库提供了几种不同类型的 `mutex`，它们各自适用于不同的并发场景。以下是几种常见的 `mutex` 及其用途：

### 1. `std::mutex`
- **定义**：这是最基础的互斥体类型，用于保护共享数据免受并发访问。只有一个线程可以同时锁定 `std::mutex`，其他试图锁定的线程会被阻塞，直到互斥体被解锁。
- **特性**：
  - 不支持递归加锁（即同一个线程不能多次锁定同一个 `std::mutex`）。
  - 适用于一般的互斥控制。

- **用法**：

```cpp
std::mutex mtx;
{
    mtx.lock();
    // 临界区
    mtx.unlock();
}
```

### 2. `std::timed_mutex`
- **定义**：`std::timed_mutex` 是 `std::mutex` 的一个扩展版本，允许线程在尝试锁定互斥体时指定一个超时时间。如果在超时时间内没有获取到锁，则返回 `false`。
- **特性**：
  - 支持 `try_lock_for` 和 `try_lock_until` 方法，分别用于指定相对时间和绝对时间的尝试锁定。

- **用法**：

```cpp
std::timed_mutex tmtx;
if (tmtx.try_lock_for(std::chrono::milliseconds(100))) {
    // 成功获取锁，临界区
    tmtx.unlock();
} else {
    // 超时未获取到锁
}
```

### 3. `std::recursive_mutex`
- **定义**：`std::recursive_mutex` 允许同一个线程多次锁定同一个互斥体，并且必须对应数量的解锁操作才能真正释放锁。适用于递归函数中可能多次锁定同一个互斥体的场景。
- **特性**：
  - 同一线程可以多次锁定互斥体，但解锁次数必须与加锁次数相同。
  - 适用于需要递归加锁的场景。

- **用法**：

```cpp
std::recursive_mutex recMtx;
void recursiveFunction(int n) {
    recMtx.lock();
    if (n > 0) {
        recursiveFunction(n - 1);
    }
    recMtx.unlock();
}
```

### 4. `std::recursive_timed_mutex`
- **定义**：`std::recursive_timed_mutex` 是 `std::recursive_mutex` 的扩展版本，支持超时锁定功能，即可以指定一个时间段内尝试递归加锁。
- **特性**：
  - 结合了递归互斥体和定时互斥体的特性，既支持递归加锁，又支持超时锁定。

- **用法**：

```cpp
std::recursive_timed_mutex rtmMtx;
if (rtmMtx.try_lock_for(std::chrono::milliseconds(100))) {
    // 成功获取锁，临界区
    rtmMtx.unlock();
} else {
    // 超时未获取到锁
}
```

### 5. `std::shared_mutex` (C++17)
- **定义**：`std::shared_mutex` 支持多线程共享锁（读锁）和独占锁（写锁）。多个线程可以同时持有共享锁，但只有一个线程可以持有独占锁。
- **特性**：
  - 适用于读多写少的场景，可以提高并发效率。
  - 支持多线程同时读取数据，但写线程必须独占锁定。

- **用法**：

```cpp
std::shared_mutex sharedMtx;
{
    std::shared_lock<std::shared_mutex> lock(sharedMtx);  // 获取共享锁，适合读操作
    // 只读操作
}
{
    std::unique_lock<std::shared_mutex> lock(sharedMtx);  // 获取独占锁，适合写操作
    // 写操作
}
```

### 6. `std::shared_timed_mutex` (C++14)
- **定义**：`std::shared_timed_mutex` 是 `std::shared_mutex` 的扩展版本，增加了超时功能，即可以指定时间段内尝试获取共享锁或独占锁。
- **特性**：
  - 结合了共享锁和定时锁的特性，允许线程在特定时间段内尝试获取锁。

- **用法**：

```cpp
std::shared_timed_mutex stmMtx;
if (stmMtx.try_lock_for(std::chrono::milliseconds(100))) {
    // 获取独占锁，适合写操作
    stmMtx.unlock();
}
if (stmMtx.try_lock_shared_for(std::chrono::milliseconds(100))) {
    // 获取共享锁，适合读操作
    stmMtx.unlock_shared();
}
```

### 总结
- **`std::mutex`**: 基础互斥体，适合一般的互斥控制。
- **`std::timed_mutex`**: 支持超时锁定，适合需要定时尝试获取锁的场景。
- **`std::recursive_mutex`**: 支持递归加锁，适合递归函数或需要多次加锁的场景。
- **`std::recursive_timed_mutex`**: 支持递归和超时锁定，适合更复杂的递归加锁场景。
- **`std::shared_mutex`**: 支持共享锁和独占锁，适合读多写少的场景。
- **`std::shared_timed_mutex`**: 支持共享锁、独占锁和超时功能，适合需要超时控制的共享锁场景。

这些 `mutex` 工具各自具有不同的特性，可以根据具体的并发需求选择合适的类型，以确保线程安全和高效的资源管理。