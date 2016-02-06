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
    
    RandomNumberGenerator rng;
    filter::UnscentedKF<TargetDyn, TargetMeas> ukf;
    Mat x0(4,1,0);
    x0(0) = 0;
    x0(1) = 0;
    
    ukf.setInitState(x0);
    
    
    for (int i = 0; i < ukf.numState(); i++) {
        for (int j = 0; j < ukf.numState(); j++) {
            ukf.stateNoise(i, j) = (i==j)*10;
        }
        ukf.stateCov(i, i) = 30.0;
    }
    
    for (int i = 0; i < ukf.numMeas(); i++) {
        for (int j = 0; j < ukf.numMeas(); j++) {
            ukf.measNoise(i, j) = 1*(i==j);
        }
    }
    
    
    double dt = 1e-2, t = dt;
    Mat xt(2,1,0), xb(2,1,0), z(2,1,0);
    Mat rnd(2,1,0);
    xb(0) = 4;
    xb(1) = 2.5;
    
    xt(0) = 1.0;
    
    while ( t <= 5 ) {
        
        for (int i = 0; i < 2; i++) {
            rnd(i) = 0.01*rng.gaussRand();
        }
        z = xb + t*xt;
        printf("Truth:\n");
        z.print();
        z = z + rnd;
        ukf(t,z);
        
        printf("Estimate:\n");
        ukf.state().print();
        
        t += dt;
    }
}


#endif /* TestExample1_h */
