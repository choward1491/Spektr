//
//  ExplicitTrapezoidal.cpp
//  Spektr
//
//  Created by Christian J Howard on 4/16/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include "ExplicitTrapezoidal.hpp"

ExplicitTrapezoidal::ExplicitTrapezoidal():ButcherIntegrator(){
    btable.resize(2);
    btable.c(0) = 0.0; btable.a(0, 0) = 0.0;
    btable.c(1) = 1.0; btable.a(1,0)  = 1.0;
    btable.b(0,0) = 0.5;
    btable.b(0,1) = 0.5;
}