#include <iostream>
#include <Eigen/Dense>

using matrix = Eigen::Matrix3d;
using vector = Eigen::Vector3d;

int main() {
    matrix p, q; // both 3 by 3.
    vector r(1, 2, 3), s(4, 5, 6);

    p << 1, 2, 3, 4, 5, 6, 7, 8, 9;
    q << 10, 11, 12, 13, 14, 15, 16, 17, 18;

    std::cout << "p =\n" << p << std::endl << std::endl;
    std::cout << "q =\n" << q << std::endl << std::endl;

    std::cout << "p + q =\n" << p + q << std::endl << std::endl;
    std::cout << "p - q =\n" << p - q << std::endl << std::endl;

    std::cout << "r =\n" << r << std::endl << std::endl;
    std::cout << "s =\n" << s << std::endl << std::endl;

    std::cout << "r + s =\n" << r + s << std::endl << std::endl;
    std::cout << "r - s =\n" << r - s << std::endl << std::endl;

    std::cout << "p^T = \n" << p.transpose() << std::endl << std::endl;

    std::cout << "Reduction operations:\n---------------------\n";
    std::cout << "Sum of all elements of p = " << p.sum() << std::endl;
    std::cout << "Product of all elements of p = " << p.prod() << std::endl;
    std::cout << "Mean of all elements of p = " << p.mean() << std::endl;
    std::cout << "Minimum element of p = " << p.minCoeff() << std::endl;
    std::cout << "Maximum element of p = " << p.maxCoeff() << std::endl;
    std::cout << "Trace of p = " << p.trace() << std::endl;

    return 0;
}