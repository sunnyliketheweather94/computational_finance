#ifndef __VANILLA_OPTION_CPP__
#define __VANILLA_OPTION_CPP__


#include "vanilla_option.hpp"
#include <cmath>


// computes the normal CDF uptil x
double normalCDF(double x) {
    return std::erfc(- x / std::sqrt(2.0)) / 2.0;
}


void VanillaOption::init() {
    K = 100.0; // strike price = $100.0
    r = 0.05; // risk-free rate = 5%
    T = 1.0; // time to maturity = 1 year
    S = 100.0; // underlying asset price is $100.0
    sigma = 0.2; // volatility of underlying asset price is 20%
}

void VanillaOption::copy(const VanillaOption& rhs) {
    K = rhs.get_K();
    r = rhs.get_r();
    T = rhs.get_T();
    S = rhs.get_S();
    sigma = rhs.get_sigma();
}

void VanillaOption::VanillaOption() {
    init();
}

void VanillaOption::VanillaOption(const double& K_, 
                             const double& r_, 
                             const double& T_,
                             const double& S_, 
                             const double& sig_)
    : K(K_), r(r_), T(T_), S(S_), sigma(sig_) {
// do nothing
}

void VanillaOption::VanillaOption(const VanillaOption& rhs) {
    copy(rhs);
}

VanillaOption& VanillaOption::operator=(const VanillaOption& rhs) {
    if(this == &rhs) { // if attempting to copy the same VanillaOption object
        return *this;
    }

    copy(rhs);

    return *this;
}

void VanillaOption::~VanillaOption() {
    // do nothing since compiler cleans up the destruction process for us
    // because we haven't declared anything on the heap.
}

double VanillaOption::get_K()     const { return K; }
double VanillaOption::get_r()     const { return r; }
double VanillaOption::get_T()     const { return T; }
double VanillaOption::get_S()     const { return S; }
double VanillaOption::get_sigma() const { return sigma; }

double calc_call_price() const {
    double sigma_sqrtT { sigma * std::sqrt(T) };
    double d_1 { (std::log(S / K) + T * (r + sigma * sigma / 2.0)) / sigma_sqrtT };
    double d_2 { d_1 - sigma_sqrtT };

    return S * normalCDF(d_1) - K * std::exp(- r * T) * normalCDF(d_2);
}

double calc_put_price() const {
    double sigma_sqrtT { sigma * std::sqrt(T) };
    double d_1 { (std::log(S / K) + T * (r + sigma * sigma / 2.0)) / sigma_sqrtT };
    double d_2 { d_1 - sigma_sqrtT };

    return K * std::exp(- r * T) * normalCDF(- d_2) - S * normalCDF(- d_1);
}





#endif