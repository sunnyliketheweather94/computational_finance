#ifndef __OPTION_HPP__
#define __OPTION_HPP__

#include "pay_off.hpp"

class Option {
public:
    Payoff* payoff;
    double K;
    double r;
    double T;

    Option(double K, double r, double T, Payoff* p);
    virtual ~Option();
};


#endif