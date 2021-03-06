#include "black-scholes.h"
#include <cmath>

double norm_pdf(const double &x) {
    return (1.0 / (pow(2 * M_PI, 0.5))) * exp(-0.5 * x * x);
}

double norm_cdf(const double &x) {
    double k = 1.0 / (1.0 + 0.2316419 * x);
    double k_sum = k * (0.319381530 + k * (-0.356563782 + k * (1.781477937 + k * (-1.821255978 + 1.330274429 * k))));
    if (x >= 0.0)       return (1.0 - (1.0 / (pow(2 * M_PI, 0.5))) * exp(-0.5 * x * x) * k_sum);
    else                return 1.0 - norm_cdf(-x);
}

double d_j(const int &j, const double &S, const double &K, const double &r, const double &v, const double &T) {
    double res =  (log(S / K) + (r + (pow(-1, j - 1)) * 0.5 * v * v) * T) / (v * (pow(T, 0.5)));
    return res;
}

double call_price(const double &S, const double &K, const double &r, const double &v, const double &T) {
    return S * norm_cdf(d_j(1, S, K, r, v, T)) - K * exp(-r * T) * norm_cdf(d_j(2, S, K, r, v, T));
}

double call_vega(const double &S, const double &K, const double &r, const double &v, const double &T) {
    return S * norm_pdf(d_j(1, S, K, r, v, T)) * sqrt(T);
}
