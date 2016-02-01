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

typedef opt::pso<opt::Rosenbrock, opt::RandomInit> PSO;
typedef la::Matrix<double, Symmetric>   Sym;
typedef la::Matrix<double, General>     Mat;
typedef la::Matrix<double, Sparse>      SMat;
typedef la::Matrix<double, Lower>       LMat;
typedef la::Matrix<double, Diagonal>    Diag;

int main(int argc, const char * argv[]) {
    
    Sym A(2,2);
    A(0,0) = 4; A(0,1) = 1;
    A(1,1) = 2;
    
    LMat L; Diag D;
    la::LDL(A,L,D);
    A.print();
    L.print();
    D.print();
    
    
    
    
    
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
    
    return 0;
}

