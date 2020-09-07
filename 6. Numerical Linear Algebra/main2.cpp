
// an application of the Thomas Algorithm in solving a discretized heat equation.

#include <iostream>
#include <cmath>
#include <vector>

using vec = std::vector<double>;


void thomas_algorithm(const vec& a,
                      const vec& b,
                      const vec& c,
                      const vec& d,
                            vec& f) {
    // f is the solution vector..
    std::size_t N = d.size();

    vec c_star(N, 0.0), d_star(N, 0.0);

    c_star[0] = c[0] / b[0]; // assume that b[0] != 0
    d_star[0] = d[0] / b[0];

    for(int i = 0; i < (int) N; ++i) {
        double m = 1.0 / (b[i] - a[i] * c_star[i - 1]);

        c_star[i] = c[i] * m;
        d_star[i] = (d[i] - a[i] * d_star[i - 1]) * m;
    }

    for(int i = (int) N - 1; i > 0; --i) {
        f[i] = d_star[i] - c_star[i] * d[i + 1];
    }
}


int main(int argc, char** argv) {
    // we set up a BVP for the 1D-heat equation..
    std::size_t N = 13;
    double delta_x = 1.0 / static_cast<double>(N);
    double delta_t = 0.001;
    double r = delta_t / (delta_x * delta_x);

    vec a(N - 1, - r / 2.0);
    vec b(N, 1.0 + r);
    vec c(N - 1, - r / 2.0);
    vec d(N, 0.0);
    vec f(N, 0.0);

    f[5] = 1;
    f[6] = 2;
    f[7] = 1;

    // outputting the vector f before a new time step
    std::cout << "f = (";
    for(int i = 0; i < N; ++i) {
        std::cout << f[i];

        if(i < N - 1) {
            std::cout << ", ";
        }
    }

    std::cout << ")" << std::endl << std::endl;

    // fill in the current time step vector d
    for(int i = 1; i < N - 1; ++i) {
        d[i] = r * 0.5 * f[i + 1] + (1.0 - r) * f[i] + r * 0.5 * f[i - 1]; 
    }

    thomas_algorithm(a, b, c, d, f);

    // outputting the solution to the linear system above
    std::cout << "f = (";
    for(int i = 0; i < N; ++i) {
        std::cout << f[i];

        if(i < N - 1) {
            std::cout << ", ";
        }
    }

    std::cout << ")" << std::endl << std::endl;  

    return 0;
}