#ifndef __VANILLA_OPTION_CPP__
#define __VANILLA_OPTION_CPP__ 

#include "vanilla_option.hpp"

VanillaOption::VanillaOption()  {}
VanillaOption::~VanillaOption() {}

VanillaOption::VanillaOption(double K_, double r_, double T_, double v_, PayOff* p)
: pay_off(p), K(K_), r(r_), T(T_), sigma(v_) {}

#endif