#include <iostream>
#include "stochastic.h"

using namespace std;

int main(int argc, char **argv)
{
    double So = 50;
    double K = 20;
    double r = 0.13;
    double sigma = 0.2;
    double T = 4;

    cout << "Bachelier model" <<  endl;
    cout << "Vanilla Call:" << Bachelier(So, K, sigma, T, "van call") << endl;
    cout << "Vanilla Put:" << Bachelier(So, K, sigma, T, "van put") << endl;
    cout << "CoN Call:" << Bachelier(So, K, sigma, T, "con call") << endl;
    cout << "CoN Put:" << Bachelier(So, K, sigma, T, "con put") << endl;
    cout << "AoN Call:" << Bachelier(So, K, sigma, T, "aon call") << endl;
    cout << "AoN Put:" << Bachelier(So, K, sigma, T, "aon put") << endl;

    cout << "Black-Scholes model" <<  endl << endl;
    cout << "Vanilla Call:" << BlackScholes(So, K, r, sigma, T, "van call") << endl;
    cout << "Vanilla Put:" << BlackScholes(So, K, r, sigma, T, "van put") << endl;
    cout << "CoN Call:" << BlackScholes(So, K, r, sigma, T, "con call") << endl;
    cout << "CoN Put:" << BlackScholes(So, K, r, sigma, T, "con put") << endl;
    cout << "AoN Call:" << BlackScholes(So, K, r, sigma, T, "aon call") << endl;
    cout << "AoN Put:" << BlackScholes(So, K, r, sigma, T, "aon putt") << endl;

    return 0;
}