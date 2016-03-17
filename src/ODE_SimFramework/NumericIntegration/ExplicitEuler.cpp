//
//  ExplicitEuler.cpp
//  NumCH
//
//  Created by Christian J Howard on 8/9/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "ExplicitEuler.hpp"
#include "ModelState.hpp"

void ExplicitEuler::integrate( double time, double dt , double* inOutState, DiffeqList & list){
    double * dqdt = &tmp[0];
    ModelState dqdt_;
    size_t ndim;
    
    if( list.size() > 0 ){
        // compute dqdt
        for (int i = 0; i < list.size(); i++) {
            ndim = list[i]->numDims();
            dqdt_.setAddress(dqdt);
            dqdt_.setNumDims(ndim);
            (*list[i])(time, dqdt_);
            dqdt = dqdt+ndim;
        }
        
        // clear dqdt pointer
        dqdt = 0;
        
        // compute resulting integration step
        for (int i = 0; i < numDims; i++ ){
            inOutState[i] += dt*tmp[i];
        }
    }
}



ExplicitEuler::~ExplicitEuler(){
    clear();
}
void ExplicitEuler::setNumDimensions( int numDimensions ){
    if (numDims != numDimensions && tmp != 0 ) {
        clear();
    }
    numDims = numDimensions;
    create(numDims);
    
}

void ExplicitEuler::clear(){
    if( tmp != 0 ){
        delete [] tmp; tmp = 0;
    }
}
void ExplicitEuler::create( int totalNumber ){
    tmp  = new double[totalNumber];
}



