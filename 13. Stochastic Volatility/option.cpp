#ifndef __OPTION_CPP__
#define __OPTION_CPP__

#include "option.hpp"

Option::Option(double K_, double r_, double T_, Payoff* p)
: payoff(p), K(K_), r(r_), T(T_) {}

Option::~Option() {}


#endif