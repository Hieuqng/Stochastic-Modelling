#!/usr/bin/env python
import numpy as np
from scipy.stats import norm

def bachelier(So, K, sigma, T, option_type):
    '''
    Calculate European option price using Bachelier model:
        dSt = sigma * S0 * dWt 
        St = S0*(1 + sigma*Wt)
    
    Parameter
    ---------
    So: float
        price of underlying asset at time 0
    K: float
        strike price of option
    sigma: float
        variance of Brownian motion
    T: float
        length of time
    option_type: str
        type of European option. 
        Including: van call/put (vanilla), con call/put (cash-or-nothing), aon call/put (asset-or-nothing)
    
    Return
    ------
    val: value of the option at time 0
    '''
    
    
    xs = (K-So) / (So * sigma * np.sqrt(T))
    val = None
    
    if So == K:
        return sigma*So*np.sqrt(T/(2*np.pi))
    
    if option_type == 'van call':
        val = (So - K) * norm.cdf(-xs) + So*sigma*np.sqrt(T)*norm.pdf(-xs)
    elif option_type == 'van put':
        val = (K - So) * norm.cdf(xs) + So*sigma*np.sqrt(T)*norm.pdf(xs)
    elif option_type == 'con call':
        val = norm.cdf(-xs)
    elif option_type == 'con put':
        val = norm.cdf(xs)
    elif option_type == 'aon call':
        val = So*norm.cdf(-xs) + So*sigma*np.sqrt(T)*norm.pdf(-xs)
    elif option_type == 'aon put':
        val = So*norm.cdf(xs) - So*sigma*np.sqrt(T)*norm.pdf(xs)
    else:
        raise(ValueError("Option type is invalid. " +
                         "Should be either 'van call', 'van put', 'con call', 'con put', 'aon call', or 'aon put'"))
    
    return val
                
    
def black_scholes(So, K, r, sigma, T, option_type):
    '''
    Calculate European option price using Black-Scholes (1973) model:
        dSt = r*dSt + sigma*St*dWt 
        St = S0*exp{(r-sigma^2/2)t + sigma*Wt}
    
    Parameter
    ---------
    So: float
        price of underlying asset at time 0
    K: float
        strike price of option
    r: float
        drift of St
    sigma: float
        variance of Brownian motion
    T: float
        length of time
    option_type: str
        type of European option. 
        Including: van call/put (vanilla), con call/put (cash-or-nothing), aon call/put (asset-or-nothing)
    
    Return
    ------
    val: value of the option at time 0
    '''
    
    
    d1 = (np.log(So/K) + (r+sigma**2/2)*T) / (sigma*np.sqrt(T))
    d2 = (np.log(So/K) + (r-sigma**2/2)*T) / (sigma*np.sqrt(T))
    val = None
    
    if So == K:
        return sigma*So*np.sqrt(T/(2*np.pi))
    
    if option_type == 'van call':
        val = So*norm.cdf(d1) - K*np.e**(-r*T)*norm.cdf(d2)
    elif option_type == 'van put':
        val = -So*norm.cdf(-d1) + K*np.e**(-r*T)*norm.cdf(-d2)
    elif option_type == 'con call':
        val = np.e**(-r*T) * norm.cdf(d2)
    elif option_type == 'con put':
        val = np.e**(-r*T) * norm.cdf(-d2)
    elif option_type == 'aon call':
        val = So*norm.cdf(d1)
    elif option_type == 'aon put':
        val = So*norm.cdf(-d1)
    else:
        raise(ValueError("Option type is invalid. " +
                         "Should be either 'van call', 'van put', 'con call', 'con put', 'aon call', or 'aon put'"))
    
    return val
                