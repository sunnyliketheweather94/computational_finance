#ifndef __NUMERICAL_OPTION_PRICING_HPP__
#define __NUMERICAL_OPTION_PRICING_HPP__

#include <cmath>
#include <algorithm>
#include <random>
#include <iostream>
#include <iomanip>


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

double monte_carlo(const int& iter, const bool& call, const double& S, 
                   const double& K, const double& r, const double& sigma, 
                   const double& T) {
    // if call = True ---> compute call option price
    // otherwise           compute put  option price
    double S_curr  {0.0};
    double total_payoff {0.0};

    std::cout << "Calculating " << (call ? "call" : "put") << " price..." << std::endl;

    for(int i = 0; i < iter; ++i) {
        S_curr = S * std::exp(normal_generator((r - 0.5 * sigma * sigma) * T, sigma * std::sqrt(T)));

        total_payoff += (call ? std::max(S_curr - K, 0.0) : std::max(K - S_curr, 0.0));
    }

    double price = total_payoff / (double) iter; // average payoff at maturity

    return std::exp(- r * T) * price; // discounted to become the price of option
}



#endif