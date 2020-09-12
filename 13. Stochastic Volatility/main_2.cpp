#include <iostream>
#include <random>

#include "pay_off.hpp"
#include "option.hpp"
#include "correlated_snd.hpp"
#include "heston_mc.hpp"

void generate_normal(double rho, vector& spot_normals, vector& cor_normals) {
    unsigned size = spot_normals.size();

    StandardNormal snd;
    vector snd_uniform(size, 0.0);

    std::random_device rd;  // will be used for seeding the Mersenne twister engine generator
    std::mt19937 gen(rd()); // Standard Mersenne twister generator
    std::uniform_real_distribution<double> dis(0.0, 1.0); 

    for(int i = 0; i < size; ++i) {
        snd_uniform.at(i) = dis(gen);
    }

    snd.random_draws(snd_uniform, spot_normals); // create standard normal draws



    CorrelatedSND c_snd(rho, &spot_normals);
    vector c_snd_uniform(size, 0.0);

    for(int i = 0; i < size; ++i) {
        c_snd_uniform.at(i) = dis(gen);
    }

    c_snd.random_draws(c_snd_uniform, cor_normals); // create the correlated standard normals
}


int main() {
    unsigned num_iter      = 10000;
    unsigned num_intervals = 100;

    double S_0 = 100.0;
    double K   = 100.0;
    double r   = 0.0319;
    double v_0 = 0.010201;
    double T   = 1.00;

    double rho   = -0.7;
    double kappa = 6.21;
    double theta = 0.019;
    double xi    = 0.61;


    Payoff* p_call = new PayoffCall(K);
    Option* p_opt  = new Option(K, r, T, p_call);
    HestonEuler hest_euler(p_opt, kappa, theta, xi, rho);

    vector spot_draws (num_intervals, 0.0);
    vector vol_draws  (num_intervals, 0.0);
    vector spot_prices(num_intervals, S_0);
    vector vol_prices (num_intervals, v_0);

    // Monte Carlo
    double pay_off {0.0};

    for(unsigned i = 0; i < num_iter; ++i) {
        // std::cout << "Calculating path..."

        generate_normal(rho, spot_draws, vol_draws);
        hest_euler.calculate_vol_path(vol_draws, vol_prices);
        hest_euler.calculate_spot_path(spot_draws, vol_prices, spot_prices);

        pay_off += (p_opt->payoff)->operator()(spot_prices.at(num_intervals - 1));
    }

    double option_price = (pay_off / (double) num_iter) * std::exp(- r * T);
    std::cout << "Option price = " << option_price << std::endl;

    delete p_opt;
    delete p_call;

    return 0;
}