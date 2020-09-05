#ifndef __PAYOFF_DIGITAL_PUT_H__
#define __PAYOFF_DIGITAL_PUT_H__

#include "payoff.h"

double heaviside(const double x) {
    return (x >= 0.0) ? 1.0 : 0.0;
}


class PayOffDigitalPut : public PayOff {
private:
    double K; // strike price

public:
    PayOffDigitalPut(const double K_) const {};
    virtual ~PayOffDigitalPut();

    // use the heaviside function. 
    // payoff = heaviside(K - S) where S = final spot price
    virtual double operator()(const double S) const;
};



#endif