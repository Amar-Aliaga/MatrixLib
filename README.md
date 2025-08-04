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

## Parallelization Strategy

**Current Implementation**: Single-threaded. The `<thread>` header is included but no parallel execution is implemented.

**Parallelization Potential**: Matrix multiplication is the primary candidate for parallelization since each result element computation is independent. Proposed strategy:

1. **Row-wise Distribution**: Assign each output row to a separate thread
2. **Thread Pool**: Use up to M threads for M-row matrices with optimal resource management
3. **Threshold-based**: Enable parallelization only for matrices above certain size thresholds

**Performance Considerations**: 
- **Memory Layout**: Contiguous storage provides excellent spatial locality
- **In-place Operations**: Compound operators minimize memory allocations
- **Trade-offs**: Parallelization would improve performance for large matrices at the cost of increased complexity

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
