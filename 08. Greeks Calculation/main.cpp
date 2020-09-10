#include "black_scholes.hpp"
#include <iostream>

int main() {
    double S {100.0}, // underlying asset price $100.0
           K {100.0}, // strike price = $100.0
           r {0.05} , // risk-free rate = 5%
           v {0.2}  , // volatility in price of underlying asset = 20%
           T {1.0}  ; // time to maturity = 1 year 

    double delta = 0.0001; // increment for the FDM
    int num_iter = 10000;

    std::cout << "\nSpot price = "     << S << std::endl;
    std::cout << "Strike price = "     << K << std::endl;
    std::cout << "Risk-free rate = "   << r << std::endl;
    std::cout << "Volatility = "       << v << std::endl;
    std::cout << "Time to expiry = "   << T << std::endl;

    std::cout << std::endl << "Using the closed-form solutions to compute the prices and the Greeks...\n";

    std::cout << "Price of call option = " << calculate_price(true, S, K, r, v, T) << std::endl;
    std::cout << "Call delta = "           << calculate_delta(true, S, K, r, v, T) << std::endl;
    std::cout << "Call gamma = "           << calculate_gamma(true, S, K, r, v, T) << std::endl;
    std::cout << "Call vega = "            <<  calculate_vega(true, S, K, r, v, T) << std::endl;
    std::cout << "Call theta = "           << calculate_theta(true, S, K, r, v, T) << std::endl;
    std::cout << "Call rho = "             <<   calculate_rho(true, S, K, r, v, T) << std::endl;

    std::cout << std::endl;
    std::cout << "Price of put option = "  << calculate_price(false, S, K, r, v, T)  << std::endl;
    std::cout << "Put delta = "            << calculate_delta(false, S, K, r, v, T) << std::endl;
    std::cout << "Put gamma = "            << calculate_gamma(false, S, K, r, v, T) << std::endl;
    std::cout << "Put vega = "             <<  calculate_vega(false, S, K, r, v, T) << std::endl;
    std::cout << "Put theta = "            << calculate_theta(false, S, K, r, v, T) << std::endl;
    std::cout << "Put rho = "              <<   calculate_rho(false, S, K, r, v, T) << std::endl;

    /////////////////////////////////////////////////////////////////////////////////////////////

    // std::cout << std::endl << "Using the analytical solutions to compute prices and finite difference methods to compute the Greeks...\n";

    // std::cout << "Price of call option = " << calculate_price(true, S, K, r, v, T)        << std::endl;
    // std::cout << "Call delta = "           <<       delta_fdm(true, S, K, r, v, T, delta) << std::endl;
    // std::cout << "Call gamma = "           <<       gamma_fdm(true, S, K, r, v, T, delta) << std::endl;
    // std::cout << "Call vega = "            <<        vega_fdm(true, S, K, r, v, T, delta) << std::endl;
    // std::cout << "Call theta = "           <<       theta_fdm(true, S, K, r, v, T, delta) << std::endl;
    // std::cout << "Call rho = "             <<         rho_fdm(true, S, K, r, v, T, delta) << std::endl;

    // std::cout << std::endl;
    // std::cout << "Price of put option = " << calculate_price(false, S, K, r, v, T)        << std::endl;
    // std::cout << "Put delta = "           <<       delta_fdm(false, S, K, r, v, T, delta) << std::endl;
    // std::cout << "Put gamma = "           <<       gamma_fdm(false, S, K, r, v, T, delta) << std::endl;
    // std::cout << "Put vega = "            <<        vega_fdm(false, S, K, r, v, T, delta) << std::endl;
    // std::cout << "Put theta = "           <<       theta_fdm(false, S, K, r, v, T, delta) << std::endl;
    // std::cout << "Put rho = "             <<         rho_fdm(false, S, K, r, v, T, delta) << std::endl;

    //////////////////////////////////////////////////////////////////////////////////////////////////

    std::cout << std::endl << "Using Monte Carlo to compute the prices and finite difference methods to compute the Greeks...\n";

    double x {0.0}, y {0.0}, z {0.0};
    monte_carlo(num_iter, true, 1, S, K, r, v, T, delta, x, y, z);

    std::cout << "Price of call option = " << y << std::endl;
    std::cout << "Call delta = "           << delta_mc(num_iter, true, S, K, r, v, T, delta) << std::endl;
    std::cout << "Call gamma = "           << gamma_mc(num_iter, true, S, K, r, v, T, delta) << std::endl;
    std::cout << "Call vega = "            <<  vega_mc(num_iter, true, S, K, r, v, T, delta) << std::endl;
    std::cout << "Call theta = "           << theta_mc(num_iter, true, S, K, r, v, T, delta) << std::endl;
    std::cout << "Call rho = "             <<   rho_mc(num_iter, true, S, K, r, v, T, delta) << std::endl;

    std::cout << std::endl;
    monte_carlo(num_iter, false, 1, S, K, r, v, T, delta, x, y, z);

    std::cout << "Price of put option = " << y << std::endl;
    std::cout << "Put delta = "           << delta_mc(num_iter, false, S, K, r, v, T, delta) << std::endl;
    std::cout << "Put gamma = "           << gamma_mc(num_iter, false, S, K, r, v, T, delta) << std::endl;
    std::cout << "Put vega = "            <<  vega_mc(num_iter, false, S, K, r, v, T, delta) << std::endl;
    std::cout << "Put theta = "           << theta_mc(num_iter, false, S, K, r, v, T, delta) << std::endl;
    std::cout << "Put rho = "             <<   rho_mc(num_iter, false, S, K, r, v, T, delta) << std::endl;

    return 0;
}