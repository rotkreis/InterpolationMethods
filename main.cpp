//
//  main.cpp
//  NA_Homework_1
//
//  Created by ikon on 3/16/15.
//  Copyright (c) 2015 ___Imaginaire___. All rights reserved.
//

#include <iostream>
#include <cmath>
#include "InterpolationMethods.h"

std::function<double (double)> retFun(double n) {
    return [n](double x) { return x - n; };
}
double quad(double x){
    return x * x;
}

int main(int argc, const char * argv[])
{
// --------- --------- Problem 1.1  --------- ---------
    
//    double integral = log(1.2);
//    std::cout << "I_0: " << integral << std::endl;
//    for (int i = 1; i <= 20; i++) {
//        integral = -5 * integral + 1.0 / i;
//        std::cout << "I_" << i << ": " << integral <<", and     " << 1.0 / i<< std::endl;
//    }

// --------- --------- Problem 2.2  --------- ---------

    mVector a(3);
    a = {1,2,3};
    std::function<double (double)> foo = Newton(quad, a);
    for (int i = 1; i <= 10; i++) {
        std::cout << foo(i) <<std::endl;
    }
//    std::function<double (double)> test = retFun(6);
//    std::cout << test(2) << std::endl;
//    std::cout << NewtonInterpCoeff(f, a);
//    std::cout << PolynominalEval(a, 2);
}


