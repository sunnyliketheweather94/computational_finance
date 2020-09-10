#ifndef __LINEAR_CONGRUENTIAL_GENERATOR_HPP__
#define __LINEAR_CONGRUENTIAL_GENERATOR_HPP__

#include "random.hpp"

class LinearCongGenerator : public RandomNumberGenerator {
private:
    double max_multiplier;

public:
    LinearCongGenerator(unsigned long draws, unsigned long init_ = 1);
    virtual ~LinearCongGenerator();

    virtual unsigned long get_random_integer();
    virtual void get_uniform_draws(std::vector<double>& draws);
};


#endif