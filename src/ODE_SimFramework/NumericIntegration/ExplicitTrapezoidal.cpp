//
//  ExplicitTrapezoidal.cpp
//  NumCH
//
//  Created by Christian J Howard on 11/22/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "ExplicitTrapezoidal.hpp"


void ExplicitTrapezoidal::integrate( double time, double dt , double* inOutState, DiffeqList & list){
    
    if( list.size() > 0 ){
        double * dqdt = &k1[0];
        double * tmpState = inOutState;
        
        for (int i = 0; i < numDims; i++) {
            tmp[i] = inOutState[i];
        }
        
        
        // compute k1
        computeDerivatives(time, dqdt, list);
        
        // prepare to compute k2 and then compute it
        computeNewStep(tmp, k1, dt, tmpState);
        dqdt = &k2[0];
        computeDerivatives(time + dt, dqdt, list);
        
        
        // clear dqdt pointer
        dqdt = 0;
        
        // reassign correct state
        for (int i = 0; i < numDims; i++) {
            inOutState[i] = tmp[i];
        }
        tmpState = 0;
        
        // compute resulting integration step
        double weight = dt/2.0;
        for (int i = 0; i < numDims; i++ ){
            inOutState[i] += weight*( k1[i]+k2[i] );
        }
    }
}

void ExplicitTrapezoidal::computeNewStep( double * y0, double* dydt, double dt, double * out){
    for (int i = 0; i < numDims; i++) {
        out[i] = y0[i] + dt*dydt[i];
    }
}

void ExplicitTrapezoidal::computeDerivatives( double time, double * & dqdt, DiffeqList & list ){
    for (int i = 0; i < list.size(); i++) {
        (*list[i])(time, dqdt);
        dqdt = dqdt+list[i]->numDims();
    }
}


ExplicitTrapezoidal::~ExplicitTrapezoidal(){
    clear();
}
void ExplicitTrapezoidal::setNumDimensions( int numDimensions ){
    if (numDims != numDimensions && tmp != 0 ) {
        clear();
    }
    numDims = numDimensions;
    create(numDims);
    
}

void ExplicitTrapezoidal::clear(){
    if( k1 != 0 ){
        delete [] k1; k1 = 0;
    }
    if( k2 != 0 ){
        delete [] k2; k2 = 0;
    }
    if( tmp != 0 ){
        delete [] tmp; tmp = 0;
    }
}
void ExplicitTrapezoidal::create( int totalNumber ){
    k1  = new double[totalNumber];
    k2  = new double[totalNumber];
    tmp = new double[totalNumber];
}