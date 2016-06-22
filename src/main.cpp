//
//  main.cpp
//
//  Created by Christian J Howard on 8/8/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include <string>
#include <math.h>
#include "LocalRegression.hpp"
//#include "TestLocalRegression1D.hpp"
#include "TestLocalRegression2D.hpp"
#include "TestAdvectionEqn.hpp"
#include <libiomp/omp.h>
#include "TestExample1.hpp"
#include "TestNeuralFilter1.hpp"

int main(int argc, const char * argv[]) {
    
    //testLocalRegression1D();
    //testLocalRegression2D();
    runExample1_UKF();
    runExample1_ADELINE();
    
    //double dtime = omp_get_wtime();
    //testAdvectionEqnSim("/User/christianjhoward/history.txt");
        
    // exit
    return 0;
}

