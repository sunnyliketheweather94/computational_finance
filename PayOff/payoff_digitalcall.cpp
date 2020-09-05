#ifndef __PAYOFF_DIGITALCALL_CPP__
#define __PAYOFF_DIGITALCALL_CPP__

#include "payoff.h"
#include "payoff_digitalcall.h"

double heaviside(const double x) const {
    return (x >= 0.0) ? 1.0 : 0.0;
}

PayOffDigitalCall::PayOffDigitalCall(const double K_) const : K(K_) {}
PayOffDigitalCall::~PayOffDigitalCall() {}
double PayOffDigitalCall::operator() (const double S) const {
    return heaviside(S - K, 0.0); // payoff function for european call option
}

#endif