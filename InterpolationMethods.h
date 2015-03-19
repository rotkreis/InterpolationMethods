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
typedef double (*fp)(double);

// Newton
double NewtonInterpCoeff(fp f, const mVector& x);

std::function<double (double)> Newton(fp f, const mVector& x);

// Linear

std::function<double (double)> Linear(fp f, const mVector& x);

double PolynominalEval(const mVector& coeffs, double x);

#endif /* defined(__NA_Homework_1__InterpolationMethods__) */
