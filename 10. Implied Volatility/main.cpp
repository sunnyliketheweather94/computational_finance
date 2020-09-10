#ifndef __MAIN_CPP__
#define __MAIN_CPP__

#include "black_scholes.hpp"
// #include "interval_bisection.hpp"
#include "newton_raphson.hpp"
#include <iostream>

int main() {
    double S {100.0}, K {100.0}, r {0.05}, T {1.0}, C_M {10.5};
    BlackScholes bsc(S, K, r, T, true);

    // // Interval bisection method's initialization
    // double low_vol {0.05}, high_vol {0.35}, epsilon {0.001};
    // double sigma = interval_bisect(C_M, low_vol, high_vol, epsilon, bsc);

    // Newton-Raphson method's initialization
    double init = 0.3, epsilon = 0.001;
    double sigma = newton_raphson<BlackScholes, &BlackScholes::option_price, &BlackScholes::option_vega>
                   (C_M, init, epsilon, bsc);


    std::cout << "Implied volatilty = " << sigma << std::endl;

    return 0;
}

#endif