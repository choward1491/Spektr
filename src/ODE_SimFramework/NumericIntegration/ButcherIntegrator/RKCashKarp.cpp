//
//  RKCashKarp.cpp
//  Spektr
//
//  Created by Christian J Howard on 5/19/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include "RKCashKarp.hpp"
#include <math.h>

RKCashKarp::RKCashKarp():ButcherIntegrator(){
    btable.resize(6,2);
    btable.c(0) = 0.0;
    btable.c(1) = 0.2;
    btable.c(2) = 0.3;
    btable.c(3) = 0.6;
    btable.c(4) = 1.0;
    btable.c(5) = 7.0/8.0;
    
    btable.a(0,0) = 0.0;
    btable.a(1,0) = 0.2;
    btable.a(2,0) = 3.0/40.0; btable.a(2,1) = 9.0/40.0;
    btable.a(3,0) = 0.3; btable.a(3,1) = -0.9; btable.a(3,2) = 1.2;
    btable.a(4,0) = -11/54.0; btable.a(4,1) = 2.5; btable.a(4,2) = -70.0/27.0;
    btable.a(4,3) = 35.0/27.0;
    btable.a(5,0) = 1631.0 / 55296.0; btable.a(5,1) = 175.0/512.0;
    btable.a(5,2) = 575.0/13824.0; btable.a(5,3) = 44275.0/110592.0;
    btable.a(5,4) = 253.0/4096.0;
    
    btable.b(0,0) = 37.0/378.0;
    btable.b(0,1) = 0.0;
    btable.b(0,2) = 250.0/621.0;
    btable.b(0,3) = 125.0/594.0;
    btable.b(0,4) = 0.0;
    btable.b(0,5) = 512.0/1771.0;
    
    btable.b(1,0) = 2825.0/27648.0;
    btable.b(1,1) = 0.0;
    btable.b(1,2) = 18575.0/48384.0;
    btable.b(1,3) = 13525.0/55296.0;
    btable.b(1,4) = 277.0/14336.0;
    btable.b(1,5) = 0.25;
}

double RKCashKarp::newStepSize( double dt, double error ){
    return 0.9 * dt * pow(fabs(tol/error),0.2);
}