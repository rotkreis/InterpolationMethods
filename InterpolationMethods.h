//
//  InterpolationMethods.h
//  NA_Homework_1
//
//  Created by ikon on 3/16/15.
//  Copyright (c) 2015 ___Imaginaire___. All rights reserved.
//

#ifndef __NA_Homework_1__InterpolationMethods__
#define __NA_Homework_1__InterpolationMethods__

#include <iostream>
#include "Matrix.h"
#include "Tridiagonal.h"//;
typedef double (*fp)(double);

// Newton
double NewtonInterpCoeff(fp f, const mVector& x);
std::function<double (double)> Newton(fp f, const mVector& x);

// Lagrange
std::function<double (double)> Lagrange(fp f, const mVector& x);

// Linear
std::function<double (double)> Linear(fp f, const mVector& x);

// Hermite
std::function<double (double)> Hermite(fp y, fp m, const mVector& x); // y: function value, m: derivative, Second Order


std::function<double (double)> Hermite(fp y, std::function<double (double)> m, const mVector& x);// for Spline

// Spline ( Natural Boundary, Third Order)
std::function<double (double)> Spline(fp f, const mVector& x);

// Construct Polynomial from Coeffs
double PolynominalEval(const mVector& coeffs, double x);

// Function yn at xn
std::function<double (double)> CustomFunction(const mVector& y, const mVector& x);

#endif /* defined(__NA_Homework_1__InterpolationMethods__) */
