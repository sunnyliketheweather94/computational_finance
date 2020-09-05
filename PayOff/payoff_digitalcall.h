#ifndef __PAYOFF_DIGITAL_CALL_H__
#define __PAYOFF_DIGITAL_CALL_H__

#include "payoff.h"

double heaviside(const double x) const;


class PayOffDigitalCall : public PayOff {
private:
    double K; // strike price

public:
    PayOffDigitalCall(const double K_) const;
    virtual ~PayOffDigitalCall();

    // use the heaviside function. 
    // payoff = heaviside(S - K) where S = final spot price
    virtual double operator()(const double S) const;
};



#endif