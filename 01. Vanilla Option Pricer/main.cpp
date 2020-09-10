#include "vanilla_option.h"
#include <iostream>
#include <iomanip>


int main() {
    
    VanillaOption example(60.0, 0.05, 1.0, 60.0, 0.1);
    
    // should output $4.08
    std::cout << "The price of the call option is $" << std::setprecision(3) << example.calc_call_price() << "." << std::endl;

    // should output $1.16
    std::cout << "The price of the put option is $" << std::setprecision(3) << example.calc_put_price() << "." << std::endl;

    return 0;
}