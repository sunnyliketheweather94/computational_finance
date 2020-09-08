#include "black_scholes.hpp"
#include <iostream>

int main() {
    double S {100.0}, // underlying asset price $100.0
           K {100.0}, // strike price = $100.0
           r {0.05} , // risk-free rate = 5%
           v {0.2}  , // volatility in price of underlying asset = 20%
           T {1.0}  ; // time to maturity = 1 year 

    std::cout << "\nSpot price = "     << S << std::endl;
    std::cout << "Strike price = "   << K << std::endl;
    std::cout << "Risk-free rate = " << r << std::endl;
    std::cout << "Volatility = "     << v << std::endl;
    std::cout << "Time to expiry = " << T << std::endl;

    std::cout << std::endl << "Using the closed-form solutions...\n";

    std::cout << "Price of call option = " << calculate_price(true, S, K, r, v, T) << std::endl;
    std::cout << "Call delta = " << calculate_delta(true, S, K, r, v, T) << std::endl;
    std::cout << "Call gamma = " << calculate_gamma(true, S, K, r, v, T) << std::endl;
    std::cout << "Call vega = " << calculate_vega(true, S, K, r, v, T) << std::endl;
    std::cout << "Call theta = " << calculate_theta(true, S, K, r, v, T) << std::endl;
    std::cout << "Call rho = " << calculate_rho(true, S, K, r, v, T) << std::endl;

    std::cout << std::endl;
    std::cout << "Price of put option = "  << calculate_price(false, S, K, r, v, T)  << std::endl;
    std::cout << "Put delta = " << calculate_delta(false, S, K, r, v, T) << std::endl;
    std::cout << "Put gamma = " << calculate_gamma(false, S, K, r, v, T) << std::endl;
    std::cout << "Put vega = " << calculate_vega(false, S, K, r, v, T) << std::endl;
    std::cout << "Put theta = " << calculate_theta(false, S, K, r, v, T) << std::endl;
    std::cout << "Put rho = " << calculate_rho(false, S, K, r, v, T) << std::endl;

    return 0;
}