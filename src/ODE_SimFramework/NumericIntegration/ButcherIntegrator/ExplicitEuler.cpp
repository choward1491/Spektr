//
//  ExplicitEuler2.cpp
//  Spektr
//
//  Created by Christian J Howard on 4/15/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include "ExplicitEuler.hpp"

ExplicitEuler::ExplicitEuler():ButcherIntegrator(){
    btable.resize(1);
    btable.c(0) = 0.0;
    btable.b(0,0) = 1.0;
    btable.a(0, 0) = 0;
}