#include <cmath>
#include "stochastic.h"
#include "statistics.h"

/**
 * Calculate European option price using Bachelier model:
 * dSt = sigma * S0 * dWt 
 * St = S0*(1 + sigma*Wt)
 * 
 * @param Spot price of underlying asset at time 0.
 * @param Strike strike price of option
 * @param Vol variance of Brownian motion
 * @param T length of time
 * @param type type of European option. Including: van call/put (vanilla), con call/put (cash-or-nothing), aon call/put (asset-or-nothing)
 * @return value of the option at time 0 
 */
double Bachelier(double Spot, double Strike, double Vol, double T, std::string type)
{
    double val;
    double xs = (Strike - Spot) / (Spot * Vol * sqrt(T));
    StandardNormalDistribution Z;

    if (Spot == Strike)
    {
        return Vol * Spot * sqrt(0.5 * T / M_PI);
    }

    if (type == "van call")
    {
        val = (Spot - Strike) * Z.cdf(-xs) + Spot * Vol * sqrt(T) * Z.pdf(-xs);
    }
    else if (type == "van put")
    {
        val = (Strike - Spot) * Z.cdf(xs) + Spot * Vol * sqrt(T) * Z.pdf(xs);
    }
    else if (type == "con call")
    {
        val = Z.cdf(-xs);
    }
    else if (type == "con put")
    {
        val = Z.cdf(xs);
    }
    else if (type == "aon call")
    {
        val = Spot * Z.cdf(-xs) + Spot * Vol * sqrt(T) * Z.pdf(-xs);
    }
    else if (type == "aon put")
    {
        val = Spot * Z.cdf(xs) - Spot * Vol * sqrt(T) * Z.pdf(xs);
    }
    else
    {
        throw std::invalid_argument("Option type is invalid. Check documentation");
    }

    return val;
}

/**
 * Calculate European option price using Black-Scholes (1973) model:
 * dSt = r*dSt + sigma*St*dWt 
 * St = S0*exp{(r-sigma^2/2)t + sigma*Wt}
 * 
 * @param Spot price of underlying asset at time 0.
 * @param Strike strike price of option
 * @param r drift of St
 * @param Vol variance of Brownian motion
 * @param T length of time
 * @param type type of European option. Including: van call/put (vanilla), con call/put (cash-or-nothing), aon call/put (asset-or-nothing)
 * @return value of the option at time 0 
 */
double BlackScholes(double Spot, double Strike, double r, double Vol, double T, std::string type)
{
    double val;
    double d1 = (log(Spot / Strike) + (r + 0.5 * Vol * Vol) * T) / (Vol * sqrt(T));
    double d2 = (log(Spot / Strike) + (r - 0.5 * Vol * Vol) * T) / (Vol * sqrt(T));
    StandardNormalDistribution Z;

    if (Spot == Strike)
    {
        return Vol * Spot * sqrt(0.5 * T / M_PI);
    }

    if (type == "van call")
    {
        val = Spot * Z.cdf(d1) - Strike * exp(-r * T) * Z.cdf(d2);
    }
    else if (type == "van put")
    {
        val = -Spot * Z.cdf(-d1) + Strike * exp(-r * T) * Z.cdf(-d2);
    }
    else if (type == "con call")
    {
        val = exp(-r * T) * Z.cdf(d2);
    }
    else if (type == "con put")
    {
        val = exp(-r * T) * Z.cdf(-d2);
    }
    else if (type == "aon call")
    {
        val = Spot * Z.pdf(d1);
    }
    else if (type == "aon put")
    {
        val = Spot * Z.pdf(-d1);
    }
    else
    {
        throw std::invalid_argument("Option type is invalid. Check documentation");
    }

    return val;
}