#ifndef __CORRELATED_SND_CPP__
#define __CORRELATED_SND_CPP__

#include "correlated_snd.hpp"
#include <iostream>
#include <cmath>

// using vector = std::vector<double>;

CorrelatedSND::CorrelatedSND(const double rho_, const vector* draws_) 
    : rho(rho_), uncorr_draws(draws_) {}

CorrelatedSND::~CorrelatedSND() {}

void CorrelatedSND::correlation_calc(vector& dist_draws) {
    for(int i = 0; i < dist_draws.size(); ++i) {
        dist_draws.at(i) = rho * uncorr_draws->at(i) + dist_draws.at(i) * std::sqrt(1 - rho * rho);
    }
}

void CorrelatedSND::random_draws(const vector& unif_draws, vector& dist_draws) {
    if(unif_draws.size() != dist_draws.size()) {
        std::cout << "Draw vectors are of unequal size." << std::endl;
        return;
    }

    if(unif_draws.size() % 2 != 0) {
        std::cout << "Uniform draw vector size is not an even number." << std::endl;
        return;
    }

    for(int i = 0; i < unif_draws.size() / 2; ++i) {
        dist_draws.at(2 * i) = std::sqrt(- 2.0 * std::log(unif_draws.at(2 * i)))
                             * std::sin(2 * M_PI * unif_draws.at(2 * i + 1));

        dist_draws.at(2 * i + 1) = std::sqrt(- 2.0 * std::log(unif_draws.at(2 * i)))
                             * std::cos(2 * M_PI * unif_draws.at(2 * i + 1));
    }

    correlation_calc(dist_draws);

    return;
}

#endif