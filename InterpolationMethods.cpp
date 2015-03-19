//
//  InterpolationMethods.cpp
//  NA_Homework_1
//
//  Created by ikon on 3/16/15.
//  Copyright (c) 2015 ___Imaginaire___. All rights reserved.
//

#include "InterpolationMethods.h"
typedef double (*fp)(double);
// Newton
double NewtonInterpCoeff(fp f, const mVector& x){
    if (x.dim() == 1) {
        return f(x[0]);
    }
    else {
        return (NewtonInterpCoeff(f, DropFirst(x)) - NewtonInterpCoeff(f, DropLast(x))) /
               (x.last() - x.first());
    }
}
std::function<double (double)> Newton(fp f, const mVector& x){
    return [&, f](double t) {
        mVector temp(x);
        double res = f(x[0]);
        for (int i = x.dim() - 1; i != 0; i--) {
            double multiple = 1;
            for (int j = 0; j <= i - 1; j++) {
                multiple *= (t - x[j]);
            }
            res += NewtonInterpCoeff(f, temp) * multiple;
            temp.droplast();
        }
        return res;
    };
    //         std::cout << i << " " << multiple << " " << NewtonInterpCoeff(f, temp)<<" " <<res <<endl;
}

// Linear
std::function<double (double)> Linear(fp f, const mVector& x){
    return [&, f](double t) {
        double res = 0;
        int n = x.dim(); // x0, x1, ...,x(n-2), x(n-1)
        for (int i = 0; i != n - 1 ; i++) { // Sequence
            assert(x[i] < x[i + 1]);
        }
        if (t >= x[0] && t <= x[1] ) {
            res += f(x[0]) * ((t - x[1]) / (x[0] - x[1]));
        }
        if (n >= 2 && t >= x[n - 2] && t <= x[n - 1] ) {
            res += f(x[n - 1]) * ((t - x[n - 2]) / (x[n - 1] - x[n - 2]));
        }
        for (int i = 1; i <= n - 2; i++) {
            if (t >= x[i - 1] && t <= x[i]) {
                res += f(x[i]) * ((t - x[i - 1]) / (x[i] - x[i - 1]));
            }
            else {
                if (t >= x[i] && t <= x[i + 1]) {
                    res += f(x[i]) * ((t - x[i + 1]) / (x[i] - x[i + 1]));
                }
            }
        }
        return res;
    };
}

// Hermite
std::function<double (double)> Hermite(fp y, fp m, const mVector& x){ // y: function value, m: derivative
    return [&, y, m](double t) {
        double res = 0;
        int n = x.dim(); // x0, x1, ...,x(n-2), x(n-1)
        for (int i = 0; i != n - 1 ; i++) { // Sequence
            assert(x[i] < x[i + 1]);
        }
        if (t >= x[0] && t <= x[1]) {
            double h = x[1] - x[0];
            res += y(x[0]) * (1 + 2 * (t - x[0]) / (x[1] - x[0])) * pow(t - x[1], 2) / pow(h, 2);
            res += m(x[0]) * (t - x[0]) * pow(t - x[1], 2) / pow(h, 2);
        }
        if (n >= 2 && t >= x[n - 2] && t <= x[n - 1]) {
            double h = x[n - 1] - x[n - 2];
            res += y(x[n - 1]) * (1 + 2 * (t - x[n - 1]) / (x[n - 2] - x[n - 1])) * pow(t - x[n - 2], 2) / pow(h, 2);
            res += m(x[n - 1]) * (t - x[n - 1]) * pow(t - x[n - 2], 2) / pow(h, 2);
        }
        for (int i = 1; i <= n - 2; i++) {
            if (t >= x[i - 1] && t <= x[i]) {
                double h = x[i] - x[i - 1];
                res += y(x[i]) * (1 + 2 * (t - x[i]) / (x[i - 1] - x[i])) * pow(t - x[i - 1], 2) / pow(h, 2);
                res += m(x[i]) * (t - x[i]) * pow(t - x[i - 1], 2) / pow(h, 2);
            }
            else {
                if (t >= x[i] && t <= x[i + 1]) {
                    double h = x[i + 1] - x[i];
                    res += y(x[i]) * (1 + 2 * (t - x[i]) / (x[i + 1] - x[i])) * pow(t - x[i + 1], 2) / pow(h, 2);
                    res += m(x[i]) * (t - x[i]) * pow(t - x[i + 1], 2) / pow(h, 2);
                }
            }
        }
        return res;
    };
}

double PolynominalEval(const mVector& coeffs, double x){
    double res = 0;
    for (int i = 0; i != coeffs.dim(); i++) {
        res += coeffs[i] * pow(x, i);
    }
    return res;
}