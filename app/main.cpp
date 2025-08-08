#include "matrix.hpp"
#include <vector>
#include <chrono>
#include <thread>


int main() {

    mxlib::Matrix one     (5000, 5000, 110000);
    mxlib::Matrix two     (5000, 5000, 110000);
    mxlib::Matrix three   (5000, 5000, 110000);
    mxlib::Matrix four    (4000, 4000, 30000);
    mxlib::Matrix result  (5000, 5000);
    mxlib::Matrix result1 (5000, 5000);
    mxlib::Matrix result2 (4000, 4000);
    mxlib::Matrix test1   (3,3,5);
    mxlib::Matrix test2   (3,3,3);
    
    std::cout << "The number of threads in this machine is: " << std::thread::hardware_concurrency() << std::endl;

    std::cout << test2;

    auto start = std::chrono::high_resolution_clock::now();

    std::thread t1([&]() { result  = one  + two;   });
    std::thread t2([&]() { result1 = one  + three; });
    std::thread t3([&]() { result2 = four + four;  });

    t1.join();
    t2.join();
    t3.join();

    auto end = std::chrono::high_resolution_clock::now();
    

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Execution time: " << duration.count() << " ms" << std::endl;


    return 0;
}
