#ifndef __PAYOFF_DOUBLEDIGITAL_CPP__
#define __PAYOFF_DOUBLEDIGITAL_CPP__

#include "payoff.h"
#include "payoff_doubledigital.h"

PayOffDoubleDigital::PayOffDoubleDigital(const double U_, const double D_) const : U(U_), D(D_) {}
PayOffDoubleDigital::~PayOffDoubleDigital() {}
double PayOffDoubleDigital::operator() (const double S) const {
    return (D <= S and S <= U) ? 1.0 : 0.0; // payoff function
}

#endif