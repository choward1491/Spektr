//
//  TestExample1.hpp
//  NumCH
//
//  Created by Christian J Howard on 2/6/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef TestExample1_h
#define TestExample1_h

#include "TargetDyn.hpp"
#include "TargetMeas.hpp"
#include "UKF.hpp"
#include "RandomNumberGenerator.hpp"

void runExample1_UKF(){
    
    // Define UKF type
    typedef spektr::filter::UnscentedKF<spektr::TargetDyn, spektr::TargetMeas> UKF;
    
    // Create Random Number Generator
    RandomNumberGenerator rng;
    
    // Create ukf filter
    UKF ukf;
    
    // Init initial conditions
    UKF::Mat x0(4,1,0);
    x0(0) = 0.1; // x pos
    x0(1) = -.1; // y pos
    x0(2) = 0.1;
    x0(3) = 0.01;
    
    // Set initial state estimate for ukf
    ukf.setInitState(x0);
    
    
    // Specify the dynamics noise covariance
    // and state estimate covariance
    for (int i = 0; i < ukf.numState(); i++) {
        for (int j = 0; j < ukf.numState(); j++) {
            ukf.stateNoise(i, j) = (i==j)*1e-2;
        }
        ukf.stateCov(i, i) = 10.0;
    }
    
    // Specify the measurement noise covariance
    for (int i = 0; i < ukf.numMeas(); i++) {
        for (int j = 0; j < ukf.numMeas(); j++) {
            ukf.measNoise(i, j) = 5*(i==j);
        }
    }
    
    // specify time step and set initial time
    double dt = 1e-2, t = dt;
    
    // xt = target velocity
    // xb = initial target location
    // z  = target sensor measurement
    // rnd= random noise component to sensor measurement
    UKF::Mat xt(2,1,0), xb(2,1,0), z(2,1,0);
    UKF::Mat rnd(2,1,0);
    xb(0) = 4;   // in m
    xb(1) = 2.5; // in m
    xt(0) = 1.0; // in m/s
    
    // run sim until time exceeds 5 seconds
    while ( t <= 5 ) {
        
        // compute noise component for sensor
        for (int i = 0; i < 2; i++) {
            rnd(i) = 5.0*rng.gaussRand();
        }
        z = xb + t*xt; // compute exact target pos
        
        // print the true pos of the target
        printf("Truth:\n");
        z.print();
        
        // add noise to z and feed into UKF
        z = z + rnd;
        ukf(t,z);
        
        // print the estimated value for
        // the target's pos
        printf("Estimate:\n");
        ukf.state().print();
        
        // increment time
        t += dt;
    }
}


#endif /* TestExample1_h */
