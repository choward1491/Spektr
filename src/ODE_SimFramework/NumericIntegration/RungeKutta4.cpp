//
//  RungeKutta4.cpp
//  NumCH
//
//  Created by Christian J Howard on 11/21/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "RungeKutta4.hpp"
#include "ModelState.hpp"

void RungeKutta4::integrate( double time, double dt , double* inOutState, DiffeqList & list ){
    
    if( list.size() > 0 ){
        double * dqdt = &k1[0];
        double * tmpState = inOutState;
        
        for (int i = 0; i < numDims; i++) {
            tmp[i] = inOutState[i];
        }
        
        
        // compute k1
        computeDerivatives(time, dqdt, list);
        
        // prepare to compute k2 and then compute it
        computeNewStep(tmp, k1, 0.5*dt, tmpState);
        dqdt = &k2[0];
        computeDerivatives(time + 0.5*dt, dqdt, list);
        
        // prepare to compute k3 and then compute it
        computeNewStep(tmp, k2, 0.5*dt, tmpState);
        dqdt = &k3[0];
        computeDerivatives(time + 0.5*dt, dqdt, list);
        
        // prepare to compute k4 and then compute it
        computeNewStep(tmp, k3, dt, tmpState);
        dqdt = &k4[0];
        computeDerivatives(time + dt, dqdt, list);
        
        
        // clear dqdt pointer
        dqdt = 0;
        
        // reassign correct state
        for (int i = 0; i < numDims; i++) {
            inOutState[i] = tmp[i];
        }
        tmpState = 0;
        
        // compute resulting integration step
        double weight = dt/6.0;
        for (int i = 0; i < numDims; i++ ){
            inOutState[i] += weight*( k1[i]+k4[i] + 2.0*(k2[i]+k3[i]));
        }
    }
}

void RungeKutta4::computeNewStep( double * y0, double* dydt, double dt, double * out){
    for (int i = 0; i < numDims; i++) {
        out[i] = y0[i] + dt*dydt[i];
    }
}

void RungeKutta4::computeDerivatives( double time, double * & dqdt, DiffeqList & list ){
    ModelState dqdt_;
    size_t ndim;
    for (int i = 0; i < list.size(); i++) {
        ndim = list[i]->numDims();
        dqdt_.setAddress(dqdt);
        dqdt_.setNumDims(ndim);
        (*list[i])(time, dqdt_);
        dqdt = dqdt+ndim;
    }
}


RungeKutta4::~RungeKutta4(){
    clear();
}
void RungeKutta4::setNumDimensions( int numDimensions ){
    if (numDims != numDimensions && tmp != 0 ) {
        clear();
    }
    numDims = numDimensions;
    create(numDims);
    
}

void RungeKutta4::clear(){
    if( k1 != 0 ){
        delete [] k1; k1 = 0;
    }
    if( k2 != 0 ){
        delete [] k2; k2 = 0;
    }
    if( k3 != 0 ){
        delete [] k3; k3 = 0;
    }
    if( k4 != 0 ){
        delete [] k4; k4 = 0;
    }
    if( tmp != 0 ){
        delete [] tmp; tmp = 0;
    }
}
void RungeKutta4::create( int totalNumber ){
    k1  = new double[totalNumber];
    k2  = new double[totalNumber];
    k3  = new double[totalNumber];
    k4  = new double[totalNumber];
    tmp = new double[totalNumber];
}