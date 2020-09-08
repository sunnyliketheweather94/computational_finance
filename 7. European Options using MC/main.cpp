#include "analytical_option_pricing.hpp"
#include "numerical_option_pricing.hpp"
#include <iostream>
#include <iomanip>



int main() {
    double S {100.0}, // underlying asset price $100.0
           K {100.0}, // strike price = $100.0
           r {0.05} , // risk-free rate = 5%
           v {0.2}  , // volatility in price of underlying asset = 20%
           T {1.0}  ; // time to maturity = 1 year 

    int num_iterations = 1000000;

    double call_mc = monte_carlo(num_iterations, true,  S, K, r, v, T);
    double put_mc  = monte_carlo(num_iterations, false, S, K, r, v, T);

    double call_an = call_price(S, K, r, v, T),
           put_an  =  put_price(S, K, r, v, T);

    std::cout << "\nSpot price = "     << S << std::endl;
    std::cout << "Strike price = "   << K << std::endl;
    std::cout << "Risk-free rate = " << r << std::endl;
    std::cout << "Volatility = "     << v << std::endl;
    std::cout << "Time to expiry = " << T << std::endl;

    std::cout << std::endl << "Using the closed-form solutions...\n";

    std::cout << "Price of call option = " << call_an << std::endl;
    std::cout << "Price of put option = "  << put_an  << std::endl;

    std::cout << std::endl << "Using the Monte Carlo method...\n";

    std::cout << "Price of call option = " << call_mc << std::endl;
    std::cout << "Price of put option = "  << put_mc  << std::endl;


    return 0;
}