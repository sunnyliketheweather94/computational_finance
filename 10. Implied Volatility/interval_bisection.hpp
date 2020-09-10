#ifndef __INTERVAL_BISECTION_HPP__
#define __INTERVAL_BISECTION_HPP__

#include <cmath>
#include <iostream>

template <typename Functor>
double interval_bisect(double y_target, 
                       double m,
                       double n,
                       double epsilon,
                       Functor g) {
    double x = 0.5 * (m - n) + n;
    double y = g(x);

    do {
        if(y < y_target) { m = x; }
        if(y > y_target) { n = x; }

        x = 0.5 * (m - n) + n;
        y = g(x);

    }while(std::fabs(y - y_target) > epsilon);

    return x;
}


#endif