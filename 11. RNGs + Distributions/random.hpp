#ifndef __RANDOM_HPP__
#define __RANDOM_HPP__

#include <vector>

class RandomNumberGenerator {
protected:
    unsigned long init_seed; // initial random seed value
    unsigned long curr_seed; // current random seed value
    unsigned long num_draws; // dimensionality of RNG

public:
    RandomNumberGenerator(unsigned long num, unsigned long init)
            : init_seed(init), curr_seed(init), num_draws(num) {}
    virtual ~RandomNumberGenerator() {};

    // member methods
    virtual unsigned long get_random_seed() const     { return curr_seed; }
    virtual void set_random_seed(unsigned long seed_) { curr_seed = seed_; }
    virtual void reset_random_seed() { curr_seed = init_seed; }
    virtual void set_num_draws(unsigned long draws) { num_draws = draws; }

    // generate random integer (random uniforms)
    virtual unsigned long get_random_integer() = 0;

    // fills vector with random uniforms from 0 to 1 (open interval)
    virtual void get_uniform_draws(std::vector<double>& draws) = 0;
};


#endif