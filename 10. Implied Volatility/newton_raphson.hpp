#ifndef __NEWTON_RAPHSON_HPP__
#define __NEWTON_RAPHSON_HPP__


#include <cmath>

template <typename T, double (T::*g)(double) const, double (T::*g_prime)(double) const>
double newton_raphson(double y_target,
                      double init,
                      double epsilon,
                      const T& root_function) {
    double y = (root_function.*g)(init);
    double x = init;

    while(std::fabs(y - y_target) > epsilon) {
        double dx = (root_function.*g_prime)(x);
        x += (y_target - y) / dx;
        y  = (root_function.*g)(x); 
    }

    return x;
}

#endif