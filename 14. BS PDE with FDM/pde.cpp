#ifndef __PDE_CPP__
#define __PDE_CPP__ 

#include "pde.hpp"
#include <cmath>

ConvectionDiffusionPDE::~ConvectionDiffusionPDE() {}

BlackScholesPDE::BlackScholesPDE(VanillaOption* o) : option(o) {}
BlackScholesPDE::~BlackScholesPDE() {
    delete option;
}

double BlackScholesPDE::diff_coeff(double t, double x) const {
    double vol = option->sigma;

    return 0.5 * vol * vol * x * x;
}

double BlackScholesPDE::conv_coeff(double t, double x) const {
    return (option->r) * x;
}

double BlackScholesPDE::zero_coeff(double t, double x) const {
    return -(option->r);
}

double BlackScholesPDE::source_coeff(double t, double x) const {
    return 0.0;
}

double BlackScholesPDE::boundary_left (double t, double x) const {
    return 0.0; // specific for call option
}

double BlackScholesPDE::boundary_right(double t, double x) const {
    return x - (option->K) * std::exp(-(option->r) * ((option->T) - t));
}

double BlackScholesPDE::init_cond(double x) const {
    return (option->pay_off)->operator()(x);
}

#endif