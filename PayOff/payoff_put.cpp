#ifndef __PAYOFF_PUT_CPP__
#define __PAYOFF_PUT_CPP__

#include "payoff.h"
#include "payoff_put.h"


PayOffPut::PayOffPut(const double K_) const : K(K_) {}
PayOffPut::~PayOffPut() {}
double PayOffPut::operator() (const double S) const {
    return std::max(K - S, 0.0); // payoff function for european call option
}

#endif