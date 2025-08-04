#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>
#include "matrix.hpp" 


#define ASSERT_EQ(a, b) assert((a) == (b))


#define ASSERT_THROWS_AS(func, exception_type) \
    do { \
        bool thrown = false; \
        try { \
            func(); \
        } catch (const exception_type&) { \
            thrown = true; \
        } catch (...) {} \
        assert(thrown && "Expected exception was not thrown."); \
    } while(0)


void test_constructors() {
    std::cout << "Running constructor tests..." << std::endl;

    // Test default constructor and deduction guide
    mxlib::Matrix<int> m1(2, 3, 5);
    ASSERT_EQ(m1.get_rows(), 2);
    ASSERT_EQ(m1.get_cols(), 3);
    ASSERT_EQ(m1(1, 2), 5);

    // Test initializer list constructor
    mxlib::Matrix<int> m2 = {{1, 2, 3}, {4, 5, 6}};
    ASSERT_EQ(m2.get_rows(), 2);
    ASSERT_EQ(m2.get_cols(), 3);
    ASSERT_EQ(m2(0, 0), 1);
    ASSERT_EQ(m2(1, 2), 6);

    // Test templated converting constructor
    mxlib::Matrix<double> m3 = m2;
    ASSERT_EQ(m3.get_rows(), 2);
    ASSERT_EQ(m3.get_cols(), 3);
    ASSERT_EQ(m3(0, 0), 1.0);
    ASSERT_EQ(m3(1, 2), 6.0);
    
    std::cout << "  - Constructors passed." << std::endl;
}

void test_constructor_exceptions() {
    std::cout << "Running constructor exception tests..." << std::endl;
    
    // Test zero dimensions
    ASSERT_THROWS_AS([&](){ mxlib::Matrix<double> m(0, 5); }, std::invalid_argument);
    ASSERT_THROWS_AS([&](){ mxlib::Matrix<double> m(5, 0); }, std::invalid_argument);

    // Test bad initializer lists
    ASSERT_THROWS_AS([&](){ mxlib::Matrix<double> m({}); }, std::invalid_argument);
    //ASSERT_THROWS_AS([&](){ mxlib::Matrix<double> m = {{1}, {2, 3}}; }, std::invalid_argument);
    
    std::cout << "  - Constructor exceptions passed." << std::endl;
}

void test_accessors() {
    std::cout << "Running accessor tests..." << std::endl;

    mxlib::Matrix<int> m = {{1, 2}, {3, 4}};
    ASSERT_EQ(m(0, 0), 1);
    ASSERT_EQ(m[3], 4);
    
    m(0, 0) = 10;
    ASSERT_EQ(m(0, 0), 10);
    
    ASSERT_THROWS_AS([&](){ m(10, 10); }, std::out_of_range);
    
    std::cout << "  - Accessors passed." << std::endl;
}

void test_addition() {
    std::cout << "Running addition tests..." << std::endl;

    mxlib::Matrix<int> a = {{1, 2}, {3, 4}};
    mxlib::Matrix<int> b = {{5, 6}, {7, 8}};
    
    // Test operator+
    mxlib::Matrix<int> c = a + b;
    ASSERT_EQ(c(0, 0), 6);
    ASSERT_EQ(c(1, 1), 12);

    // Test operator+=
    a += b;
    ASSERT_EQ(a(0, 0), 6);
    ASSERT_EQ(a(1, 1), 12);
    
    std::cout << "  - Addition passed." << std::endl;
}

void test_subtraction() {
    std::cout << "Running subtraction tests..." << std::endl;

    mxlib::Matrix<int> a = {{1, 2}, {3, 4}};
    mxlib::Matrix<int> b = {{1, 1}, {1, 1}};
    
    // Test operator-
    mxlib::Matrix<int> c = a - b;
    ASSERT_EQ(c(0, 0), 0);
    ASSERT_EQ(c(1, 1), 3);

    // Test operator-=
    a -= b;
    ASSERT_EQ(a(0, 0), 0);
    ASSERT_EQ(a(1, 1), 3);
    
    std::cout << "  - Subtraction passed." << std::endl;
}

void test_multiplication() {
    std::cout << "Running multiplication tests..." << std::endl;

    mxlib::Matrix<int> a = {{1, 2}, {3, 4}};
    mxlib::Matrix<int> b = {{5, 6}, {7, 8}};
    
    // Test operator*
    mxlib::Matrix<int> c = a * b;
    ASSERT_EQ(c(0, 0), 19);
    ASSERT_EQ(c(0, 1), 22);
    ASSERT_EQ(c(1, 0), 43);
    ASSERT_EQ(c(1, 1), 50);

    // Test operator*=
    a *= b;
    ASSERT_EQ(a(0, 0), 19);
    
    std::cout << "  - Multiplication passed." << std::endl;
}

void test_transpose() {
    std::cout << "Running transpose tests..." << std::endl;

    // Square matrix
    mxlib::Matrix<int> a = {{1, 2}, {3, 4}};
    a.transpose();
    ASSERT_EQ(a(0, 0), 1);
    ASSERT_EQ(a(0, 1), 3);
    ASSERT_EQ(a(1, 0), 2);
    ASSERT_EQ(a(1, 1), 4);
    
    // Non-square matrix
    mxlib::Matrix<int> b = {{1, 2, 3}, {4, 5, 6}};
    b.transpose();
    ASSERT_EQ(b.get_rows(), 3);
    ASSERT_EQ(b.get_cols(), 2);
    ASSERT_EQ(b(0, 1), 4);
    ASSERT_EQ(b(2, 0), 3);
    
    std::cout << "  - Transpose passed." << std::endl;
}


int main() {
    std::cout << "Starting all tests..." << std::endl;
    
    test_constructors();
    test_constructor_exceptions();
    test_accessors();
    test_addition();
    test_subtraction();
    test_multiplication();
    test_transpose();

    std::cout << "All tests passed successfully!" << std::endl;
    
    return 0;
}
