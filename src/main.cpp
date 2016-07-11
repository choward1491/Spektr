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
#include "TestNeuralKalmanFilter.hpp"
//#include "TestANN_Autoencoder.hpp"
//#include "TestANN_SingleClassification.hpp"
#include "TestANN_SingleClassificationPSO.hpp"
#include "TestANN_GradientCheck.hpp"

int main(int argc, const char * argv[]) {
    
    //testLocalRegression1D();
    //testLocalRegression2D();
    runExample1_UKF();
    //runExample1_ADELINE();
    //runExample1_NeuralKalman();
    
    //TestANN_Autoencoder();
    //TestANN_SingleClassificationPSO();
    
    /*la::SMat<double> A(3,3,2);
    A(0,1) = -1; A(1,2) = -1; A(0,2) = 0;
    A.print();
    
    la::LMat<double> L(3,3,0);
    la::cholesky(A, L);
    L.print();
    
    la::Mat<double> u(3,1,0);
    u(0) = 0.2; u(1) = 0.1; u(2) = -0.01;
    la::Mat<double> ut = u;
    ut.t();
    
    la::Mat<double> D = (u*ut);
    D.print();
    
    L.rankOneUpdate(u);
    L.print();
    la::Mat<double> Lt = L;
    Lt.t();
    
    la::SMat<double> A2 = L*Lt;
    A2.print();
    
    la::SMat<double> A3 = A + D;
    la::SMat<double> del = A2 - A3;
    
    del.print();*/
    
    
    
    // exit
    return 0;
}

