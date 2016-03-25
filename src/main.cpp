//
//  main.cpp
//  NumCH
//
//  Created by Christian J Howard on 8/8/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include <string>
#include "TestPendulumSim.hpp"
#include "Matrix.hpp"
#include "Fraction.h"

typedef la::Mat<Fraction> mat;

int main(int argc, const char * argv[]) {
    
    mat a(2,2,1);
    a.print();
    mat x(2,1,1/3.0);
    x.print();
    mat c = a*x;
    c.print();
    
    // exit
    return 0;
}

