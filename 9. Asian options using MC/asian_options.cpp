#ifndef __ASIAN_OPTION_CPP__
#define __ASIAN_OPTION_CPP__

#include "asian_options.hpp"
#include "pay_off.hpp"
#include <vector>
#include <numeric> // need std::accumulate

using vector = std::vector<double>;

// Asian option..
AsianOption::AsianOption(Payoff* p) : pay_off(p) {
    // do nothing
}

AsianOption::~AsianOption() {
    // do nothing
}

// arithmetic Asian option
AsianOptionArithmetic::AsianOptionArithmetic(Payoff* p) : AsianOption(p) {
    // do nothing
}

double AsianOptionArithmetic::payoff_price(const vector& spot_prices) const {
    unsigned n = spot_prices.size();
    double sum = std::accumulate(spot_prices.begin(), spot_prices.end(), 0.0);
    double arithmetic_mean = sum / (double) n;

    return (*pay_off)(arithmetic_mean);
}



// geometric Asian option
AsianOptionGeometric::AsianOptionGeometric(Payoff* p) : AsianOption(p) {
    // do nothing
}

double AsianOptionGeometric::payoff_price(const vector& spot_prices) const {
    unsigned n = spot_prices.size();

    auto log_sum = [](double& a, const double& b) { a += std::log(b); return a; };

    // computes the log_sum of all elements in the spot_prices vector
    double sum = std::accumulate(spot_prices.begin(), spot_prices.end(), std::log(spot_prices.at(0)), log_sum);
    double geom_mean = std::exp(sum / (double) n);

    return (*pay_off)(geom_mean);
}


#endif