#include "numerical_option_pricing.hpp"
#include <iostream>
#include <iomanip>



int main() {
    double S {60.0}, // underlying asset price $100.0
           K {60.0}, // strike price = $100.0
           r {0.05} , // risk-free rate = 5%
           v {0.1}  , // volatility in price of underlying asset = 20%
           T {1.0}  ; // time to maturity = 1 year 

    int num_iterations = 1000000;

    double call = monte_carlo(num_iterations, true,  S, K, r, v, T);
    double put  = monte_carlo(num_iterations, false, S, K, r, v, T);

    std::cout << "\nSpot price = "     << S << std::endl;
    std::cout << "Strike price = "   << K << std::endl;
    std::cout << "Risk-free rate = " << r << std::endl;
    std::cout << "Volatility = "     << v << std::endl;
    std::cout << "Time to expiry = " << T << std::endl;

    std::cout << std::endl;

    std::cout << "Price of call option = " << call << std::endl;
    std::cout << "Price of put option = "  << put  << std::endl;

    // int i = 10;
    // while(i--) {
    //     std::cout << normal_generator() << std::endl;
    // }

    return 0;
}