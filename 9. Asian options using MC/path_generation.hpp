#ifndef __PATH_GENERATION_HPP__
#define __PATH_GENERATION_HPP__

#include <vector>
#include <cmath>
#include <random>

using vector = std::vector<double>;

double normal_generator(const double& mu = 0.0, const double& sigma = 1.0) {
    // mu = mean of the Normal distribution
    // sigma = standard deviation of the Normal distribution

    std::random_device rd;  // will be used for seeding the Mersenne twister engine generator
    std::mt19937 gen(rd()); // Standard Mersenne twister generator
    std::normal_distribution<double> dis(mu, sigma); 

    return dis(gen);
}


void CalcPathOfSpotPrices(vector& spot_prices, // asset path
                          const double& r,     // risk-free rate
                          const double& v,     // volatility of underlying asset
                          const double& T) {    // time to maturity
    double dt = T / (double) spot_prices.size();
    double drift = std::exp(dt * (r - 0.5 * v * v));
    double vol = v * std::sqrt(dt);

    for(int i = 1; i < spot_prices.size(); ++i) {
        double gauss = normal_generator();
        spot_prices.at(i) = spot_prices.at(i - 1) * drift * std::exp(vol * gauss);
    }
}

#endif