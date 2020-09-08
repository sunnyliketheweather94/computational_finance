#include "analytical_option_pricing.hpp"
#include <iostream>
#include <iomanip>



int main() {
    double S {100.0}, // underlying asset price $100.0
           K {100.0}, // strike price = $100.0
           r {0.05} , // risk-free rate = 5%
           v {0.2}  , // volatility in price of underlying asset = 20%
           T {1.0}  ; // time to maturity = 1 year 

    double call { call_price(S, K, r, v, T) },
            put {  put_price(S, K, r, v, T) };

    std::cout << "Spot price = "     << S << std::endl;
    std::cout << "Strike price = "   << K << std::endl;
    std::cout << "Risk-free rate = " << r << std::endl;
    std::cout << "Volatility = "     << v << std::endl;
    std::cout << "Time to expiry = " << T << std::endl;

    std::cout << std::endl;

    std::cout << "Price of call option = " << call << std::endl;
    std::cout << "Price of put option = "  << put  << std::endl;

    return 0;
}