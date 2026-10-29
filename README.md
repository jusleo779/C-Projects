# ECE 150 — C++ Programming Projects

Five C++ projects from ECE 150 (Fundamentals of Programming) at the University of Waterloo, Fall 2025. They cover input validation, bit manipulation, manual heap memory management, C-style strings and recursion, and a linked-list data structure with operator overloading.

> **Authorship.** The course supplied each project's specification, function signatures, and test harnesses. Supplied files are marked **[supplied]** below. All function bodies not marked as supplied are my own implementations.

## Quick start

Requires `g++` with C++17.

```bash
# Project 1–3: single file with its own main()
g++ -std=c++17 Project1/project_1.cpp -o p1 && ./p1
g++ -std=c++17 Project2/project_2.cpp -o p2 && ./p2
g++ -std=c++17 project3/project_3.cpp -o p3 && ./p3

# Project 4: implementation + supplied header and test main
cd Project4 && g++ -std=c++17 project_4.cpp main.cpp -o p4 && ./p4

# Project 5: supplied test main #includes project_5.cpp
cd Project5 && g++ -std=c++17 project_5_test_main.cpp -o p5 && ./p5
```

| # | Project | Main concepts |
|---|---------|---------------|
| 1 | Final grade calculator | Input validation loops, weighted interpolation |
| 2 | Patterns and bit manipulation | Nested loops, bit masks, shifts |
| 3 | Dynamic arrays | `new[]`/`delete[]`, pointer ownership, in-place array algorithms |
| 4 | C-string library | Null-terminated strings, recursion, insertion sort |
| 5 | Linked-list `Set` class | Classes, copy/move semantics, operator overloading |

---

## Project 1 — Final grade calculator

`Project1/project_1.cpp`

An interactive program that reads the maximum and earned marks for a final exam, a midterm, and five projects, and then prints the course grade.

- **Input validation:** a `do`/`while` loop re-prompts until each maximum is a positive integer and each earned mark is between 0 and that maximum.
- **Grading rules:**
  - Each mark is converted to a percentage.
  - If the final exam percentage is higher than another component, it replaces that component.
  - The exam average is 75% final and 25% midterm.
  - At 40% or below, the exam average is the course grade.
  - At 60% or above, the course grade is two-thirds exams and one-third projects.
  - Between 40% and 60%, the project weight is interpolated linearly.

## Project 2 — Patterns and bit manipulation

`Project2/project_2.cpp`

| Function | What it does |
|----------|--------------|
| `pattern(n)` | Prints an hourglass of `*` characters with `2n + 1` rows |
| `log10(n)` | Returns ⌊log₁₀ n⌋ for a 32-bit unsigned value, computed by repeated multiplication with no `<cmath>`. Asserts `n != 0`. |
| `count(n, bit)` | Counts the 0s or 1s among the 32 bits of `n` by masking the LSB and shifting right |
| `swap_bytes(n, b0, b1)` | Swaps byte `b0` and byte `b1` of a 32-bit word. Each byte is extracted with a mask (`0xFF << 8k`) and cleared from the word, then the two bytes are shifted into each other's positions and OR'd back in. |

`main()` contains commented-out test blocks for each function. Uncomment one block to run it.

**Known gap:** `swap_bytes2` is an unfinished stub with no return value, so it is not used.

## Project 3 — Dynamic arrays

`project3/project_3.cpp`

| Function | What it does |
|----------|--------------|
| `geometric(a, ratio, cap)` | Allocates a `double[cap]` on the heap and fills it with `a, a·r, a·r², …` |
| `cross_correlation(a0, n0, a1, n1)` | Allocates a zero-initialized array of size `n0 + n1 − 1` and accumulates `out[i+j] += a0[i]·a1[j]`. The spec names this cross-correlation, but the operation is discrete convolution. |
| `shift_duplicates(array, n)` | Works in place: keeps unique values at the front in their original order, moves repeats to the back, and returns the number of unique values |
| `deallocate(ptr, is_array, n)` | Zeroes the memory, calls the matching `delete`/`delete[]`, and sets the caller's pointer to `nullptr` (the pointer is passed by reference) |
| `test_geometric`, `test_shift` | Self-written checks for `geometric` and `shift_duplicates` |

The functions that return heap arrays transfer ownership to the caller, who must call `deallocate`.

## Project 4 — C-string library

`Project4/project_4.cpp` · `p_4_header.hpp` **[supplied]** · `main.cpp` **[supplied]** · `test_words.txt` **[supplied]**

This project reimplements string utilities without `<cstring>` and uses them on arrays of words.

| Function | What it does |
|----------|--------------|
| `length` | Counts characters up to `'\0'` |
| `compare` | Lexicographic comparison that returns −1, 0, or 1 |
| `assign` | Copies a string, including the terminator |
| `distance` | Recursive edit distance: the minimum number of insertions, deletions, and substitutions |
| `is_sorted` | Returns the length of the sorted prefix |
| `insert` / `insertion_sort` | Insertion sort on an array of `char*` |
| `remove_duplicates` | Removes adjacent duplicates from a sorted array and returns the new count |
| `find` | Returns the index of an exact match, otherwise a fallback index based on edit distance |
| `free_word_array` | Frees the two allocations made by the supplied file reader |

`read_words_from_file` is declared in the supplied header and is not my implementation.

**Known limitations:**

- `distance` is plain recursion without memoization, so it takes exponential time and only suits short words.
- The fallback in `find` keeps the *largest* distance (`smallD < size`), not the smallest, so it does not return the closest word.
- `insert` allocates a new copy of each word it moves, and that copy is never freed.

## Project 5 — Linked-list `Set` class

`Project5/project_5.cpp` · `project_5_test_main.cpp` **[supplied]**

An integer set stored as a singly linked list of `Node` objects. New elements are added at the head.

**Supplied by the course:** the `Set`/`Node` class declarations, `operator<<`, and the test main.

**My implementation:**

- **Lifetime:**
  - initializer-list constructor
  - destructor (`clear()`)
  - copy constructor
  - move constructor
  - copy assignment (with a self-assignment check)
  - move assignment
- **Core operations:**
  - `empty`
  - `size`
  - `clear`
  - `find`, which returns the `Node*` or `nullptr`
  - `insert` for a single item or an array range, which rejects duplicates and returns the number added
  - `erase`
  - `merge`, which moves nodes from `other` instead of copying them
- **Set algebra:**
  - in-place operators `|=` (union), `&=` (intersection), `^=` (symmetric difference), and `-=` (difference)
  - non-mutating `|`, `&`, `^`, and `-`, each built on its in-place counterpart through a copy
- **Comparison:**
  - `<=` and `>=` (subset and superset)
  - `<` and `>` (proper subset and superset)
  - `==` and `!=` (defined as mutual subset)

**Known limitations:**

- Move assignment swaps heads and then nulls `orig`, so the target set's previous list is leaked. It should call `clear()` first.
- `merge` stops when `o->next()` is null, so the last node of `other` is never checked.
- `insert(array, begin, end)` calls `insert` twice for each element. The result is correct but the work is redundant.
- Most operations are O(n) per lookup, so the set operations are O(n·m).

---

## Repository notes

- The `.exe` files are local Windows builds. They are not source files and should be excluded from version control.
- Check the course's academic-integrity policy before publishing this code publicly.
