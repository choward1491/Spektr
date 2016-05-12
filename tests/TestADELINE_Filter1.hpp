//
//  TestADELINE_Filter1.hpp
//  Spektr
//
//  Created by Christian J Howard on 5/3/16.
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

#ifndef TestADELINE_Filter1_h
#define TestADELINE_Filter1_h

#include "ADELINE.hpp"
#include "RandomNumberGenerator.hpp"
#include "FileObject.hpp"

void runExample1_ADELINE(){
    
    // File Handle
    FileObject file;
    file.openFile("/Users/christianjhoward/adeline.txt", FileObject::Write);
    
    // Define ADELINE filter type
    typedef spektr::filter::ADELINE ADELINE;
    
    // Create Random Number Generator
    RandomNumberGenerator rng;
    
    // Create adeline filter
    ADELINE filter(5);
    filter.setMaxLearningIterations(3);
    filter.setLearningStepSize(1e-2);
    
    // Init initial conditions
    ADELINE::Mat x0(2,1,0);
    x0(0) = 3.7; // x pos
    x0(1) = 2.4; // y pos
    
    // Set initial state estimate for ukf
    filter.setInitState(x0);
    
    // specify time step and set initial time
    double dt = 1e-2, t = dt;
    
    // xt = target velocity
    // xb = initial target location
    // z  = target sensor measurement
    // rnd= random noise component to sensor measurement
    ADELINE::Mat xt(2,1,0), xb(2,1,0), z(2,1,0), truth(2,1,0);
    ADELINE::Mat rnd(2,1,0);
    xb(0) = 4;   // in m
    xb(1) = 2.5; // in m
    xt(0) = 1.0; // in m/s
    
    // run sim until time exceeds 5 seconds
    while ( t <= 5 ) {
        
        // compute noise component for sensor
        for (int i = 0; i < 2; i++) {
            rnd(i) = 1.0*rng.gaussRand();
        }
        truth = xb + t*xt; // compute exact target pos
        
        // print the true pos of the target
        printf("Truth:\n");
        truth.print();
        
        // add noise to z and feed into filter
        z = truth + rnd;
        filter(t,z);
        
        // print the estimated value for
        // the target's pos
        printf("Estimate:\n");
        filter.state().print();
        
        fprintf(file.ref(), "%lf, %lf, %lf, %lf, %lf, %lf\n",truth[0],truth[1],z[0],z[1],filter.state()[0],filter.state()[1]);
        
        // increment time
        t += dt;
    }
}


#endif /* TestADELINE_Filter1_h */
