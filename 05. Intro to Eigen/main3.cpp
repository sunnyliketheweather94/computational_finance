#include <iostream>
#include <Eigen/Dense>

int main() {
    Eigen::Matrix3d m = Eigen::Matrix3d::Random();
    m = (m + Eigen::Matrix3d::Constant(1.2)) * 50;

    std::cout << "m:\n" << m << std::endl;


    Eigen::Vector3d v(1, 2, 3);
    std::cout << "m * v = \n" << m * v << std::endl;


    return 0;
}