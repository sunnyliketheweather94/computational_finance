#include "payoff.hpp"
#include "vanilla_option.hpp"
#include "pde.hpp"
#include "fdm.hpp"

int main() {
    // option parameters
    double K = 0.5;
    double r = 0.05;
    double v = 0.2;
    double T = 1.00;

    // FDM discretization parameters
    double x_dom = 1.0;
    unsigned long J = 20;
    double t_dom = T;
    unsigned long N = 20;

    // create PayOff and Option objects
    PayOff* p_call = new PayOffCall(K);
    VanillaOption* c_option = new VanillaOption(K, r, T, v, p_call);

    // create PDE and FDM objects
    BlackScholesPDE* bs_pde = new BlackScholesPDE(c_option);
    FDM_Euler_Explicit fdm_euler(x_dom, J, t_dom, N, bs_pde);

    // run the FDM solver
    fdm_euler.step_march();

    delete bs_pde;
    // delete c_option,
    delete p_call;

    return 0;
}