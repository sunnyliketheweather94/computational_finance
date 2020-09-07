#include <iostream>
#include <Eigen/Dense>
#include <Eigen/LU>

int main() {

    using Matrix = Eigen::Matrix<double, 4, 4>;
    Matrix p;

    p << 7, 3, -1, 2, 
         3, 8, 1, -4,
        -1, 1, 4, -1,
        2, -4, -1, 6;

    std::cout << "The matrix to be factorized: \n" << p << std::endl << std::endl;

    Eigen::PartialPivLU<Matrix> lu(p);
    std::cout << "The LU matrix is:\n" << lu.matrixLU() << std::endl << std::endl;

    // outputting the lower triangular matrix L
    Matrix L = Eigen::MatrixXd::Identity(4, 4);
    L.block<4, 4>(0, 0).triangularView<Eigen::StrictlyLower>() = lu.matrixLU();

    // outputting the upper triangular matrix U
    Matrix U = lu.matrixLU().triangularView<Eigen::Upper>();

    std::cout << "L:\n" << L << std::endl << std::endl;
    std::cout << "U:\n" << U << std::endl << std::endl;


    return 0;
}