#include <iostream>
// #include <vector>
// #include "linear_congruential_generator.hpp"
#include "statistics.hpp"

using vector = std::vector<double>;

int main() {
    // // testing the LCG
    // unsigned long init = 1;
    // unsigned long num = 20;

    // std::vector<double> draws(num, 0.0);


    // LinearCongGenerator lcg(num, init);
    // lcg.get_uniform_draws(draws);

    // for(auto const x : draws) {
    //     std::cout << x << std::endl;
    // }

    // std::cout << std::endl;

    // return 0;

    // testing the standard normal distribution class
    StandardNormal snd;
    vector uniform(20, 0.0);
    vector normal (20, 0.0);

    for(int i = 0; i < uniform.size(); ++i) {
        uniform.at(i) = rand() / (double) RAND_MAX;
    }

    snd.random_draws(uniform, normal);

    for(const auto x : normal) {
        std::cout << x << std::endl;
    }

    std::cout << std::endl;
}