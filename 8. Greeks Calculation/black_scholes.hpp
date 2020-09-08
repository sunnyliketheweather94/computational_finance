#ifndef __BLACK_SCHOLES_HPP__
#define __BLACK_SCHOLES_HPP__

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <algorithm>
#include <random>

// ========================== //
//   ANALYTICAL FORMULAS      //
// ========================== //

double normal_pdf(double x) {
    return (1.0 / std::sqrt(2 * M_PI)) * std::exp(- 0.5 * x * x);
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

// computes price of a call option
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

double calculate_delta(const bool& call, const double& S, const double& K, 
                       const double& r,  const double& v, const double& T) {
    // if call == true --> compute price of call option
    // otherwise           compute price of put  option
    return (call ? normal_cdf(d_j(1, S, K, r, v, T)) : normal_cdf(d_j(1, S, K, r, v, T)) - 1);
}

double calculate_gamma(const bool& call, const double& S, const double& K, 
                       const double& r,  const double& v, const double& T) {
    // if call == true --> compute price of call option
    // otherwise           compute price of put  option
    return normal_pdf(d_j(1, S, K, r, v, T)) / (S * v * std::sqrt(T));
}

double calculate_vega(const bool& call, const double& S, const double& K, 
                      const double& r,  const double& v, const double& T) {
    // if call == true --> compute price of call option
    // otherwise           compute price of put  option
    return S * normal_pdf(d_j(1, S, K, r, v, T)) * std::sqrt(T);
}

double calculate_theta(const bool& call, const double& S, const double& K, 
                       const double& r,  const double& v, const double& T) {
    // if call == true --> compute price of call option
    // otherwise           compute price of put  option
    double a = - S * v * normal_pdf(d_j(1, S, K, r, v, T)) * 0.5 / std::sqrt(T);
    double b = r * K * std::exp(- r * T) * (call ? normal_cdf(d_j(2, S, K, r, v, T)) : normal_cdf(- d_j(2, S, K, r, v, T)));

    return (call ? a - b : a + b);
}

double calculate_rho(const bool& call, const double& S, const double& K, 
                     const double& r,  const double& v, const double& T) {
    // if call == true --> compute price of call option
    // otherwise           compute price of put  option
    double a = T * K * std::exp(- r * T) * (call ? normal_cdf(d_j(2, S, K, r, v, T)) : normal_cdf(- d_j(2, S, K, r, v, T)));

    return (call ? a : - a);
}


// ========================== //
//    MONTE CARLO METHODS     //
// ========================== //

double normal_generator(const double& mu = 0.0, const double& sigma = 1.0) {
    // mu = mean of the Normal distribution
    // sigma = standard deviation of the Normal distribution
    // uses the Box-Muller algorithm

    std::random_device rd;  // will be used for seeding the Mersenne twister engine generator
    std::mt19937 gen(rd()); // Standard Mersenne twister generator
    std::uniform_real_distribution<double> dis(-1.0, 1.0); 

    // generates two random numbers from Unif(0, 1) distribution
    double x {0.0}, y {0.0}, distance {0.0};

    do {
        x = dis(gen);
        y = dis(gen);

        distance = x * x + y * y;
    }while(distance >= 1.0 or distance == 0.0);

    // generates a N(0, 1) random number
    double random_number = x * std::sqrt(- 2 * std::log(distance) / distance);

    return mu + random_number * sigma;
}


#endif