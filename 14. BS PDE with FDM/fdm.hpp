#ifndef __FDM_HPP__
#define __FDM_HPP__ 

#include "pde.hpp"
#include <vector>

using vector = std::vector<double>;

class FDMBase {
protected:
    ConvectionDiffusionPDE* pde;

    // space discretization
    double x_dom; // spatial extent = [0.0, x_dom]
    unsigned long J; // number of spatial differencing points
    double dx; // spatial step size
    vector x_values; // stores coordinates of the x-dimension

    // time discretization
    double t_dom; // temporal extent [0.0, t_dom]
    unsigned long N; // number of temporal differencing points
    double dt; // temporal step size

    double prev_t, curr_t; // previous and current times

    double alpha, beta, gamma; // differencing coefficients

    vector new_result; // new solutions (becomes N + 1)
    vector old_result; // old solutions (becomes N)

    FDMBase(double, unsigned long, double, unsigned long, ConvectionDiffusionPDE*);

    virtual void calculate_step_size() = 0;
    virtual void set_init_conditions() = 0;
    virtual void calculate_boundary_conditions() = 0;
    virtual void calculate_inner_domain() = 0;


public:
    virtual void step_march() = 0;    
};

class FDM_Euler_Explicit : public FDMBase {
protected:
    void calculate_step_size();
    void set_init_conditions();
    void calculate_boundary_conditions();
    void calculate_inner_domain();

public:
    FDM_Euler_Explicit(double, unsigned long, double, unsigned long, ConvectionDiffusionPDE*);
    void step_march();
};

#endif