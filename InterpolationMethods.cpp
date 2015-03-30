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
// Lagrange
std::function<double (double)> Lagrange(fp f, const mVector& x){
    return [&, f](double t) {
        double res = 0;
        int n = x.dim();
        for (int i = 0; i != n; i++) {
            double multiple = 1;
            for (int j = 0; j != n; j++) {
                if (j != i) {
                    multiple *= (t - x[j]);
                    multiple /= (x[i] - x[j]);
                }
            }
            res += f(x[i]) * multiple;
        }
        return res;
    };
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
std::function<double (double)> Hermite(fp y, std::function<double (double)> m, const mVector& x){ // y: function value, m: derivative
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

// Spline
std::function<double (double)> Spline(fp f, const mVector& x){
    int n = x.dim() - 1; // index from 0 to n, n + 1 points total
    mVector c(n);
    for (int i = 0; i != x.dim() - 1; i++) {
        assert(x[i] < x[i + 1]);
    }
    c[0] = 1;
    for (int i = 1; i != c.dim(); i++) {
        c[i] = (x[i] - x[i - 1]) / (x[i + 1] - x[i - 1]);
    }
    mVector a(n);
    for (int i = 0; i != n - 1; i++) {
        a[i] = 1 - c[i + 1];
    }
    a[n - 1] = 1;
    mVector b(n + 1);
    for (int i = 0; i != b.dim(); i++) {
        b[i] = 2.0;
    }
    mVector d(n + 1);
    d[0] = 3 * (f(x[1]) - f(x[0])) / (x[1] - x[0]);
    d[n] = 3 * (f(x[n]) - f(x[n - 1])) / (x[n] - x[n - 1]);
    for (int i = 1; i != d.dim(); i++) {
        d[i] = 3 * (1 - c[i]) / (x[i] - x[i - 1]) * (f(x[i]) - f(x[i - 1]))
             + 3 * c[i] / (x[i + 1] - x[i]) * (f(x[i + 1]) - f(x[i]));
    }
    mVector sol(n + 1);
    TridiagonalSolve(a, b, c, d, sol);
    Matrix test(n + 1, n + 1);
    for(int i = 0; i != n + 1; i++){
        test(i,i) = 2;
    }
    for (int i = 0; i != n; i++) {
        test(i + 1, i) = a[i];
    }
    for (int i = 0; i != n; i++) {
        test(i, i + 1) = c[i];
    }
    std::cout << test * sol - d;
    
    std::function<double (double)> m = CustomFunction(sol,x);
//    std::cout << reslu.GetNumRows();
//    std::cout << reslu.GetNumCols();
    return Hermite(f, m, x);
}

// Polynomial
double PolynominalEval(const mVector& coeffs, double x){
    double res = 0;
    for (int i = 0; i != coeffs.dim(); i++) {
        res += coeffs[i] * pow(x, i);
    }
    return res;
}

// Function yn at xn
std::function<double (double)> CustomFunction(const mVector& y, const mVector& x){
    return [&,y](double t){
        for (int i = 0; i != x.dim(); i++) {
            if (t == x[i]) {
                return y[i];
            }
        }
        return 0.0;
    };
}