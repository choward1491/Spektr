//
//  GenIntegrator.hpp
//  NumCH
//
//  Created by Christian J Howard on 8/8/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef GenIntegrator_cpp
#define GenIntegrator_cpp

#include "AdaptiveArray.h"
#include "DynamicModel.hpp"

typedef AdaptiveArray<DynamicModel*> DiffeqList;


enum IntegratorType { ExplicitEuler, RungeKutta4, ExplicitTrapezoidal };


class GenIntegrator {
    
public:
    
    GenIntegrator();
    virtual void setNumDimensions( int numDimensions ) = 0;
    virtual ~GenIntegrator();
    virtual void integrate( double time, double dt , double* lastState, DiffeqList & list ) = 0;
    
protected:
    
    int numDims;
    
};



#endif /* GenIntegrator_cpp */
