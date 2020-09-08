
/* QR decomposition:
decomposes matrix A into 2 matrices: Q and R 
Q is an orthogonal matrix - QQ^T = I
R is an upper triangular matrix

slower than other methods but is numerically stable

we use the Householder Reflections method
*/

#include <iostream>
#include <Eigen/Dense>

using matrix = Eigen::Matrix<double, 3, 3>;

int main() {
    matrix P; // 3-by-3 matrix
    P << 12, -51, 4,
         6, 167, -68,
         -4, 24, -41;

    std::cout << "The matrix P is:\n" << P << std::endl << std::endl;

    Eigen::HouseholderQR<matrix> QR(P);
    matrix Q = QR.householderQ(); // returns the matrix Q

    std::cout << "The matrix Q is:\n" << Q << std::endl << std::endl;
    std::cout << "The matrix R is:\n" << Q.transpose() * P << std::endl << std::endl;

    return 0;
}