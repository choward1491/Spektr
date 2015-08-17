//
//  main.cpp
//  NumCH
//
//  Created by Christian J Howard on 8/8/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include <iostream>
#include "TestSim.hpp"
#include "ConfigParser.hpp"
#include "Function.hpp"
#include "GradientDescent.hpp"
using namespace NumCH;

int main(int argc, const char * argv[]) {
    
    //TestSim sim;
    //sim.simLoop();
    
    GradientDescent<1, 2> test;
    test.setMaxIterations( 5000 );
    test.setStopThreshold( 1e-20 );
    
    
    Quadratic quad;
    Vect<double> guess(1);
    guess[0] = 5.0;
    Vect<double> output = test.solve( guess, quad );
    output.print();
    printf("Num Iters = %i\n", test.numIters);
    
    return 0;
}
