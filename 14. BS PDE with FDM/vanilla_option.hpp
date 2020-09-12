#ifndef __VANILLA_OPTION_HPP__
#define __VANILLA_OPTION_HPP__ 

#include "payoff.hpp"

class VanillaOption {
public:
    PayOff* pay_off;
    double K;
    double r;
    double T;
    double sigma;

    VanillaOption();
    VanillaOption(double, double, double, double, PayOff*);
    virtual ~VanillaOption();
};

#endif