#ifndef __STOCHASTIC_H
#define __STOCHASTIC_H

#include <string>

// Bachelier model
// dSt = sigma * S0 * dWt
// St = S0*(1 + sigma*Wt)
double Bachelier(double Spot, double Strike, double Vol, double T,  std::string type);

// Black-Scholes (1973) model
// dSt = r*dSt + sigma*St*dWt
// St = S0*exp{(r-sigma^2/2)t + sigma*Wt}
double BlackScholes(double Spot, double Strike, double r, double Vol, double T, std::string type);

#endif