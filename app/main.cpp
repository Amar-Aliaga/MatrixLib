#include <vector>
#include "matrix.hpp"
using namespace mxlib;

int main() {

    std::vector<std::vector<int>> m {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };
    std::vector<std::vector<int>> m1 {
        {1,1,1},
        {1,1,1},
        {2,2,2}
    };

    Matrix mat ={ 
                  {1,2,3}, 
                  {4,5,6}
                };
    Matrix mati12 ={
                  {3,4,2}, 
                  {5,6,7}, 
                  {7,8,1}
                };

    Matrix mat3 ={
                  {1000,30000,400}, 
                  {400,50000,6000}, 
                  {6000,700,80000}
                };

    Matrix test (3,3,1);
    Matrix test1(3,3,1);

    test *= mati12;
    test = test + test1;
    //res.transpose();
    std::cout << test;


    return 0;
}