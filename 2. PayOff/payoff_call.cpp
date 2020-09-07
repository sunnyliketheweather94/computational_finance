#ifndef __PAYOFF_CALL_CPP__
#define __PAYOFF_CALL_CPP__

#include "payoff.h"
#include "payoff_call.h"


PayOffCall::PayOffCall(const double K_) const : K(K_) {}
PayOffCall::~PayOffCall() {}
double PayOffCall::operator() (const double S) const {
    return std::max(S - K, 0.0); // payoff function for european call option
}

#endif