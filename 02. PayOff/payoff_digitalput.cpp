#ifndef __PAYOFF_DIGITALPUT_CPP__
#define __PAYOFF_DIGITALPUT_CPP__

#include "payoff.h"
#include "payoff_digitalput.h"

double heaviside(const double x) const {
    return (x >= 0.0) ? 1.0 : 0.0;
}

PayOffDigitalPut::PayOffDigitalPut(const double K_) const : K(K_) {}
PayOffDigitalPut::~PayOffDigitalPut() {}
double PayOffDigitalPut::operator() (const double S) const {
    return heaviside(K - S, 0.0); // payoff function for european call option
}

#endif