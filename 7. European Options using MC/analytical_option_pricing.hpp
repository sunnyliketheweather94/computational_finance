#ifndef __ANALYTICAL_OPTION_PRICING_HPP__
#define __ANALYTICAL_OPTION_PRICING_HPP__

#include <cmath>


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

// computes price of a call option
double call_price(const double& S, const double& K, const double& r, 
                  const double& v, const double& T) {
    return S * normal_cdf(d_j(1, S, K, r, v, T)) 
         - K * std::exp(- r * T) * normal_cdf(d_j(2, S, K, r, v, T));
}

// computes price of a put option
double put_price(const double& S, const double& K, const double& r, 
                 const double& v, const double& T) {
    return - S * normal_cdf(- d_j(1, S, K, r, v, T)) 
           + K * std::exp(- r * T) * normal_cdf( - d_j(2, S, K, r, v, T));
}


#endif