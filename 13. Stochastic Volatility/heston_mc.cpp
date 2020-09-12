#ifndef __HESTON_MC_CPP__
#define __HESTON_MC_CPP__

#include "heston_mc.hpp"
#include <cmath>
#include <algorithm>

HestonEuler::HestonEuler(Option* o, double k, double t, double x, double r)
: p_option(o), kappa(k), theta(t), xi(x), rho(r) {}

HestonEuler::~HestonEuler() {}

void HestonEuler::calculate_vol_path (const vector& vol_draws, vector& vol_path) {
    std::size_t vec_size = vol_draws.size();
    double dt = (p_option -> T) / (double) vec_size;

    for(int i = 1; i < vec_size; ++i) {
        double v_max = std::max(vol_path.at(i - 1), 0.0);

        vol_path.at(i) = vol_path.at(i - 1) + kappa * (theta - v_max) * dt + 
                         xi * std::sqrt(v_max * dt) * vol_draws.at(i - 1);
    }
}

void HestonEuler::calculate_spot_path(const vector& spot_draw, const vector& vol_path, vector& spot_path) {
    std::size_t vec_size = spot_draw.size();
    double dt = (p_option -> T) / (double) vec_size;

    for(int i = 1; i < vec_size; ++i) {
        double v_max = std::max(vol_path.at(i - 1), 0.0);

        spot_path.at(i) = spot_path.at(i - 1) + std::exp((p_option->r - 0.5 * v_max) * dt
                          + std::sqrt(v_max * dt) * spot_draw.at(i - 1));
    }
}

#endif