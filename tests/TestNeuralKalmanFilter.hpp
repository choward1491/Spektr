//
//  TestNeuralKalmanFilter.hpp
//  Spektr
//
//  Created by Christian J Howard on 5/12/16.
//
//  The MIT License (MIT)
//    Copyright © 2016 Christian Howard. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
//
//

#ifndef TestNeuralKalmanFilter_h
#define TestNeuralKalmanFilter_h

#include "TargetDyn.hpp"
#include "TargetMeas.hpp"
#include "UKF.hpp"
#include "NeuralFilter.hpp"
#include "RandomNumberGenerator.hpp"
#include "FileObject.hpp"
#include <math.h>

void runExample1_NeuralKalman(){
    
    // File Handle
    FileObject file;
    
    
    // Define NeuralFilter filter type
    typedef spektr::filter::NeuralFilter NeuralFilter;
    
    // Define UKF type
    typedef spektr::filter::UnscentedKF<spektr::TargetDyn, spektr::TargetMeas> UKF;
    
    // Create Random Number Generator
    RandomNumberGenerator rng;
    
    // Create ukf filter
    UKF ukf;
    
    // Create adeline filter
    NeuralFilter filter(5);
    filter.setMaxLearningIterations(3);
    filter.setLearningStepSize(1e-2);
    
    // Init initial conditions
    UKF::Mat x0(4,1,0);
    x0(0) = 0; // x pos
    x0(1) = 0; // y pos
    
    // Set initial state estimate for ukf
    ukf.setInitState(x0);
    
    
    // Specify the dynamics noise covariance
    // and state estimate covariance
    for (int i = 0; i < ukf.numState(); i++) {
        for (int j = 0; j < ukf.numState(); j++) {
            ukf.stateNoise(i, j) = (i==j) * 2e-4 + 0*(i!=j);
        }
        ukf.stateCov(i, i) = 5;
    }
    
    // Specify the measurement noise covariance
    for (int i = 0; i < ukf.numMeas(); i++) {
        for (int j = 0; j < ukf.numMeas(); j++) {
            ukf.measNoise(i, j) = 0.1*(i==j) - 0*1/(i+j+1)*(i!=j);
        }
    }
    
    // Set initial state estimate for ukf
    x0.resize(2, 1);
    x0(0) = 0; x0(1) = 0;
    filter.setInitState(x0);
    
    // specify time step and set initial time
    double dt = 1e-2, t = dt;
    
    // xt = target velocity
    // xb = initial target location
    // z  = target sensor measurement
    // rnd= random noise component to sensor measurement
    NeuralFilter::Mat xt(2,1,0), xb(2,1,0), z(2,1,0), truth(2,1,0);
    NeuralFilter::Mat rnd(2,1,0);
    xb(0) = 4;   // in m
    xb(1) = 2.5; // in m
    xt(0) = 1.0; // in m/s
    
    file.openFile("/Users/christianjhoward/neuralKalman.txt", FileObject::Write);
    
    // run sim until time exceeds 5 seconds
    while ( t <= 10 ) {
        
        // compute noise component for sensor
        for (int i = 0; i < 2; i++) {
            rnd(i) = 1*rng.gaussRand();
        }
        if( t <= 5 ){
            truth = xb + 0.5*t*t; // compute exact target pos
        }else{
            truth = xb + 0.5*5*5 - 0.7*(t-5)*(t-5);
        }
        
        // print the true pos of the target
        printf("Truth:\n");
        truth.print();
        
        // add noise to z and feed into filter
        z = truth + rnd;
        filter.truth = truth;
        filter(t,z);
        ukf(t,filter.state());
        double alpha = 0.5, beta = 1.0-alpha;
        x0 = alpha*filter.state() + beta*x0;
        
        // print the estimated value for
        // the target's pos
        printf("Estimate1:\n");
        filter.state().print();
        
        printf("Estimate2:\n");
        x0.print();
        //ukf.state().print();
        //ukf.stateCov().print();
        
        fprintf(file.ref(), "%lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf\n",truth[0],truth[1],z[0],z[1],
                filter.state()[0],filter.state()[1],ukf.state()[0],ukf.state()[1], filter.ratio[0],filter.ratio[1],
                filter.meas_error[0],filter.meas_error[1],filter.avg_error[0],filter.avg_error[1]);
        
        // increment time
        t += dt;
    }
    
    
}


#endif /* TestNeuralKalmanFilter_h */
