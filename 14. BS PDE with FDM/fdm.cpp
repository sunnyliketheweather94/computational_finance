#ifndef __FDM_CPP__
#define __FDM_CPP__ 

#include "fdm.hpp"
#include <fstream>

FDMBase::FDMBase(double x_, unsigned long j, double t_, unsigned long n, ConvectionDiffusionPDE* p)
: pde(p), x_dom(x_), J(j), t_dom(t_), N(n) {}

FDM_Euler_Explicit::FDM_Euler_Explicit(double x_, unsigned long j, double t_, unsigned long n, ConvectionDiffusionPDE* p)
: FDMBase(x_, j, t_, n, p) {
    calculate_step_size();
    set_init_conditions();
}

void FDM_Euler_Explicit::calculate_step_size() {
    dx = x_dom / (double) (J - 1);
    dt = t_dom / (double) (N - 1);
}

void FDM_Euler_Explicit::set_init_conditions() {
    // spatial settings
    double curr_spot = 0.0;

    old_result.resize(J, 0.0);
    new_result.resize(J, 0.0);

    x_values.resize(J, 0.0);

    for(unsigned long j = 0; j < J; ++j) {
        curr_spot = (double) j * dx;
        old_result.at(j) = pde->init_cond(curr_spot);
        x_values.at(j) = curr_spot;
    }

    // temporal settings
    prev_t = 0.0;
    curr_t = 0.0;
}

void FDM_Euler_Explicit::calculate_boundary_conditions() {
    new_result.at(0) =     pde->boundary_left (prev_t, x_values.at(0));
    new_result.at(J - 1) = pde->boundary_right(prev_t, x_values.at(J - 1));
}

void FDM_Euler_Explicit::calculate_inner_domain() {
    for(unsigned long j = 1; j < J - 1; ++j) {
        double dt_sig =       dt * (pde->diff_coeff(prev_t, x_values.at(j)));
        double dt_sig2 = dx * dt * (pde->diff_coeff(prev_t, x_values.at(j)));

        // differencing coefficients
        alpha = dt_sig - dt_sig2;
        beta  = dx * dx - 2.0 * dt_sig + (dt * dx * dx * (pde->zero_coeff(prev_t, x_values.at(j))));
        gamma = dt_sig + dt_sig2;

        new_result.at(j) = ((alpha * old_result.at(j - 1)) + beta * old_result.at(j) + gamma * old_result.at(j + 1)) / (dx * dx)
                            - (dt * pde->source_coeff(prev_t, x_values.at(j)));
    }
}

void FDM_Euler_Explicit::step_march() {
    std::ofstream fdm_out("fdm.csv");

    while(curr_t < t_dom) {
        curr_t = prev_t + dt;
        calculate_boundary_conditions();
        calculate_inner_domain();

        for(int j = 0; j < J; ++j) {
            fdm_out << x_values.at(j) << " " << prev_t << " " << new_result.at(j) << std::endl;
        }

        old_result = new_result;
        prev_t = curr_t;
    }

    fdm_out.close();
}


#endif