#include "qs_matrix.hpp"
#include <iostream>

int main() {
    QSMatrix<double> mat1(3, 4, 0.0);
    // QSMatrix<double> mat2(5, 5, 2.0);
    // double scalar1 = 5.0;

    // QSMatrix<double> mat3 = mat1 * scalar1;
    double count = 1.0;

    for(unsigned i = 0; i < mat1.get_rows(); ++i) {
        for(unsigned j = 0; j < mat1.get_cols(); ++j) {
            mat1(i, j) += count++;
        }
    }

    std::cout << "The matrix A is:\n" << mat1 << std::endl << std::endl;
    // std::cout << "The matrix B is:\n" << scalar1 << std::endl << std::endl;
    // std::cout << "The sum of A and B is:\n" << mat3 << std::endl << std::endl;

    std::cout << "The transpose of A is:\n" << mat1.transpose() << std::endl;

    return 0;
}