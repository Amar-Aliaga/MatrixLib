# Matrix Operations Library

A robust, template-based C++ Matrix class for fundamental matrix operations, designed as a lightweight, header-only solution focusing on clarity and performance.

## Features
- **Template-based design** - works with any numeric type
- **Modern C++20** - template deduction guides and move semantics
- **Header-only library** - easy integration, no separate compilation
- **Exception safety** - robust error handling with RAII
- **STL compatibility** - full iterator support

## Quick Start
```cpp
#include "matrix.hpp"
using namespace mxlib;

Matrix mat1 = {{1, 2, 3}, {4, 5, 6}};          // 2x3 matrix
Matrix<double> mat2(3, 3, 2.5);                // 3x3 filled with 2.5
auto result = mat1 * mat2;                     // Matrix multiplication
mat1.transpose();                              // In-place transpose
```

## Design Choices

**Templated Design**: Template class (`template <typename T>`) enables type flexibility and safety without code duplication.

**Contiguous Storage**: Elements stored in single `std::vector<T>` for:
- **Cache Locality**: Contiguous memory layout optimizes CPU cache usage
- **Memory Safety**: Automatic allocation/deallocation eliminates memory leaks
- **STL Integration**: Native iterator support for standard algorithms

**Move Semantics**: `std::move` in operations like `operator*=` and `transpose()` ensures efficient resource transfer for large matrices.

**Friend Operators**: Non-member arithmetic operators enable symmetric design and improved code organization.

## Time Complexity Analysis

| Operation | Complexity | Notes |
|-----------|------------|-------|
| Constructor (fill) | O(M×N) | Iterates through all elements |
| Element Access | O(1) | Direct index calculation |
| Addition/Subtraction | O(M×N) | Single pass through elements |
| Multiplication | O(M×N×P) | Classic O(N³) for square matrices |
| Transpose (in-place) | O(N²) | Square matrices only |
| Transpose (copy) | O(M×N) | Rectangular matrices |


## Parallel Matrix Operations

### Design Choices

Matrix addition operations are parallelized using C++11 `std::thread`. Each thread computes the sum of two matrices independently, allowing multiple matrix additions to execute concurrently. This approach is simple and leverages the operating system’s thread scheduler, making it easy to scale for multiple independent matrix operations.

- **Thread Usage:** In `main.cpp`, each matrix addition (`result = one + two`, etc.) is assigned to a separate thread.
- **Data Safety:** Each thread writes to its own result matrix, so no synchronization (mutex) is required.
- **Simplicity:** No thread pools or batching; threads are created for each independent operation.

### Complexity Analysis

| Operation                | Complexity | Notes                                 |
|--------------------------|------------|---------------------------------------|
| Matrix Addition (single) | O(M×N)     | Each element is summed once           |
| Thread Launch            | O(1)       | Overhead per thread                   |
| Parallel Additions       | O(M×N) per thread | Each thread runs independently |

- **Total time for N additions:** If run sequentially, O(N×M×N). With threads, wall-clock time can be reduced if CPU cores are available.

### Parallel Strategy

- **Independent Tasks:** Each thread performs a full matrix addition with no shared data.
- **No Synchronization Needed:** Since result matrices are separate, there are no data races.
- **Thread Count:** Number of threads equals the number of independent additions.
- **Scalability:** Performance improves with more CPU cores, but thread creation overhead may be noticeable for very small matrices.

### Performance

For large matrices (e.g., 5000×5000), parallel execution can significantly reduce total wall-clock time if the system has multiple CPU cores. Example timing (on a quad-core CPU):

- **Sequential:** ~X ms per addition (total ~3X ms for three additions)
- **Parallel (3 threads):** ~X ms total (all additions complete in roughly the time of one addition)

Actual performance depends on hardware, OS thread scheduling, and matrix size.

---


## Building
```bash
mkdir build && cd build
cmake ..
make
./test_matrixes/matrix_tests    # Run tests
```

**Requirements**: C++20, CMake 3.20+, GCC 10+/Clang 10+/MSVC 2019+

---
*This library demonstrates modern C++ design principles while maintaining simplicity and performance for educational and small-scale applications.*
