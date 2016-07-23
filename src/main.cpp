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
//#include "TestANN_SingleClassificationPSO.hpp"
#include "TestANN_GradientCheck.hpp"
#include "CrossValidation.hpp"
#include "SampleDataSet.hpp"
#include "SampleLinearModel.hpp"
#include "SampleQuadraticModel.hpp"
#include "SampleCubicModel.hpp"

typedef CrossValidation<30, QuadraticDataSet, LinearModel> CVLTest;
typedef CrossValidation<30, QuadraticDataSet, QuadraticModel> CVQTest;
typedef CrossValidation<30, QuadraticDataSet, CubicModel> CVCTest;

int main(int argc, const char * argv[]) {
    
    CVLTest cv_test;
    printf("CVL Error = %lf\n",cv_test.evaluate() );
    
    CVQTest cv_test2;
    printf("CVQ Error = %lf\n",cv_test2.evaluate() );
    
    CVCTest cv_test3;
    printf("CVC Error = %lf\n",cv_test3.evaluate() );
    
    
    //testLocalRegression1D();
    //testLocalRegression2D();
    //runExample1_UKF();
    //runExample1_ADELINE();
    //runExample1_NeuralKalman();
    //TestANN_Autoencoder();
    //TestANN_SingleClassificationPSO();
    
    
    
    
    // exit
    return 0;
}

