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
#include "TestANN_SingleClassification.hpp"
//#include "TestANN_SingleClassificationPSO.hpp"
#include "TestANN_GradientCheck.hpp"
#include "CrossValidation.hpp"
#include "SampleDataSet.hpp"
#include "SampleLinearModel.hpp"
#include "SampleQuadraticModel.hpp"
#include "SampleCubicModel.hpp"
#include "NeuralNet.hpp"

int main(int argc, const char * argv[]) {
    
    RandomNumberGenerator rng;
    NeuralNet net( {1, 1, 1} );
    NeuralNet::Mat x(1,1,5);
    NeuralNet::Mat o(1,1,0);
    
    for(int i = 0; i < net.numWeights(); ++i){
        double value = rng.rand()*3-1.5;
        net.weightAt(i) = value;
    }
    printf("Number of weights = %i\n",net.numWeights());
    net.printWeights();
    
    o = net(x);
    x.print();
    o.print();
    
    /*CVLTest cv_test;
    printf("CVL Error = %lf\n",cv_test.evaluate() );
    
    CVQTest cv_test2;
    printf("CVQ Error = %lf\n",cv_test2.evaluate() );
    
    CVCTest cv_test3;
    printf("CVC Error = %lf\n",cv_test3.evaluate() );*/
    
    
    //testLocalRegression1D();
    //testLocalRegression2D();
    //runExample1_UKF();
    //runExample1_ADELINE();
    //runExample1_NeuralKalman();
    //TestANN_Autoencoder();
    //TestANN_SingleClassification();
    //TestANN_SingleClassificationPSO();
    
    
    
    
    // exit
    return 0;
}

