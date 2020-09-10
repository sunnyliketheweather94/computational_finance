#include <vector>
#include <iostream>
#include <cmath>
#include <numeric>
#include <algorithm>

using vector = std::vector<double>;

int main() {
    vector v;

    for(double i = 1.0; i < 11.0; ++i) {
        v.push_back(i);
    }

    for(auto const item : v) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    auto log_sum = [](double& a, double& b) { a += std::log(b); return a; };
    double trial_sum = std::accumulate(v.begin(), v.end(), std::log(v.at(0)), log_sum);
    double true_sum = 0;

    for(auto it = v.begin(); it != v.end(); ++it) {
        true_sum += std::log(*it);
    }

    std::cout << "Trial sum = " << trial_sum << std::endl;
    std::cout << "True sum = " << true_sum << std::endl;

    return 0;
}