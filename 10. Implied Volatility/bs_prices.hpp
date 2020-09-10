#ifndef __BS_PRICES_HPP__
#define __BS_PRICES_HPP__

#define _USE_MATH_DEFINES // get mathematical constants
#include <cmath>

// computes the normal PDF of x
double normal_pdf(double x) {
    return (1 / std::sqrt(2 * M_PI)) * std::exp(- 0.5 * x * x);
}

// computes the normal CDF uptil x
double normal_cdf(double x) {
    return std::erfc(- x / std::sqrt(2.0)) / 2.0;
}

/*
Here we use the following variables:
------------------------------------
S = spot price
K = strike price
r = rise-free rate or rate of interest
v = volatility in the underlying asset's price
T = time to maturity
*/

// calculates d_j for j in {1, 2}.
// used in the final formula for the price of put or call option
double d_j(const int& j, const double& S, const double& K, 
           const double& r, const double& v, const double& T) {
    return (std::log(S / K) + (r + (std::pow(-1, j - 1)) * 0.5 * v * v) * T)
            / (v * std::pow(T, 0.5));
}

// computes price of an option
double calculate_price(const bool& call, const double& S, const double& K, 
                       const double& r,  const double& v, const double& T) {
    // if call == true --> compute price of call option
    // otherwise           compute price of put  option
    double a = (call 
                    ? S * normal_cdf(d_j(1, S, K, r, v, T)) 
                    : - S * normal_cdf(- d_j(1, S, K, r, v, T)));

    double b = (call 
                ? - K * std::exp(- r * T) * normal_cdf(d_j(2, S, K, r, v, T)) 
                : K * std::exp(- r * T) * normal_cdf( - d_j(2, S, K, r, v, T)));

    return a + b;
}


// computes the vega of an option
double calculate_vega(const bool& call, const double& S, const double& K, 
                       const double& r,  const double& v, const double& T) {
    // if call == true --> compute price of call option
    // otherwise           compute price of put  option
    return S * std::sqrt(T) * normal_pdf(d_j(1, S, K, r, v, T));
}

#endif