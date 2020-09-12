#ifndef __CORRELATED_SND_HPP__
#define __CORRELATED_SND_HPP__

#include "statistics.hpp"

using vector = std::vector<double>;

class CorrelatedSND : public StandardNormal {
protected:
    double rho; // correlation coefficient/matrix
    const vector* uncorr_draws;
    virtual void correlation_calc(vector& dist_draws); // computes correlation with dist_draws

public:
    CorrelatedSND(const double rho_, const vector* draws_);
    virtual ~CorrelatedSND();

    virtual void random_draws(const vector& uniform, vector& dist);
};



#endif