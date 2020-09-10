#ifndef __PAYOFF_DOUBLE_DIGITAL_H__
#define __PAYOFF_DOUBLE_DIGITAL_H__

#include "payoff.h"

class PayOffDoubleDigital : public PayOff {
private:
    double U; // upper strike price
    double D; // lower strike price

public:
    PayOffDoubleDigital(const double U_, const double D_) const;
    virtual ~PayOffDoubleDigital();

    // payoff = 1 if D < S < U, = 0 otherwise
    virtual double operator()(const double S) const;
};


#endif