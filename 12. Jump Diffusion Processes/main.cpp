#include "jump_process.hpp"
#include <iostream>


int main() {
    double S {100.0}, K {100.0}, r {0.05}, v {0.2}, T {1.0};
    int N {50};
    double m {1.083287}, lambda {1.0}, nu {0.4};

    std::cout << "call price under jump diffusion = " << price_under_jump(S, K, r, v, T, N, m, lambda, nu) << std::endl;

    return 0;
}