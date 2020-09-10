#ifndef __BLACK_SCHOLES_CPP__
#define __BLACK_SCHOLES_CPP__

#include "bs_prices.hpp"
#include "black_scholes.hpp"

BlackScholes::BlackScholes(double S_, double K_, double r_, double T_, bool call_)
    : S(S_), K(K_), r(r_), T(T_), call(call_) {
    // do nothing
}

double BlackScholes::option_price(double sigma) const {
    return calculate_price(call, S, K, r, sigma, T);
}

double BlackScholes::option_vega(double sigma) const {
    return calculate_vega(call, S, K, r, sigma, T);
}


#endif