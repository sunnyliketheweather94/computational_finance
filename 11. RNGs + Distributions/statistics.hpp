#ifndef __STATISTICS_HPP__
#define __STATISTICS_HPP__

#include <vector>
#include <cmath>

class StatisticalDistribution {
public:
    StatisticalDistribution();          // default constructor
    virtual ~StatisticalDistribution(); // destructor

    // distribution functions
    virtual double     pdf(const double& x)        const = 0;
    virtual double     cdf(const double& x)        const = 0;
    virtual double inv_cdf(const double& quantile) const = 0; // the quantile function

    // descriptive statistics
    virtual double mean()  const = 0;
    virtual double var()   const = 0;
    virtual double stdev() const = 0;

    // obtain a sequence of random draws from this distribution
    virtual void random_draws(const std::vector<double>& uniform_draws, 
                                    std::vector<double>& stat_draws) = 0;
};


class StandardNormal : public StatisticalDistribution {
public:
    StandardNormal();
    virtual ~StandardNormal();

    // distribution functions
    virtual double     pdf(const double& x)        const;
    virtual double     cdf(const double& x)        const;
    virtual double inv_cdf(const double& quantile) const; // the quantile function

    // descriptive statistics
    virtual double mean()  const; // = 0.0
    virtual double var()   const; // = 1.0
    virtual double stdev() const; // = 1.0

    // obtain a sequence of random draws from this distribution
    virtual void random_draws(const std::vector<double>& uniform_draws, 
                                    std::vector<double>& stat_draws);
};


#endif