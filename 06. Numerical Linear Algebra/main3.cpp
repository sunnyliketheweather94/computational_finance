

// using the Cholesky decomposition
#include <iostream>
#include <Eigen/Dense>

using matrix = Eigen::Matrix<double, 4, 4>;

int main() {
    matrix p; // p needs to be Hermitian and positive-definite.
    p << 6, 3, 4, 8,
         3, 6, 5, 1,
         4, 5, 10, 7,
         8, 1, 7, 25;


    std::cout << "The matrix P is:\n" << p << std::endl << std::endl;

    Eigen::LLT<matrix> llt(p); // computes the Cholesky decomposition
    matrix L = llt.matrixL(); // returns the matrix L such that P = LL^T

    std::cout << "The matrix L is:\n" << L << std::endl << std::endl;

    matrix U = L.transpose(); // get L^T and confirm that LL^T = P
    std::cout << "The product LL^T is:\n" << L * U << std::endl << std::endl;


    return 0;
}