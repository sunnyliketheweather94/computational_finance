#include <iostream>
#include "pay_off.hpp"
#include "path_generation.hpp"
#include "asian_options.hpp"

using vector = std::vector<double>;

int main() {

    int num_iter {10000};
    int num_intervals {250};
    double S {30.0}; // spot price = $30.00
    double K {29.0}; // strike price = $29.00
    double r {0.08}; // risk-free rate = 8%
    double v {0.3}; // volatility = 30%
    double T {1.0}; // 1 year to maturiy

    vector spot_prices(num_intervals, S);
    Payoff* p_call = new PayoffCall(K);
    AsianOptionArithmetic asian(p_call);

    double payoff_sum {0.0};

    for(int i = 0; i < num_iter; ++i) {
        CalcPathOfSpotPrices(spot_prices, r, v, T);
        payoff_sum += asian.payoff_price(spot_prices);
    }

    double discounted_avg = std::exp(- r * T) * (payoff_sum / (double) num_iter);

    delete p_call;

    std::cout << "Number of paths = "     << num_iter      << std::endl;
    std::cout << "Number of intervals = " << num_intervals << std::endl;
    
    std::cout << "\nSpot price = "     << S << std::endl;
    std::cout << "Strike price = "     << K << std::endl;
    std::cout << "Risk-free rate = "   << r << std::endl;
    std::cout << "Volatility = "       << v << std::endl;
    std::cout << "Time to maturity = " << T << std::endl;

    std::cout << "\nPrice of arithmetic Asian option = " << discounted_avg << std::endl;

    return 0;
}