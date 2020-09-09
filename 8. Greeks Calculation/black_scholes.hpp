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

void monte_carlo(const int& iter, const bool& call, const int& choice, const double& S, 
                   const double& K, const double& r,  const double& sigma, 
                   const double& T, const double& delta,
                         double& price_Sm,double& price_S, double& price_Sp) {
    // if call = True ---> compute call option price
    // otherwise           compute put  option price
    double S_curr {0.0}, S_curr_m {0.0}, S_curr_p {0.0};
    double total_payoff_m {0.0}, total_payoff {0.0}, total_payoff_p {0.0};

    for(int i = 0; i < iter; ++i) {
        double gauss = normal_generator();

        double exp_gauss   {0.0};
        double exp_gauss_m {0.0};
        double exp_gauss_p {0.0};

        switch(choice) {
            case 1: // for delta
            case 2: // for gamma
                exp_gauss = std::exp((r - 0.5 * sigma * sigma) * T + sigma * std::sqrt(T) * gauss);

                S_curr_m = (S - delta) * exp_gauss;
                S_curr   =     S       * exp_gauss;
                S_curr_p = (S + delta) * exp_gauss;

                break;

            case 3: // for vega
                exp_gauss_m = std::exp(T * (r - 0.5 * (sigma - delta) * (sigma - delta)) + (sigma - delta) * std::sqrt(T) * gauss);
                exp_gauss   = std::exp(T * (r - 0.5 * (sigma        ) * (sigma        )) + (sigma        ) * std::sqrt(T) * gauss);
                exp_gauss_p = std::exp(T * (r - 0.5 * (sigma + delta) * (sigma + delta)) + (sigma + delta) * std::sqrt(T) * gauss);

                S_curr_m = S * exp_gauss_m;
                S_curr   = S * exp_gauss  ;
                S_curr_p = S * exp_gauss_p;

                break;

            case 4: // for theta
                exp_gauss_m = std::exp((T - delta) * (r - 0.5 * sigma * sigma) + sigma * std::sqrt(T - delta) * gauss);
                exp_gauss   = std::exp((T        ) * (r - 0.5 * sigma * sigma) + sigma * std::sqrt(T        ) * gauss);
                exp_gauss_p = std::exp((T + delta) * (r - 0.5 * sigma * sigma) + sigma * std::sqrt(T + delta) * gauss);

                S_curr_m = S * exp_gauss_m;
                S_curr   = S * exp_gauss  ;
                S_curr_p = S * exp_gauss_p;

                break;    

            case 5: // for rho
                exp_gauss_m = std::exp(T * ((r - delta) - 0.5 * sigma * sigma) + sigma * std::sqrt(T) * gauss);
                exp_gauss   = std::exp(T * ((r        ) - 0.5 * sigma * sigma) + sigma * std::sqrt(T) * gauss);
                exp_gauss_p = std::exp(T * ((r + delta) - 0.5 * sigma * sigma) + sigma * std::sqrt(T) * gauss);

                S_curr_m = S * exp_gauss_m;
                S_curr   = S * exp_gauss  ;
                S_curr_p = S * exp_gauss_p;

                break; 

            default:
                S_curr   = 0.0;
                S_curr_m = 0.0;   
                S_curr_p = 0.0;

                break;
        }

        total_payoff_m += (call ? std::max(S_curr_m - K, 0.0) : std::max(K - S_curr_m, 0.0));        
        total_payoff   += (call ?   std::max(S_curr - K, 0.0) : std::max(K - S_curr,   0.0));
        total_payoff_p += (call ? std::max(S_curr_p - K, 0.0) : std::max(K - S_curr_p, 0.0));
    }

    price_Sm = std::exp(- r * T) * total_payoff_m / (double) iter;
    price_S  = std::exp(- r * T) * total_payoff   / (double) iter;
    price_Sp = std::exp(- r * T) * total_payoff_p / (double) iter;
}

double delta_mc(const int& iter, const bool& call, double& S, 
                const double& K, const double& r, const double& sigma, 
                const double& T, const double& delta) {
    // if call = True ---> compute call option price
    // otherwise           compute put  option price
    double price_Sp {0.0}, price_S {0.0}, price_Sm {0.0};
    monte_carlo(iter, call, 1, S, K, r, sigma, T, delta, price_Sm, price_S, price_Sp);

    return (price_Sp - price_S) / delta;
}

double gamma_mc(const int& iter, const bool& call, double& S, 
                const double& K, const double& r, const double& sigma, 
                const double& T, const double& delta) {
    // if call = True ---> compute call option price
    // otherwise           compute put  option price
    double price_Sp {0.0}, price_S {0.0}, price_Sm {0.0};
    monte_carlo(iter, call, 2, S, K, r, sigma, T, delta, price_Sm, price_S, price_Sp);

    return (price_Sp - 2 * price_S + price_Sm) / (delta * delta);
}

double  vega_mc(const int& iter, const bool& call, double& S, 
                const double& K, const double& r, const double& sigma, 
                const double& T, const double& delta) {
    // if call = True ---> compute call option price
    // otherwise           compute put  option price
    double price_Sp {0.0}, price_S {0.0}, price_Sm {0.0};
    monte_carlo(iter, call, 3, S, K, r, sigma, T, delta, price_Sm, price_S, price_Sp);

    return (price_Sp - price_S) / delta;
}

double theta_mc(const int& iter, const bool& call, double& S, 
                const double& K, const double& r, const double& sigma, 
                const double& T, const double& delta) {
    // if call = True ---> compute call option price
    // otherwise           compute put  option price
    double price_Sp {0.0}, price_S {0.0}, price_Sm {0.0};
    monte_carlo(iter, call, 4, S, K, r, sigma, T, delta, price_Sm, price_S, price_Sp);

    return (price_Sp - price_S) / delta;
}

double   rho_mc(const int& iter, const bool& call, double& S, 
                const double& K, const double& r, const double& sigma, 
                const double& T, const double& delta) {
    // if call = True ---> compute call option price
    // otherwise           compute put  option price
    double price_Sp {0.0}, price_S {0.0}, price_Sm {0.0};
    monte_carlo(iter, call, 5, S, K, r, sigma, T, delta, price_Sm, price_S, price_Sp);

    return (price_Sp - price_S) / delta;
}


// ================================ //
//    FINITE DIFFERENCE METHODS     //
// ================================ //

double delta_fdm(const bool& call, const double& S, const double& K, 
                 const double& r,  const double& v, const double& T,
                 const double& delta_S) {
    // if call == true --> compute price of call option
    // otherwise           compute price of put  option
    return (calculate_price(call, S + delta_S, K, r, v, T) - calculate_price(call, S, K, r, v, T)) 
           / delta_S;
}

double  gamma_fdm(const bool& call, const double& S, const double& K, 
                  const double& r,  const double& v, const double& T,
                  const double& delta_S) {
    // if call == true --> compute price of call option
    // otherwise           compute price of put  option
    return (calculate_price(call, S + delta_S, K, r, v, T) - 2.0 * calculate_price(call, S, K, r, v, T) 
            + calculate_price(call, S - delta_S, K, r, v, T)) / (delta_S * delta_S);
}


double vega_fdm(const bool& call, const double& S, const double& K, 
                const double& r,  const double& v, const double& T,
                const double& delta_v) {
    // if call == true --> compute price of call option
    // otherwise           compute price of put  option
    return (calculate_price(call, S, K, r, v + delta_v, T) - calculate_price(call, S, K, r, v, T)) 
           / delta_v;
}

double theta_fdm(const bool& call, const double& S, const double& K, 
                 const double& r,  const double& v, const double& T,
                 const double& delta_T) {
    // if call == true --> compute price of call option
    // otherwise           compute price of put  option
    return (calculate_price(call, S, K, r, v, T + delta_T) - calculate_price(call, S, K, r, v, T)) 
           / delta_T;
}

double   rho_fdm(const bool& call, const double& S, const double& K, 
                 const double& r,  const double& v, const double& T,
                 const double& delta_r) {
    // if call == true --> compute price of call option
    // otherwise           compute price of put  option
    return (calculate_price(call, S, K, r + delta_r, v, T) - calculate_price(call, S, K, r, v, T)) 
           / delta_r;
}


#endif