//
//  InterpolationMethods.cpp
//  NA_Homework_1
//
//  Created by ikon on 3/16/15.
//  Copyright (c) 2015 ___Imaginaire___. All rights reserved.
//

#include "InterpolationMethods.h"
typedef double (*fp)(double);

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
//            std::cout << i << " " << multiple << " " << NewtonInterpCoeff(f, temp)<<" " <<res <<endl;
            res += NewtonInterpCoeff(f, temp) * multiple;
            temp.droplast();
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