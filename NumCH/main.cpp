//
//  main.cpp
//  NumCH
//
//  Created by Christian J Howard on 8/8/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "Rosenbrock.hpp"
#include "RandomInit.hpp"
#include "PSO.hpp"
#include "Matrix.hpp"
#include "Timer.hpp"
#include "RandomNumberGenerator.hpp"
#include "Solver.hpp"

typedef opt::pso<opt::Rosenbrock, opt::RandomInit> PSO;

typedef la::SMat<double>    Sym;
typedef la::Mat<double>     Mat;
typedef la::SpMat<double>   SMat;
typedef la::LMat<double>    LMat;
typedef la::DMat<double>    Diag;

int main(int argc, const char * argv[]) {
    
    
    Timer timer;
    RandomNumberGenerator rng;
    timer.start();
    
    
    Sym A(3,3,2.0);
    A(0,0) = 1; A(0,1) = 7; A(0,2) = 3;
    A(1,1) = 4; A(1,2) = -5;
    A(2,2) = 6;
    
    Mat b(3,1,4);
    b(0) = -1; b(2) = 11;
    
    A.print();
    b.print();
    
    
    /*
    PSO test;
    opt::vec lb(2,1,-10), rb(2,1,10);
    test.setGlobalStep(0.1);
    test.setLocalStep(0.3);
    test.setMaxIter(100);
    test.setNumParticles(20);
    test.setdims(lb, rb);
    test.init();
    test.solve();
    */
    
    
    timer.stop();
    printf("Time was %lf\n",timer.getDuration());
    
    
    
    
    
    
    
    
    return 0;
}

