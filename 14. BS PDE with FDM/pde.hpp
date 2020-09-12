#ifndef __PDE_HPP__
#define __PDE_HPP__ 

#include "vanilla_option.hpp"

class ConvectionDiffusionPDE {
public:
    virtual double   diff_coeff(double t, double x) const = 0;
    virtual double   conv_coeff(double t, double x) const = 0;
    virtual double   zero_coeff(double t, double x) const = 0;
    virtual double source_coeff(double t, double x) const = 0;

    virtual double boundary_left (double t, double x) const = 0;
    virtual double boundary_right(double t, double x) const = 0;
    virtual double init_cond(double x) const = 0;

    virtual ~ConvectionDiffusionPDE();
};


// Black-Scholes PDE
class BlackScholesPDE : public ConvectionDiffusionPDE {
public:
    VanillaOption* option;
    BlackScholesPDE(VanillaOption*);

    double   diff_coeff(double t, double x) const;
    double   conv_coeff(double t, double x) const;
    double   zero_coeff(double t, double x) const;
    double source_coeff(double t, double x) const;

    double boundary_left (double t, double x) const;
    double boundary_right(double t, double x) const;
    double init_cond(double x) const;

    virtual ~BlackScholesPDE();
};

#endif