#ifndef __HESTON_MC_HPP__
#define __HESTON_MC_HPP__

#include <vector>
#include <iostream>
#include "option.hpp"

using vector = std::vector<double>;

class HestonEuler {
private:
    Option* p_option;
    double kappa;
    double theta;
    double xi;
    double rho;

public:
    HestonEuler(Option*, double, double, double, double);
    virtual ~HestonEuler();

    void calculate_vol_path (const vector& vol_draws, vector& vol_path);
    void calculate_spot_path(const vector& spot_draw, const vector& vol_path, vector& spot_path);
};


#endif