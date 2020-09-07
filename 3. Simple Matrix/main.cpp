#include "simple_matrix.h"
#include <iostream>

int main() {
    SimpleMatrix<double> A(3, 3, 5.0);
    SimpleMatrix<double> B(3, 3, 1.0); 
    SimpleMatrix<double> C = A + B;

    std::cout << "The matrix A is:\n" << A << std::endl << std::endl;
    std::cout << "The matrix B is:\n" << B << std::endl << std::endl;
    std::cout << "The sum of A and B is:\n" << C << std::endl << std::endl;

    return 0;
}