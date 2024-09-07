

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


## queue
在C++标准模板库（STL）中，`queue` 是一个先进先出（FIFO，First In First Out）数据结构，底层通常是基于容器适配器实现的。`queue` 本身并不是一个独立的容器，它是基于其他标准容器如 `deque` 或 `list` 进行适配的。

### 实现原理：
1. **容器适配器（Container Adapter）：**
   - `queue` 是一个容器适配器，底层可以使用任何符合要求的顺序容器，比如 `deque`、`list` 或 `vector`。不过，默认情况下 `queue` 是基于 `deque` 实现的。`deque`（双端队列）支持在两端高效地插入和删除元素，这使得它成为实现 `queue` 的良好选择。

2. **主要操作：**
   - **入队 (`push`)：** 新元素插入到队列的末尾。
   - **出队 (`pop`)：** 删除并返回队列的第一个元素。
   - **获取队首元素 (`front`)：** 获取队列的第一个元素，但不删除它。
   - **获取队尾元素 (`back`)：** 获取队列的最后一个元素，但不删除它。

3. **核心成员变量：**
   `queue` 主要依赖底层容器来存储数据，核心成员变量通常是一个顺序容器对象，用来存储元素。

4. **时间复杂度：**
   - **插入和删除操作：** `push` 和 `pop` 操作的时间复杂度都是 O(1)，因为它们只涉及在容器的末端和开头插入和删除元素，特别是对于 `deque` 容器。
   - **访问操作：** `front` 和 `back` 也是 O(1) 操作。

### 底层实现细节（以 `deque` 为例）：
   - 当调用 `push` 操作时，队列会调用 `deque` 的 `push_back` 来将元素添加到队列的末尾。
   - 当调用 `pop` 操作时，队列会调用 `deque` 的 `pop_front` 来删除队列的第一个元素。
   - `front` 和 `back` 分别调用 `deque` 的 `front` 和 `back` 成员函数来访问元素。

### 代码示例：
```cpp
#include <iostream>
#include <queue>

int main() {
    std::queue<int> q;

    q.push(10);  // 入队
    q.push(20);
    q.push(30);

    std::cout << "队首元素: " << q.front() << std::endl;  // 输出10
    std::cout << "队尾元素: " << q.back() << std::endl;   // 输出30

    q.pop();  // 出队

    std::cout << "队首元素: " << q.front() << std::endl;  // 输出20

    return 0;
}
```

总结：`queue` 的实现依赖于底层的顺序容器，默认情况下是 `deque`，通过容器适配器对外提供一个先进先出（FIFO）的接口，实现队列的功能。

## stack

在C++标准模板库（STL）中，`stack` 是一个后进先出（LIFO，Last In First Out）数据结构。`stack` 和 `queue` 类似，它也是一个**容器适配器**，即基于其他容器来实现的容器。`stack` 的底层通常使用 `deque`、`vector` 或 `list` 来存储数据，不过默认情况下，`stack` 是基于 `deque` 实现的。

### 实现原理：
1. **容器适配器（Container Adapter）：**
   - `stack` 作为容器适配器，本质上是通过对标准顺序容器（如 `deque`、`vector` 或 `list`）的一些接口进行封装，来实现其后进先出的行为。

2. **主要操作：**
   - **入栈 (`push`)：** 新元素插入到栈的顶端。
   - **出栈 (`pop`)：** 移除栈顶的元素。
   - **获取栈顶元素 (`top`)：** 返回栈顶元素的引用。
   - **判空 (`empty`)：** 判断栈是否为空。
   - **获取栈的大小 (`size`)：** 返回栈中元素的个数。

3. **核心成员变量：**
   `stack` 依赖一个底层容器对象（如 `deque`）来存储数据。

4. **时间复杂度：**
   - **插入和删除操作：** `push` 和 `pop` 操作的时间复杂度为 O(1)，因为它们只涉及在容器的末尾插入和删除元素。
   - **访问操作：** `top` 操作也是 O(1)。

### 底层实现细节（以 `deque` 为例）：
   - `push` 操作通过调用 `deque` 的 `push_back` 来将元素插入到栈顶（即 `deque` 的末尾）。
   - `pop` 操作通过调用 `deque` 的 `pop_back` 来移除栈顶元素（即 `deque` 的末尾）。
   - `top` 操作则通过调用 `deque` 的 `back` 来获取栈顶元素。

### 代码示例：
```cpp
#include <iostream>
#include <stack>

int main() {
    std::stack<int> s;

    s.push(10);  // 入栈
    s.push(20);
    s.push(30);

    std::cout << "栈顶元素: " << s.top() << std::endl;  // 输出30

    s.pop();  // 出栈

    std::cout << "栈顶元素: " << s.top() << std::endl;  // 输出20

    std::cout << "栈的大小: " << s.size() << std::endl;  // 输出2

    return 0;
}
```

### 底层容器选择：
- **`deque`**：双端队列，支持在两端高效地插入和删除元素，是 `stack` 的默认底层实现。
- **`vector`**：动态数组，在末尾插入和删除元素的性能良好，适合栈的需求。
- **`list`**：双向链表，支持在任意位置插入和删除元素，虽然可以用来实现栈，但在大多数情况下没有 `deque` 或 `vector` 高效。

### 总结：
C++ STL 中的 `stack` 是一个基于容器适配器的后进先出数据结构，默认使用 `deque` 实现，但也可以使用其他容器如 `vector` 或 `list` 作为底层容器。


## priority_queue

## map 
在C++标准模板库（STL）中，`map` 是一种**关联容器**，它以**键值对**的形式存储数据，其中每个键唯一对应一个值。`map` 通常基于**红黑树（Red-Black Tree）**实现，具有自动排序和高效的查找、插入和删除操作。

### 实现原理：
1. **键值对（Key-Value Pair）：**
   - `map` 以键值对的形式存储数据，格式为 `std::pair<const Key, T>`，其中 `Key` 是键，`T` 是值。键是唯一的，不允许重复。

2. **基于红黑树（Red-Black Tree）实现：**
   - `map` 的底层通常采用红黑树作为平衡二叉搜索树的数据结构，这意味着 `map` 中的键是**有序的**，并且所有操作的平均时间复杂度为 O(log n)。
   - 红黑树是一种自平衡二叉树，它确保树的高度保持在 O(log n)，因此插入、删除、查找等操作都非常高效。

3. **主要操作：**
   - **插入 (`insert`)：** 将一个键值对插入到 `map` 中。如果键已经存在，插入操作不会覆盖原值。
   - **删除 (`erase`)：** 删除某个键对应的键值对。
   - **查找 (`find`)：** 根据键查找对应的值，返回一个迭代器指向该键值对。
   - **访问操作 (`operator[]`)：** 使用 `map[key]` 可以直接通过键访问和修改对应的值。如果键不存在，将创建该键并将其值初始化为默认值。
   - **判空 (`empty`)：** 判断 `map` 是否为空。
   - **获取大小 (`size`)：** 返回 `map` 中的键值对个数。

4. **自动排序：**
   - `map` 中的元素按照键的**升序**自动排序。默认情况下，`map` 使用 `<` 运算符来比较键的大小。如果需要自定义排序，可以提供一个比较器（如 `std::greater`）来改变排序规则。

5. **时间复杂度：**
   - **插入、删除、查找操作：** O(log n)，因为 `map` 依赖于红黑树这种平衡二叉搜索树来实现所有操作。
   - **访问元素：** O(log n) 通过 `find` 查找键对应的元素；使用 `operator[]` 访问元素的时间复杂度也是 O(log n)。
6. **multimap：**
   - multimap 是 map 的变种，它允许相同的键对应多个值，也就是说，在 multimap 中键不需要唯一。

### 总结：
C++ STL 中的 `map` 是一种基于红黑树实现的关联容器，提供了键值对的有序存储，并支持 O(log n) 时间复杂度的查找、插入和删除操作。`map` 通过自动排序和高效操作，是在需要高效键值对查找和管理时常用的数据结构。

## set
在C++标准模板库（STL）中，`set` 是一种关联容器，用于存储**唯一的**、有序的元素集合。`set` 通常基于**红黑树（Red-Black Tree）**实现，这意味着其元素是自动排序的，并且查找、插入和删除操作的时间复杂度为 O(log n)。

### 实现原理：
1. **唯一性：**
   - `set` 中的每个元素都是唯一的，不能有重复元素。如果试图插入已存在的元素，插入操作将失败。
   
2. **基于红黑树（Red-Black Tree）实现：**
   - `set` 底层使用红黑树作为数据结构，这是一种自平衡的二叉搜索树。红黑树确保 `set` 中的元素总是按**升序**排列（默认情况下），并且所有的插入、删除和查找操作都保持 O(log n) 的时间复杂度。
   
3. **有序性：**
   - `set` 自动对存储的元素进行排序，默认是按照升序排序。如果需要自定义排序顺序，可以使用自定义比较器。

4. **主要操作：**
   - **插入 (`insert`)：** 将新元素插入到 `set` 中。若元素已存在，插入操作将失败。
   - **删除 (`erase`)：** 删除特定元素。
   - **查找 (`find`)：** 查找某个元素是否存在，返回一个指向该元素的迭代器。
   - **判空 (`empty`)：** 判断 `set` 是否为空。
   - **获取大小 (`size`)：** 返回 `set` 中元素的个数。
   - **范围操作 (`begin()` 和 `end()`)：** 通过迭代器遍历 `set`。

5. **时间复杂度：**
   - **插入、删除、查找操作：** O(log n)，因为 `set` 依赖红黑树的平衡性来保持操作的高效性。
   - **遍历操作：** O(n)，遍历整个 `set` 的时间复杂度为 O(n)，因为元素是按顺序存储的。

### 常用成员函数：
- **`insert()`**：插入元素。
- **`erase()`**：删除元素。
- **`find()`**：查找元素是否存在。
- **`size()`**：返回元素个数。
- **`empty()`**：判断是否为空。
- **`clear()`**：清空集合中的所有元素。

### `multiset`：
`multiset` 是 `set` 的一个变种，区别在于 `multiset` 允许**重复元素**的存在。在 `multiset` 中，同样的元素可以出现多次，而 `set` 中元素必须是唯一的。

### 总结：
`set` 是一种基于红黑树实现的关联容器，主要用于存储唯一且有序的元素。它通过 O(log n) 的时间复杂度实现插入、删除和查找操作，适用于需要频繁查找或插入唯一元素的场景。如果需要存储重复元素，可以使用 `multiset`。

## deque

https://blog.csdn.net/yl_puyu/article/details/103361874

## vector

https://blog.csdn.net/qq_61820853/article/details/140149705

## vector和list的比较

在C++标准模板库（STL）中，`vector` 和 `list` 是两种常见的序列容器，但它们在实现方式和性能上存在显著差异。选择哪种容器取决于你的应用场景。下面将从实现原理、操作性能、存储方式等方面对它们进行详细比较。

### 1. **底层实现**：
- **`vector`**：基于**动态数组**实现，存储在**连续的内存块**中。
- **`list`**：基于**双向链表**实现，元素存储在**非连续的内存块**中，每个元素都有指向前后元素的指针。

### 2. **内存分配**：
- **`vector`**：所有元素存储在连续的内存中。由于 `vector` 需要一次性分配足够的内存来存储所有元素，因此当 `vector` 容量不足时，它会重新分配一块更大的内存，并将现有元素复制到新内存中。这种操作耗费时间，但因为容量通常以倍数扩展，所以扩展操作被均摊到多次插入中。
- **`list`**：每个元素独立分配内存，内存不连续。`list` 只需要为每个新元素分配内存，不需要进行大规模的复制和重分配。

### 3. **访问效率**：
- **`vector`**：支持**O(1) 时间复杂度**的随机访问，因为 `vector` 底层是连续存储的数组，可以通过下标直接访问任意元素。
- **`list`**：不支持随机访问。查找某个位置的元素需要遍历链表，时间复杂度为**O(n)**。

### 4. **插入和删除操作**：
- **`vector`**：
  - **尾部插入/删除（`push_back` / `pop_back`）**：时间复杂度为**O(1)**。如果内存不足，`push_back` 可能触发内存重新分配，导致时间复杂度变为 O(n)（但这个操作是均摊的）。
  - **中间或前端插入/删除**：时间复杂度为**O(n)**，因为需要移动元素以保持内存连续性。
  
- **`list`**：
  - **任意位置的插入和删除**：时间复杂度为**O(1)**，因为 `list` 的插入和删除操作只涉及指针的修改，不需要移动其他元素。但要找到插入/删除的位置，需要先遍历链表，耗费 O(n) 的时间。
  - **头部和尾部的插入/删除**：如果直接操作链表的头尾节点（`push_front` / `push_back`），时间复杂度为**O(1)**。

### 5. **迭代器的有效性**：
- **`vector`**：
  - 插入或删除操作可能使**所有迭代器失效**，因为 `vector` 的元素存储在连续的内存中，插入或删除可能导致内存重新分配或移动现有元素。
- **`list`**：
  - 插入或删除元素不会影响其他迭代器的有效性，除非删除的是迭代器指向的元素。

### 6. **内存开销**：
- **`vector`**：
  - 由于 `vector` 使用连续内存，内存开销较小。然而，为了应对元素增长，`vector` 通常会预留比当前元素更多的内存（通过 `capacity`）。
- **`list`**：
  - 由于 `list` 的每个元素都有两个额外的指针（前驱和后继），因此内存开销相对较大，尤其是在元素较多时，这些指针的开销显著。

### 7. **场景适用性**：
- **`vector`**：
  - 适用于需要频繁进行**随机访问**的场景。
  - 适合数据量较大但插入、删除操作相对较少的情况，尤其是需要按顺序存储数据的场景。
  
- **`list`**：
  - 适用于需要频繁在**中间插入或删除**元素的场景，尤其是当数据量较大、插入删除操作多时。
  - 由于 `list` 的顺序存储方式，它在实现队列、双端队列（如 `deque`）、LRU 缓存等场景中很有用。

### 8. **性能对比总结**：

| **操作**           | **`vector` 性能**             | **`list` 性能**              |
|--------------------|-----------------------------|-----------------------------|
| **随机访问**       | O(1)                         | O(n)                        |
| **尾部插入/删除**  | O(1)（均摊）                 | O(1)                        |
| **头部插入/删除**  | O(n)                         | O(1)                        |
| **中间插入/删除**  | O(n)                         | O(1)（插入/删除），O(n)（查找） |
| **内存消耗**       | 较小（但会预留多余内存）     | 较大（需要额外指针开销）     |

### 选择建议：
- **使用 `vector` 的场景**：如果你的程序需要频繁地**随机访问**元素，或者你主要在**尾部插入和删除**元素，那么 `vector` 是更好的选择。
- **使用 `list` 的场景**：如果你的程序需要在**中间位置频繁插入或删除**元素，或者对性能的要求是保证操作的 O(1) 插入和删除，而不是随机访问，那么 `list` 更适合。


## vector迭代器失效
* 当容器调用erase()方法后，当前位置到容器末尾元素的所有迭代器全部失效。
* 当容器调用insert()方法后，当前位置到容器末尾元素的所有迭代器全部失效。
* 如果容器扩容，在其他地方重新又开辟了一块内存。原来容器底层的内存上所保存的迭代器全都失效了。

## explicit关键字

`explicit` 关键字在 C++ 中用于防止编译器执行隐式类型转换或单参数构造函数的隐式调用。它可以防止因为隐式转换带来的意外行为，从而提高代码的可读性和安全性。

### `explicit` 关键字的作用

1. **防止隐式转换**
   当类中定义了带有一个参数的构造函数时，编译器可以允许使用隐式转换。例如，如果一个类 `A` 有一个单参数的构造函数，则可以通过传递该参数的类型来隐式创建 `A` 的对象，而不需要显式调用构造函数。`explicit` 关键字可以防止这种隐式转换。

2. **防止单参数构造函数的隐式调用**
   编译器可能会将某个单一参数传递给构造函数，这时会自动调用构造函数将该参数转化为类对象。使用 `explicit` 关键字，可以避免这种隐式调用，只允许显式调用。

### 示例代码

#### 没有 `explicit` 的隐式转换

```cpp
#include <iostream>

class A {
public:
    // 单参数构造函数，允许隐式转换
    A(int x) {
        std::cout << "Constructor called with value: " << x << std::endl;
    }
};

void func(A a) {
    std::cout << "func called" << std::endl;
}

int main() {
    func(42);  // 隐式转换，int 42 被自动转换为 A 对象
    return 0;
}
```

**输出：**

```
Constructor called with value: 42
func called
```

在这个例子中，整数 `42` 被隐式转换为 `A` 类对象。这是因为类 `A` 的构造函数允许从 `int` 到 `A` 的隐式转换。

#### 使用 `explicit` 防止隐式转换

```cpp
#include <iostream>

class A {
public:
    // 使用 explicit 防止隐式转换
    explicit A(int x) {
        std::cout << "Constructor called with value: " << x << std::endl;
    }
};

void func(A a) {
    std::cout << "func called" << std::endl;
}

int main() {
    // func(42);  // 错误：不允许隐式转换
    func(A(42));  // 必须显式调用构造函数
    return 0;
}
```

**输出：**

```
Constructor called with value: 42
func called
```

在这个例子中，`explicit` 关键字阻止了从 `int` 到 `A` 的隐式转换，因此不能直接传递整数 `42` 给 `func`，必须通过 `A(42)` 显式构造 `A` 对象。

### `explicit` 用在多个参数的构造函数中

`explicit` 也可以用于多个参数的构造函数，但在这种情况下，隐式转换通常不会发生，因为多个参数构造函数本身并不支持隐式调用。

```cpp
class B {
public:
    explicit B(int x, int y) {
        std::cout << "B constructor called with values: " << x << ", " << y << std::endl;
    }
};

int main() {
    // B b = {10, 20};  // 错误：explicit 禁止了此类的初始化
    B b(10, 20);  // 正确，必须显式构造对象
    return 0;
}
```

### `explicit` 与模板

在 C++11 中，`explicit` 可以与模板一起使用，这对于模板类的构造函数也很有用。

```cpp
template <typename T>
class C {
public:
    explicit C(T t) {
        std::cout << "C constructor called with value: " << t << std::endl;
    }
};

int main() {
    // C<int> c = 10;  // 错误：禁止隐式转换
    C<int> c(10);  // 必须显式调用构造函数
    return 0;
}
```

### 小结

- `explicit` 关键字用于防止隐式类型转换，尤其是在类的单参数构造函数中。
- 它提高了代码的安全性和可读性，避免意外的隐式转换。
- 通过使用 `explicit`，可以强制要求调用者在创建对象时显式地进行类型转换。
- 总结隐式调用的危害
  * 隐藏的类型转换：隐式调用隐藏了类型转换的实际发生，可能会让代码逻辑变得不清晰，开发者误认为自己在处理一种类型，实际上却是在处理另一个类型的对象。
  * 引入逻辑错误：在复杂代码中，隐式转换可能会引发意外的逻辑错误，特别是在类型不兼容或不期望发生转换的地方。
  * 性能损失：每次隐式转换都会创建一个新对象，可能会带来不必要的对象创建和析构，消耗系统资源。


## cpp智能指针实现原理

C++智能指针是一种自动管理动态内存的工具，旨在避免手动管理内存时出现的内存泄漏或重复释放问题。C++标准库中常见的智能指针有`std::unique_ptr`、`std::shared_ptr`和`std::weak_ptr`。每种智能指针都有不同的用途和实现方式，但它们的核心思想是通过RAII（Resource Acquisition Is Initialization）管理资源的生命周期。

### `std::unique_ptr` 实现原理
`std::unique_ptr` 是一种独占所有权的智能指针，它确保在同一时间只有一个指针拥有对象的所有权。

**实现要点**：
- **单一所有权**：当`unique_ptr`销毁时，它会自动释放其所持有的对象。这通过其析构函数完成。
- **禁止拷贝**：`unique_ptr`通过禁用拷贝构造函数和拷贝赋值运算符来防止所有权的共享，但允许移动操作，转移所有权。
  
```cpp
template<typename T>
class unique_ptr {
private:
    T* ptr;  // 原始指针

public:
    // 构造函数
    explicit unique_ptr(T* p = nullptr) : ptr(p) {}

    // 禁用拷贝构造函数和赋值运算符
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

    // 移动构造函数和移动赋值运算符
    unique_ptr(unique_ptr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    unique_ptr& operator=(unique_ptr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    // 析构函数
    ~unique_ptr() {
        delete ptr;
    }

    // 重载*和->操作符
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }

    // 获取原始指针
    T* get() const { return ptr; }

    // 释放所有权
    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    // 重置指针
    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }
};
```

### `std::shared_ptr` 实现原理
`std::shared_ptr` 是一种引用计数的智能指针，可以多个`shared_ptr`对象共享同一资源，只有当最后一个指针销毁时，资源才会被释放。

**实现要点**：
- **引用计数**：`shared_ptr`使用一个引用计数器来跟踪有多少个指针共享同一对象。每当一个新的`shared_ptr`拷贝构造时，引用计数加1；当一个`shared_ptr`销毁时，引用计数减1；当引用计数为0时，资源被释放。
  
```cpp
template<typename T>
class shared_ptr {
private:
    T* ptr;                 // 原始指针
    size_t* ref_count;       // 引用计数器

public:
    // 构造函数
    explicit shared_ptr(T* p = nullptr) : ptr(p), ref_count(new size_t(1)) {}

    // 拷贝构造函数
    shared_ptr(const shared_ptr& other) : ptr(other.ptr), ref_count(other.ref_count) {
        ++(*ref_count);
    }

    // 拷贝赋值运算符
    shared_ptr& operator=(const shared_ptr& other) {
        if (this != &other) {
            // 先减少当前对象的引用计数
            if (--(*ref_count) == 0) {
                delete ptr;
                delete ref_count;
            }
            // 复制新对象的指针和引用计数
            ptr = other.ptr;
            ref_count = other.ref_count;
            ++(*ref_count);
        }
        return *this;
    }

    // 析构函数
    ~shared_ptr() {
        if (--(*ref_count) == 0) {
            delete ptr;
            delete ref_count;
        }
    }

    // 重载*和->操作符
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }

    // 获取引用计数
    size_t use_count() const { return *ref_count; }
};
```

### `std::weak_ptr` 实现原理
`std::weak_ptr`是为了解决`shared_ptr`的循环引用问题设计的。它不会增加引用计数，因此不会影响对象的生命周期，但可以用来检查资源是否仍然存在并获取对资源的访问。

**实现要点**：
- `weak_ptr`内部持有一个指向`shared_ptr`管理对象的弱引用，使用时需要调用`lock()`获取临时的`shared_ptr`对象，以确保对象仍然存在。

### 总结
智能指针的核心原理是通过RAII、引用计数等机制来自动管理资源的生命周期，减少内存泄漏和重复释放的问题。

## 野指针

### 野指针的产生

野指针是指那些指向无效或已经被释放的内存地址的指针。访问野指针会导致程序出现未定义行为，可能引发崩溃或数据损坏。

野指针主要在以下几种情况下产生：

1. **未初始化的指针**：
   在声明指针变量时，如果没有对其进行初始化，它将持有一个随机的内存地址，可能指向程序的任意内存位置，这就形成了野指针。

   ```cpp
   int* p;  // p 未初始化，指向未知地址，成为野指针
   *p = 10; // 未定义行为
   ```

2. **内存释放后继续使用**：
   当动态分配的内存被释放（通过`delete`或`free`），原来的指针并不会自动变为`nullptr`，它仍然指向原来的内存地址，但这块内存已经被释放或可能重新分配给其他用途，导致野指针产生。

   ```cpp
   int* p = new int(10);
   delete p;  // p 指向的内存被释放
   *p = 20;   // p 现在是野指针，未定义行为
   ```

3. **超出作用域的指针**：
   当指针指向的对象超出其作用域时，指针仍然持有一个已经无效的内存地址，这也会导致野指针。

   ```cpp
   int* getPointer() {
       int x = 10;
       return &x;  // 返回局部变量的地址，x 超出作用域后 p 成为野指针
   }

   int* p = getPointer();
   *p = 20;  // 未定义行为
   ```

4. **指向堆区的指针误用**：
   如果手动释放了内存但没有正确处理，或动态分配了内存但没有释放，这些情况可能造成野指针。

### 避免野指针的策略

1. **指针初始化**：
   始终在声明指针时进行初始化。如果没有合适的值，可以将其初始化为`nullptr`。

   ```cpp
   int* p = nullptr;  // 使用 nullptr 代替未初始化的指针
   ```

2. **内存释放后将指针置为`nullptr`**：
   在释放动态分配的内存后，立即将指针设置为`nullptr`，这样再次使用该指针时可以检测是否为空。

   ```cpp
   int* p = new int(10);
   delete p;
   p = nullptr;  // 防止野指针
   ```

3. **使用智能指针**：
   C++的智能指针如`std::unique_ptr`和`std::shared_ptr`可以自动管理内存，避免手动释放内存时出现错误。智能指针会在适当的时候自动释放资源。

   ```cpp
   std::unique_ptr<int> p = std::make_unique<int>(10);  // 自动管理内存
   ```

4. **避免返回局部对象的指针**：
   不要将函数中的局部变量的地址作为返回值，因为局部变量在函数返回后会被销毁。

   ```cpp
   int* getPointer() {
       static int x = 10;  // 使用静态变量代替局部变量
       return &x;
   }
   ```

5. **使用工具检测野指针**：
   使用内存检测工具（如Valgrind）可以帮助在调试过程中检测野指针问题，并进行相应的修正。

### 总结
野指针的产生是由于指针管理不当导致的，常见的原因包括未初始化指针、使用已经释放的指针等。通过合理的指针初始化、在释放内存后将指针置为`nullptr`、使用智能指针等方法可以有效避免野指针的产生。


## new/delete与malloc/free的区别

`new/delete` 和 `malloc/free` 是C++中用于动态内存管理的两种机制。它们的主要区别在于语法、内存管理机制和与对象生命周期的关系。下面详细介绍它们的不同之处：

### `new` 和 `delete`

- **用法**：
  - `new`：用于动态分配内存并调用构造函数。
    ```cpp
    int* p = new int(10);    // 分配内存并初始化为10
    int* arr = new int[5];   // 分配内存给一个整数数组
    ```
  - `delete`：用于释放由`new`分配的内存并调用析构函数。
    ```cpp
    delete p;       // 释放单个对象的内存
    delete[] arr;   // 释放数组的内存
    ```

- **特点**：
  - **对象构造和析构**：`new`不仅分配内存，还调用对象的构造函数；`delete`不仅释放内存，还调用对象的析构函数。这使得`new/delete`适合用来管理对象的生命周期。
  - **类型安全**：`new`和`delete`是类型安全的，即编译器会检查类型匹配。`new`返回特定类型的指针，`delete`适用于`new`分配的同一类型。
  - **使用异常**：如果`new`无法分配足够的内存，它会抛出`std::bad_alloc`异常。`delete`也会处理释放内存时可能出现的问题。

- **示例**：
  ```cpp
  class MyClass {
  public:
      MyClass() { /* constructor code */ }
      ~MyClass() { /* destructor code */ }
  };

  MyClass* obj = new MyClass(); // 分配内存并构造对象
  delete obj; // 释放内存并调用析构函数
  ```

### `malloc` 和 `free`

- **用法**：
  - `malloc`：用于分配内存，但不会初始化内存中的值。
    ```cpp
    int* p = (int*)malloc(sizeof(int));    // 分配内存
    ```
  - `free`：用于释放由`malloc`分配的内存。
    ```cpp
    free(p);  // 释放内存
    ```

- **特点**：
  - **无对象构造和析构**：`malloc`只是分配原始内存，不会调用构造函数或析构函数；`free`只是释放内存，不会调用析构函数。
  - **不类型安全**：`malloc`返回的是`void*`类型，必须强制转换为目标类型；`free`也不进行类型检查。
  - **无异常处理**：`malloc`在分配失败时返回`NULL`，而不是抛出异常。因此，程序需要手动检查返回值并处理错误。

- **示例**：
  ```cpp
  int* p = (int*)malloc(sizeof(int));  // 分配内存
  if (p != nullptr) {
      *p = 10; // 使用分配的内存
      free(p); // 释放内存
  }
  ```

### 总结

- **`new/delete`** 是C++专用的内存管理机制，支持对象的构造和析构，类型安全，适用于C++中的对象。
- **`malloc/free`** 是C语言的内存管理函数，适用于处理原始内存，不涉及对象的生命周期管理，类型不安全。

在C++中，推荐使用`new/delete`来处理动态内存，因为它们与C++的对象模型和异常处理机制更兼容。`malloc/free`主要用于与C代码兼容或在处理C风格的内存分配时。


## sizeof 和 strlen 区别？

*  sizeof 是运算符，它用于获取类型或对象在内存中的大小，其操作数可以是一个类型、一个对象或一个类型的表达式。
*  strlen 是一个函数，它用于获取字符串（即以空字符 '\0' 结尾的字符数组）的长度。它返回的是字符串中字符的个数，不包括结尾的空字符。