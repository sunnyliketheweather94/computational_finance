#ifndef __BLACK_SCHOLES_HPP__
#define __BLACK_SCHOLES_HPP__


class BlackScholes {
private:
    double S;
    double K;
    double r;
    double T;
    bool call;

public:
    BlackScholes(double S_, double K_, double r_, double T_, bool call_);
    double option_price(double sigma) const;
    double option_vega (double sigma) const;
};

#endif