#ifndef __LINEAR_CONGRUENTIAL_GENERATOR_CPP__
#define __LINEAR_CONGRUENTIAL_GENERATOR_CPP__

#include "linear_congruential_generator.hpp"

// defining constants for the Park and Miller algorithm
const unsigned long a = 16807; // = 7^5
const unsigned long m = 2147483647; // = 2^32 - 1 (thus, prime)

// Scrage's algorithm constants
const unsigned long q = 127773;
const unsigned long r = 2836;

LinearCongGenerator::LinearCongGenerator(unsigned long d, unsigned long i) 
    : RandomNumberGenerator(d, i) {
        if(i == 0) {
            init_seed = 1;
            curr_seed = 1;
        }

        max_multiplier = 1.0 / (1.0 + ((double) m - 1));
}

LinearCongGenerator::~LinearCongGenerator() {}

unsigned long LinearCongGenerator::get_random_integer() {
    unsigned long k = 0;
    k = curr_seed / q;
    curr_seed = a * (curr_seed - k * q) - r * k;

    if(curr_seed < 0) {
        curr_seed += m;
    }

    return curr_seed;
}

void LinearCongGenerator::get_uniform_draws(std::vector<double>& draws) {
    for(unsigned long i = 0; i < num_draws; ++i) {
        draws.at(i) = get_random_integer() * max_multiplier;
    }
}


#endif