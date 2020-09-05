#ifndef __PAYOFF_CALL_H__
#define __PAYOFF_CALL_H__

#include "payoff.h"

class PayOffCall : public PayOff {
private:
    double K; // strike price

public:
    PayOffCall(const double K_) {}; // no default constructor is made
    virtual ~PayOffCall() {};

    // not pure-virtual anymore.. payoff is max(S - K, 0)
    virtual double operator() (const double S) const;
};


#endif