#ifndef __PAYOFF_PUT_H__
#define __PAYOFF_PUT_H__

#include "payoff.h"

class PayOffPut : public PayOff {
private:
    double K; // strike price

public:
    PayOffPut(const double K_) {}; // no default constructor is made
    virtual ~PayOffPut() {};

    // not pure-virtual anymore.. payoff is max(K - S, 0)
    virtual double operator() (const double S) const; // S = asset price
};


#endif