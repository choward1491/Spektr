//
//  main.cpp
//
//  Created by Christian J Howard on 8/8/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include <string>
#include "TestNeuralKalmanFilter.hpp"
#include "Network.hpp"
#include "TestExample1.hpp"
#include "NBodySim.hpp"
#include "TestPendulumSim.hpp"
#include "TestAdvectionEqn.hpp"
#include "TestHeatEquationSim.hpp"
#include "TestNeuronSim.hpp"
#include "NonlinearSim.h"



int main(int argc, const char * argv[]) {
    
    //NBodySim sim;
    //sim.runSim();
    NonlinearSim sim;
    sim.runSim();
    
    //testPendulumSim("/Users/christianjhoward/history.txt");
    //testAdvectionEqnSim("/Users/christianjhoward/history.txt");
    //testHeatEquationSim("/Users/christianjhoward/history.txt");
    //testNeuronSim("/Users/christianjhoward/history.txt");
    
    //runExample1_ADELINE();
    //runExample1_NeuralKalman();
    //runExample1_UKF();
    
    // exit
    return 0;
}

