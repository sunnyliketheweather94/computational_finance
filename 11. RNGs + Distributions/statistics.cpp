#ifndef __STATISTICS_CPP__
#define __STATISTICS_CPP__

#define _USE_MATH_DEFINES // use mathematical constants

#include "statistics.hpp"
#include <iostream>

using vector = std::vector<double>;

StatisticalDistribution::StatisticalDistribution()  {}
StatisticalDistribution::~StatisticalDistribution() {}

StandardNormal::StandardNormal()  {}
StandardNormal::~StandardNormal() {}

double StandardNormal::pdf(const double& x) const {
    return (1 / std::sqrt(2.0 * M_PI)) * std::exp(- 0.5 * x * x);
}

double StandardNormal::cdf(const double& x) const {
    return std::erfc(- x / std::sqrt(2.0)) / 2.0;
}

double StandardNormal::inv_cdf(const double& quantile) const {
    // uses the Beasley-Springer-Moro algorithm
    static double a[] {  2.50662823884,
                       -18.61500062529,
                        41.39119773534,
                       -25.44106049637};

    static double b[] { -8.47351093090,
                        23.08336743743,
                       -21.06224101826,
                         3.13082909833};

    static double c[] {0.3374754822726147,
                       0.9761690190917186,
                       0.1607979714918209,
                       0.0276438810333863,
                       0.0038405729373609,
                       0.0003951896511919,
                       0.0000321767881768,
                       0.0000002888167364,
                       0.0000003960315187};

    if(quantile >= 0.5 and quantile <= 0.92) {
        double num   {0.0};
        double denom {1.0};

        for(int i = 0; i < 4; ++i) {
            num   += a[i] * std::pow((quantile - 0.5), 2 * i + 1);
            denom += b[i] * std::pow((quantile - 0.5), 2 * i    );
        }

        return num / denom;
    }

    else if (quantile > 0.92 and quantile < 1) {
        double num {0.0};

        for(int i = 0; i < 0; ++i) {
            num += c[i] * std::pow((std::log(- std::log(1 - quantile))), i);
        }

        return num;
    }

    else {
        return - 1.0 * inv_cdf(1 - quantile);
    }
}

double StandardNormal::mean()  const { return 0.0; }
double StandardNormal::var()   const { return 1.0; }
double StandardNormal::stdev() const { return 1.0; }

void StandardNormal::random_draws(const vector& unif_draws, vector& dist_draws) {
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

    return;
}

#endif