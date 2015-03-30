//
//  main.cpp
//  NA_Homework_1
//
//  Created by ikon on 3/16/15.
//  Copyright (c) 2015 ___Imaginaire___. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include "InterpolationMethods.h"
//#include "Tridiagonal.h"

std::function<double (double)> retFun(double n) {
    return [n](double x) { return x - n; };
}
double quad(double x){
    return x * x;
}
double runge(double x){
    return 1 / (1 + x * x);
}
double deriv(double x){
    return - 2 * x / pow(1 + pow(x, 2),2);
}

int main(int argc, const char * argv[])
{
// --------- --------- Problem 1.1  --------- ---------
    
//    double integral = log(1.2);
//    for (int i = 1; i <= 20; i++) {
//        std::cout <<  i << "&  " << 5 * integral <<"&  " << 1.0 / i <<  "\\\\ \\hline   " <<endl;
//        integral = -5 * integral + 1.0 / i;
////        std::cout << "res: " << integral <<std::endl;
//    }

// --------- --------- Problem 2.2  --------- ---------

    std::ofstream res;
    res.open("/Users/lixr/Desktop/res.txt");
    mVector a(11);
    for (int i = 0; i <= 10; i++) {
        a[i] = i - 5;
    }
//    std::function<double (double)> foo = Hermite(runge,deriv, a);
    std::function<double (double)> foo = Lagrange(runge, a);
    for (double i = -5; i <= 5; i += 0.01) {
        res << i << " " << foo(i) <<std::endl;
    }
    res.close();

    
    
//    std::function<double (double)> test = retFun(6);
//    std::cout << test(2) << std::endl;
//    std::cout << NewtonInterpCoeff(f, a);
//    std::cout << PolynominalEval(a, 2);
}


