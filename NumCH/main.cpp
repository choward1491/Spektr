//
//  main.cpp
//  NumCH
//
//  Created by Christian J Howard on 8/8/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "Matrix.hpp"
#include "Timer.hpp"
#include "RandomNumberGenerator.hpp"

typedef la::SMat<double>    Sym;
typedef la::Mat<double>     Mat;
typedef la::SpMat<double>   SMat;
typedef la::LMat<double>    LMat;
typedef la::DMat<double>    Diag;


#include "TestExample1.hpp"
#include "TestPSO1.hpp"


int main(int argc, const char * argv[]) {
    
    

    Timer timer;
    timer.start();
    
    runExample1_UKF();
    testPSO_Rosenbrock_RandInit();
    
    timer.stop();
    printf("Time was %lf\n",timer.getDuration());
    
    
    return 0;
}

