//
//  RungeKutta42.cpp
//  Spektr
//
//  Created by Christian J Howard on 4/16/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include "RungeKutta4.hpp"

RungeKutta4::RungeKutta4():ButcherIntegrator(){
    btable.resize(4);
    btable.c(0) = 0.0; btable.a(0, 0) = 0;
    btable.c(1) = 0.5; btable.a(1,0)  = 0.5;
    btable.c(2) = 0.5; btable.a(2,1)  = 0.5;
    btable.c(3) = 1.0; btable.a(3,2)  = 1.0;
    btable.b(0,0) = 1.0/6.0;
    btable.b(0,1) = 1.0/3.0;
    btable.b(0,2) = 1.0/3.0;
    btable.b(0,3) = 1.0/6.0;
}