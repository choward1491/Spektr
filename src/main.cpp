//
//  main.cpp
//  NumCH
//
//  Created by Christian J Howard on 8/8/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include <string>
#include "ExampleSim.hpp"
#include "Matrix.hpp"

typedef la::Mat<double> Mat;

int main(int argc, const char * argv[]) {
    
    ExampleSim sim;
    sim.runSim();
    
    // exit
    return 0;
}

