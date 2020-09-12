#ifndef __PAYOFF_CPP__
#define __PAYOFF_CPP__


#include "pay_off.hpp"

// ==================== //
//     Payoff Class     //
// ==================== //

Payoff::Payoff() {
    // do nothing
}

// double Payoff::operator()(const double& S) {
//     // do nothing
// }


// ========================= //
//     Payoff Call Class     //
// ========================= //

PayoffCall::PayoffCall(const double& K_) {
    K = K_; // do nothing else
}

double PayoffCall::operator()(const double& S) {
    return std::max(S - K, 0.0);
}

// ======================== //
//     Payoff Put Class     //
// ======================== //

PayoffPut::PayoffPut(const double& K_) : K(K_) {
    // do nothing else
}

double PayoffPut::operator()(const double& S) const {
    return std::max(K - S, 0.0);
}

#endif