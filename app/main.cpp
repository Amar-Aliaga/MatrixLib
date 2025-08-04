#include <vector>
#include "matrix.hpp"
#include <chrono>
using namespace mxlib;

int main() {

    Matrix one (10,10,10000000.3);
    Matrix two (10,10,48110000.4);

    auto start = std::chrono::high_resolution_clock::now();
    one += two;
    auto end = std::chrono::high_resolution_clock::now();
    

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Execution time: " << duration.count() << " ms" << std::endl;

    std::cout << one;

    return 0;
}