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

double NewtonInterpCoeff(fp f, mVector& x);

#endif /* defined(__NA_Homework_1__InterpolationMethods__) */
