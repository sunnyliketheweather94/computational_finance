#ifndef __PAYOFF_H__
#define __PAYOFF_H__

#include <algorithm>


class PayOff {
public:
    PayOff() {}; // do nothing
    virtual ~PayOff() {};

    // pure virtual method; will be overridden in the superclasses
    virtual double operator() const = 0 {};
};



#endif