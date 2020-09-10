#ifndef __ASIAN_OPTION_HPP__
#define __ASIAN_OPTION_HPP__

#include "pay_off.cpp"
#include <vector>

using vector = std::vector<double>;


// since there are many types of Asian options...
// we create an abstract class and inherit from it
class AsianOption {
protected:
    Payoff* pay_off; // example of polymorphism
    // obj doesn't know which payoff function it will use
    // so when doing AsianOption(payoff_call), where payoff_call is declared as:
        // Payoff* payoff_call = new PayoffCall();
    // then the AsianOption will automatically use the payoff function for call option

    
public:
    AsianOption(Payoff* p);
    virtual ~AsianOption();
    virtual double payoff_price(const vector& spot_prices) const = 0;
};


// arithmetic asian option; price = arithmetic mean of spot prices taken at equal intervals
class AsianOptionArithmetic : public AsianOption {
public:
    AsianOptionArithmetic(Payoff* p);
    virtual ~AsianOptionArithmetic();

    virtual double payoff_price(const vector& spot_prices) const;
};


// geometric asian option; price = geometric mean of spot prices taken at equal intervals
class AsianOptionGeometric : public AsianOption {
public:
    AsianOptionGeometric(Payoff* p);
    virtual ~AsianOptionGeometric();

    virtual double payoff_price(const vector& spot_prices) const;
};



#endif