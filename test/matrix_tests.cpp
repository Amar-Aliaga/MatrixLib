#include <cassert>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include "matrix.hpp"

// Test helper macros
#define ASSERT_THROWS(expression, exception_type) \
    do { \
        bool caught = false; \
        try { \
            expression; \
        } catch (const exception_type&) { \
            caught = true; \
        } \
        assert(caught && "Expected exception was not thrown"); \
    } while(0)

#define TEST_FUNCTION(name) \
    void name(); \
    void name()

// Test basic construction
TEST_FUNCTION(test_basic_construction) {
    std::cout << "Testing basic construction..." << std::endl;
    
    // Test basic constructor
    Matrix mat(3, 4, 5);
    assert(mat.get_rows() == 3);
    assert(mat.get_cols() == 4);
    assert(mat.size() == 12);
    assert(!mat.empty());
    
    // Check all elements are initialized correctly
    for(size_t i = 0; i < mat.size(); ++i) {
        assert(mat[i] == 5);
    }
    
    // Test default initialization
    Matrix mat2(2, 2);
    for(size_t i = 0; i < mat2.size(); ++i) {
        assert(mat2[i] == 0);
    }
    
    std::cout << "✅ Basic construction tests passed!" << std::endl;
}

// Test initializer list construction
TEST_FUNCTION(test_initializer_list_construction) {
    std::cout << "Testing initializer list construction..." << std::endl;
    
    Matrix mat = {{1, 2, 3}, 
                  {4, 5, 6}};
    
    assert(mat.get_rows() == 2);
    assert(mat.get_cols() == 3);
    assert(mat.size() == 6);
    
    // Check values
    assert(mat(0, 0) == 1); assert(mat(0, 1) == 2); assert(mat(0, 2) == 3);
    assert(mat(1, 0) == 4); assert(mat(1, 1) == 5); assert(mat(1, 2) == 6);
    
    // Test 1D access
    assert(mat[0] == 1); assert(mat[1] == 2); assert(mat[2] == 3);
    assert(mat[3] == 4); assert(mat[4] == 5); assert(mat[5] == 6);
    
    std::cout << "✅ Initializer list construction tests passed!" << std::endl;
}

// Test error conditions in construction
TEST_FUNCTION(test_construction_errors) {
    std::cout << "Testing construction error handling..." << std::endl;
    
    // Test zero dimensions
    ASSERT_THROWS(Matrix(0, 5), std::invalid_argument);
    ASSERT_THROWS(Matrix(5, 0), std::invalid_argument);
    
    // Test empty initializer list
    ASSERT_THROWS(Matrix({}), std::invalid_argument);
    
    // Test inconsistent row sizes
    ASSERT_THROWS(Matrix({{1, 2}, {3, 4, 5}}), std::invalid_argument);
    
    // Test empty rows
    ASSERT_THROWS(Matrix({{}}), std::invalid_argument);
    
    std::cout << "✅ Construction error tests passed!" << std::endl;
}

// Test element access
TEST_FUNCTION(test_element_access) {
    std::cout << "Testing element access..." << std::endl;
    
    Matrix mat = {{1, 2, 3}, 
                  {4, 5, 6}};
    
    // Test 2D access
    assert(mat(0, 0) == 1);
    assert(mat(0, 1) == 2);
    assert(mat(1, 2) == 6);
    
    // Test modification
    mat(0, 0) = 99;
    assert(mat(0, 0) == 99);
    assert(mat[0] == 99);  // Check 1D access reflects change
    
    // Test 1D access
    mat[3] = 88;
    assert(mat[3] == 88);
    assert(mat(1, 0) == 88);  // Check 2D access reflects change
    
    // Test const access
    const Matrix& const_mat = mat;
    assert(const_mat(0, 0) == 99);
    assert(const_mat[3] == 88);
    
    std::cout << "✅ Element access tests passed!" << std::endl;
}

// Test bounds checking
TEST_FUNCTION(test_bounds_checking) {
    std::cout << "Testing bounds checking..." << std::endl;
    
    Matrix mat(2, 3);
    
    // Test valid access (should not throw)
    mat(1, 2) = 42;
    mat[5] = 42;
    
    // Test invalid 2D access
    ASSERT_THROWS(mat(2, 0), std::out_of_range);  // row out of bounds
    ASSERT_THROWS(mat(0, 3), std::out_of_range);  // col out of bounds
    ASSERT_THROWS(mat(2, 3), std::out_of_range);  // both out of bounds
    
    // Test invalid 1D access
    ASSERT_THROWS(mat[6], std::out_of_range);     // index out of bounds
    
    // Test const versions
    const Matrix& const_mat = mat;
    ASSERT_THROWS(const_mat(2, 0), std::out_of_range);
    ASSERT_THROWS(const_mat[6], std::out_of_range);
    
    std::cout << "✅ Bounds checking tests passed!" << std::endl;
}

// Test addition operations
TEST_FUNCTION(test_addition) {
    std::cout << "Testing addition operations..." << std::endl;
    
    Matrix mat1 = {{1, 2}, 
                   {3, 4}};
    Matrix mat2 = {{5, 6}, 
                   {7, 8}};
    
    // Test operator+
    Matrix result = mat1 + mat2;
    assert(result(0, 0) == 6);  assert(result(0, 1) == 8);
    assert(result(1, 0) == 10); assert(result(1, 1) == 12);
    
    // Check original matrices unchanged
    assert(mat1(0, 0) == 1);
    assert(mat2(0, 0) == 5);
    
    // Test operator+=
    mat1 += mat2;
    assert(mat1(0, 0) == 6);  assert(mat1(0, 1) == 8);
    assert(mat1(1, 0) == 10); assert(mat1(1, 1) == 12);
    
    // Test dimension mismatch
    Matrix mat3(3, 2);
    ASSERT_THROWS(mat1 + mat3, std::invalid_argument);
    ASSERT_THROWS(mat1 += mat3, std::invalid_argument);
    
    std::cout << "✅ Addition tests passed!" << std::endl;
}

// Test subtraction operations
TEST_FUNCTION(test_subtraction) {
    std::cout << "Testing subtraction operations..." << std::endl;
    
    Matrix mat1 = {{10, 8}, 
                   {6, 4}};
    Matrix mat2 = {{1, 2}, 
                   {3, 4}};
    
    // Test operator-
    Matrix result = mat1 - mat2;
    assert(result(0, 0) == 9); assert(result(0, 1) == 6);
    assert(result(1, 0) == 3); assert(result(1, 1) == 0);
    
    // Check original matrices unchanged
    assert(mat1(0, 0) == 10);
    assert(mat2(0, 0) == 1);
    
    // Test operator-=
    mat1 -= mat2;
    assert(mat1(0, 0) == 9); assert(mat1(0, 1) == 6);
    assert(mat1(1, 0) == 3); assert(mat1(1, 1) == 0);
    
    std::cout << "✅ Subtraction tests passed!" << std::endl;
}

// Test multiplication operations
TEST_FUNCTION(test_multiplication) {
    std::cout << "Testing multiplication operations..." << std::endl;
    
    // Test basic multiplication
    Matrix mat1 = {{1, 2}, 
                   {3, 4}};  // 2x2
    Matrix mat2 = {{5, 6}, 
                   {7, 8}};  // 2x2
    
    Matrix result = mat1 * mat2;
    assert(result.get_rows() == 2);
    assert(result.get_cols() == 2);
    
    // Expected: [[1*5+2*7, 1*6+2*8], [3*5+4*7, 3*6+4*8]]
    //          = [[19, 22], [43, 50]]
    assert(result(0, 0) == 19); assert(result(0, 1) == 22);
    assert(result(1, 0) == 43); assert(result(1, 1) == 50);
    
    // Test non-square multiplication
    Matrix mat3 = {{1, 2, 3}, 
                   {4, 5, 6}};  // 2x3
    Matrix mat4 = {{7, 8}, 
                   {9, 10}, 
                   {11, 12}};   // 3x2
    
    Matrix result2 = mat3 * mat4;
    assert(result2.get_rows() == 2);
    assert(result2.get_cols() == 2);
    
    // Expected: [[1*7+2*9+3*11, 1*8+2*10+3*12], [4*7+5*9+6*11, 4*8+5*10+6*12]]
    //          = [[58, 64], [139, 154]]
    assert(result2(0, 0) == 58);  assert(result2(0, 1) == 64);
    assert(result2(1, 0) == 139); assert(result2(1, 1) == 154);
    
    // Test operator*=
    Matrix mat5 = {{1, 2}};  // 1x2
    Matrix mat6 = {{3}, {4}}; // 2x1
    mat5 *= mat6;
    assert(mat5.get_rows() == 1);
    assert(mat5.get_cols() == 1);
    assert(mat5(0, 0) == 11);  // 1*3 + 2*4 = 11
    
    // Test dimension mismatch
    Matrix mat7(2, 3);
    Matrix mat8(2, 2);  // cols of mat7 != rows of mat8
    ASSERT_THROWS(mat7 * mat8, std::invalid_argument);
    ASSERT_THROWS(mat7 *= mat8, std::invalid_argument);
    
    std::cout << "✅ Multiplication tests passed!" << std::endl;
}

// Test transpose operation
TEST_FUNCTION(test_transpose) {
    std::cout << "Testing transpose operation..." << std::endl;
    
    // Test square matrix transpose (in-place)
    Matrix square = {{1, 2, 3}, 
                     {4, 5, 6}, 
                     {7, 8, 9}};
    
    square.transpose();
    assert(square.get_rows() == 3);
    assert(square.get_cols() == 3);
    
    // Check transposed values
    assert(square(0, 0) == 1); assert(square(0, 1) == 4); assert(square(0, 2) == 7);
    assert(square(1, 0) == 2); assert(square(1, 1) == 5); assert(square(1, 2) == 8);
    assert(square(2, 0) == 3); assert(square(2, 1) == 6); assert(square(2, 2) == 9);
    
    // Test rectangular matrix transpose
    Matrix rect = {{1, 2, 3}, 
                   {4, 5, 6}};  // 2x3
    
    rect.transpose();  // Should become 3x2
    assert(rect.get_rows() == 3);
    assert(rect.get_cols() == 2);
    
    assert(rect(0, 0) == 1); assert(rect(0, 1) == 4);
    assert(rect(1, 0) == 2); assert(rect(1, 1) == 5);
    assert(rect(2, 0) == 3); assert(rect(2, 1) == 6);
    
    std::cout << "✅ Transpose tests passed!" << std::endl;
}

// Test chained operations
TEST_FUNCTION(test_chained_operations) {
    std::cout << "Testing chained operations..." << std::endl;
    
    Matrix A = {{1, 2}, {3, 4}};
    Matrix B = {{2, 0}, {1, 2}};
    Matrix C = {{1, 1}, {1, 1}};
    
    // Test A + B + C
    Matrix result1 = A + B + C;
    assert(result1(0, 0) == 4); assert(result1(0, 1) == 3);
    assert(result1(1, 0) == 5); assert(result1(1, 1) == 7);
    
    // Test (A + B) * C
    Matrix result2 = (A + B) * C;
    assert(result2(0, 0) == 6);  // (3*1 + 3*1)
    assert(result2(0, 1) == 6);  // (3*1 + 3*1)
    assert(result2(1, 0) == 12); // (6*1 + 6*1)
    assert(result2(1, 1) == 12); // (6*1 + 6*1)
    
    std::cout << "✅ Chained operations tests passed!" << std::endl;
}

// Test output operator
TEST_FUNCTION(test_output_operator) {
    std::cout << "Testing output operator..." << std::endl;
    
    Matrix mat = {{1, 2, 3}, 
                  {4, 5, 6}};
    
    std::ostringstream oss;
    oss << mat;
    std::string output = oss.str();
    
    // Check that output contains all elements (basic check)
    assert(output.find("1") != std::string::npos);
    assert(output.find("2") != std::string::npos);
    assert(output.find("6") != std::string::npos);
    
    std::cout << "✅ Output operator tests passed!" << std::endl;
}

// Test utility functions
TEST_FUNCTION(test_utility_functions) {
    std::cout << "Testing utility functions..." << std::endl;
    
    Matrix mat(3, 4, 42);
    
    assert(mat.get_rows() == 3);
    assert(mat.get_cols() == 4);
    assert(mat.size() == 12);
    assert(!mat.empty());
    
    Matrix empty_test(0, 0);  // This should throw, but let's test empty on valid matrix
    Matrix single(1, 1);
    assert(!single.empty());
    
    std::cout << "✅ Utility function tests passed!" << std::endl;
}

