#ifndef __VANILLA_OPTION_H__
#define __VANILLA_OPTION_H__


class VanillaOption {
private:
    void init();
    void copy(const VanillaOption& rhs); // don't copy the parameter rhs and don't modify it either.

    double K; // strike price
    double r; // risk-free rate
    double T; // maturity time
    double S; // underlying asset price
    double sigma; // volatility of underlying asset

public:
    VanillaOption(); // default constructor
    VanillaOption(const double& K_, const double& r_, const double& T_,
                  const double& S_, const double& sig_);
    VanillaOption(const VanillaOption& rhs); // copy constructor
    VanillaOption& operator=(const VanillaOption& rhs); // assignment operator
    virtual ~VanillaOption(); // virtual destructor (always recommended)



    // here const means that the function does not modify the member 
    // or anything else. If it were at the beginning.. like const double get_K()
    // then the function would RETURN a const value (that cannot be modified)
    // which is NOT what we want here.

    // getter functions for the parameters defining the vanilla option
    double get_K() const;
    double get_r() const;
    double get_T() const;
    double get_S() const;
    double get_sigma() const;

    // computes the call or put price for the option
    double calc_call_price() const;
    double calc_put_price()  const;
};



#endif