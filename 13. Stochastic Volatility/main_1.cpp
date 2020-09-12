#include "statistics.hpp"
#include "correlated_snd.hpp"
#include <iostream>
#include <vector>
#include <random>

// using vector = std::vector<double>;

int main() {
    int vals {30};
    StandardNormal snd;
    vector snd_uniform(vals, 0.0);
    vector snd_normal (vals, 0.0);

    std::random_device rd;  // will be used for seeding the Mersenne twister engine generator
    std::mt19937 gen(rd()); // Standard Mersenne twister generator
    std::uniform_real_distribution<double> dis(0.0, 1.0); 

    for(int i = 0; i < vals; ++i) {
        snd_uniform.at(i) = dis(gen);
    }

    snd.random_draws(snd_uniform, snd_normal);


    double rho {0.5}; // correlation coefficient
    CorrelatedSND c_snd(rho, &snd_normal);
    vector c_snd_uniform(vals, 0.0);
    vector c_snd_normal (vals, 0.0);

    for(int i = 0; i < vals; ++i) {
        c_snd_uniform.at(i) = dis(gen);
    }

    c_snd.random_draws(c_snd_uniform, c_snd_normal);


    for(int i = 0; i < vals; ++i) {
        std::cout << snd_normal.at(i) << " " << c_snd_normal.at(i) << std::endl;
    }

    return 0;
}