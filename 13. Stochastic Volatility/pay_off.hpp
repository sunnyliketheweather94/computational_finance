#ifndef __PAYOFF_HPP__
#define __PAYOFF_HPP__

#include <algorithm>

class Payoff {
public:
    Payoff(); // default constructor
    virtual ~Payoff(); // destructor

    virtual double operator()(const double& S) = 0; // pure virtual function
};


// models an European call option
class PayoffCall : public Payoff {
private:
    double K; // strike price

public:
    PayoffCall(const double& K_);
    virtual ~PayoffCall();

    virtual double operator()(const double& S);
};


// models an European put option
class PayoffPut : public Payoff {
private:
    double K; // strike price

public:
    PayoffPut(const double& K_);
    virtual ~PayoffPut();

    virtual double operator()(const double& S) const;
};


#endif