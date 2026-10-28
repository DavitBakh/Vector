# 📦 Vector — Custom STL-Compatible Dynamic Array in C++

![C++20](https://img.shields.io/badge/Language-C%2B%2B20-blue.svg)
![IDE](https://img.shields.io/badge/IDE-Visual%20Studio%202022-purple.svg)
![Type](https://img.shields.io/badge/Type-STL--like%20Container-green.svg)
![Coursework](https://img.shields.io/badge/University-Data%20Structures%20Course-orange.svg)
![Tests](https://img.shields.io/badge/Tests-TDD%20(16%20Suites)-brightgreen.svg)

A university coursework project for the **Data Structures and Algorithms** course. This repository provides a complete, modern C++ implementation of a dynamically resizing contiguous array (`Vector<T>`), matching the interface, resource ownership semantics, and asymptotic complexities of `std::vector` from the C++ Standard Template Library (STL).

---

## 📌 Architectural Highlights

### 1. Low-Level Memory Management & In-Place Construction
Naive dynamic array implementations frequently rely on `new T[n]`, which strictly requires `T` to be Default Constructible. This project handles memory using professional allocator-level idioms:
- Memory is acquired as **raw uninitialized byte storage**:
  ```cpp
  _arr = reinterpret_cast<T*>(new char[_capacity * sizeof(T)]);
  ```
- Elements are constructed in place via **placement new**:
  ```cpp
  new(_arr + i) T(val);
  ```
- Destroyed elements have their destructors explicitly invoked:
  ```cpp
  _arr[i].~T();
  ```
- Buffer deallocation releases raw storage:
  ```cpp
  delete[] reinterpret_cast<char*>(_arr);
  ```
This design enables `Vector<T>` to store **types lacking a default constructor** and **move-only types (lacking a copy constructor)**.

### 2. Move Semantics & Exception Safety (`noexcept`)
- Implements a move constructor and move assignment operator marked with `noexcept`.
- Reallocations transfer existing elements into the enlarged buffer via `std::move`, eliminating unnecessary deep copies.

### 3. In-Place Emplacement (`emplace_back`)
- A variadic member function `emplace_back(Args&&... args)` uses perfect forwarding (`std::forward<Args>(args)...`) to construct objects directly inside raw memory without intermediate copies.

### 4. Exponential Capacity Growth
- Expands capacity using the `2 * capacity + 1` geometric progression rule, guaranteeing **amortized O(1)** insertion time for `push_back`.

---

## 📁 Repository Structure

```text
Vector/
├── Vector.sln                       # Visual Studio 2022 Solution
├── .gitignore                       # Git ignores for build artifacts
│
└── Vector/
    ├── Vector.h                     # Template declaration & implementation of Vector<T>
    ├── main.cpp                     # Test runner entry point
    ├── Vector.vcxproj               # MSVC Project file
    │
    └── Tests/                       # 16 Modular TDD Test Suites
        ├── 1BasicConstructorsTest.h
        ├── 2InitializerListConstructorTest.h
        ├── 3PushBackTest.h
        ├── 4PopBackTest.h
        ├── 5ClearTest.h
        ├── 6CopyConstructorTest.h
        ├── 7AssignmentOperatorTest.h
        ├── 8AccessFunctionsTest.h
        ├── 9ReserveAndShrinkToFitTest.h
        ├── 10SwapTest.h
        ├── 11SubscriptOperatorTest.h
        ├── 12DestructorCallTest.h
        ├── 13EmplaceBackTest.h
        ├── 14ClassWithoutDefaultConstructorTest.h
        ├── 15ClassWithoutCopyConstructorTest.h
        ├── 16MoveConstructorAndMoveAssignmentOperatorTest.h
        └── Fixtures/                # Custom test fixtures & CustomAsserts
```

---

## 📋 Method Reference & Complexity

| Method | Signature | Time Complexity | Description |
| :--- | :--- | :--- | :--- |
| `push_back` | `void push_back(const T& val)` | `O(1)` amortized | Appends element to the end of the vector |
| `emplace_back` | `void emplace_back(Args&&... args)` | `O(1)` amortized | Constructs element in place at the back |
| `pop_back` | `void pop_back()` | `O(1)` | Removes the last element and invokes its destructor |
| `operator[]` | `T& operator[](size_t index)` | `O(1)` | Fast unchecked indexing (with debug `assert`) |
| `at` | `T& at(size_t index)` | `O(1)` | Bounds-checked access (throws `std::invalid_argument`) |
| `front` / `back` | `T& front()`, `T& back()` | `O(1)` | Access to the first and last elements |
| `data` | `T* data()` | `O(1)` | Direct pointer to the underlying continuous buffer |
| `size` | `size_t size() const` | `O(1)` | Number of active elements |
| `capacity` | `size_t capacity() const` | `O(1)` | Total allocated element capacity |
| `empty` | `bool empty() const` | `O(1)` | Returns true if the vector contains zero elements |
| `reserve` | `void reserve(size_t newCap)` | `O(N)` | Preallocates memory without changing vector size |
| `shrink_to_fit` | `void shrink_to_fit()` | `O(N)` | Reallocates buffer to exactly match `size` |
| `resize` | `void resize(size_t newSize)` | `O(N)` | Adjusts vector length, constructing or destroying items |
| `clear` | `void clear()` | `O(N)` | Destroys all elements and resets size to 0 |
| `swap` | `void swap(Vector& other)` | `O(1)` | Swaps storage pointers and metadata without copying |
| `operator==` | `bool operator==(const Vector&, ...)` | `O(N)` | Element-wise equality comparison |

---

## 🧪 Unit Testing (TDD)

The container passes **16 rigorous unit test suites**:
1. Default, sized, and value-filled constructors.
2. Initializer list construction (`std::initializer_list<T>`).
3. `push_back` append operations and capacity growth validation.
4. `pop_back` element removal.
5. `clear()` state verification.
6. Copy constructor deep copying.
7. Copy assignment operator with self-assignment guard.
8. Element access functions: `at()`, `front()`, `back()`, `data()`.
9. Capacity management: `reserve()` and `shrink_to_fit()`.
10. `O(1)` pointer swap via `swap()`.
11. Mutable and const `operator[]` subscripting.
12. **Destructor invocation tracker**: verifies zero memory leaks and prevents double-free defects.
13. Variadic `emplace_back` with arbitrary constructor argument lists.
14. Vector instantiation over types with **no default constructor**.
15. Support for Move-Only types (types with deleted copy constructors).
16. Move constructor and move assignment operator with source pointer nullification.

---

## ⚙️ Build and Execution

1. Open `Vector.sln` in **Visual Studio 2022**.
2. Select configuration **Debug / x64** or **Release / x64**.
3. Compile (`Ctrl + Shift + B`) and run the test executable (`Ctrl + F5`).
4. Output upon passing all 16 suites:
   ```text
   All tests passed!
   ```

---

## 👨‍💻 Author

- **Davit Bakhshyan ([DavitBakh](https://github.com/DavitBakh))**
