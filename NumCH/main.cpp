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
#include "Cholesky.hpp"
#include "LDL.hpp"
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
    
    LMat A(3,3,1);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            A(i,j) = 40*rng.rand();
        }
    }
    
    Diag I(3,3,1);
    Mat Ainv(3,3);
    la::solve(A, A, Ainv);
    
    A.print();
    Ainv.print();
    Mat I2 = A*Ainv;
    I2.print();
    
    
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

