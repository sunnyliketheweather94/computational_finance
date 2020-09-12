#ifndef __PAYOFF_CPP__
#define __PAYOFF_CPP__ 

#include "payoff.hpp"

PayOff::PayOff()  {}
PayOff::~PayOff() {}

/////// Payoff CALL

PayOffCall::PayOffCall(const double& K_) : K(K_) {}
PayOffCall::~PayOffCall() {}

double PayOffCall::operator()(const double& S) const {
    return std::max(S - K, 0.0);
}

/////// Payoff PUT 

PayOffPut::PayOffPut(const double& K_) : K(K_) {}
PayOffPut::~PayOffPut() {}

double PayOffPut::operator()(const double& S) const {
    return std::max(K - S, 0.0);
}

#endif