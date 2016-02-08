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

#include "GradientBase.hpp"
#include "ConstantStep.hpp"
#include "Rosenbrock.hpp"
#include "Parabola2D.hpp"
#include "TestMPSO1.hpp"

typedef opt::gradient<opt::Parabola2D, opt::ConstantStep<opt::Parabola2D> > gradient;

int main(int argc, const char * argv[]) {
    
    gradient grad;
    grad.setMaxIter(100);
    grad.setMomentumCoef(0.1);
    grad.setTolerance(1e-3);
    grad.step.setStepSize(1e-1);
    
    Mat guess(2,1,0);
    guess(0) = 20;
    guess(1) = 5;
    
    grad.setGuess(guess);
    
    Timer timer;
    timer.start();
    
    grad.init();
    grad.solve();
    grad.soln().print();
    
    
    
    timer.stop();
    printf("Time was %lf\n",timer.getDuration());
    
    
    return 0;
}

