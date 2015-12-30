//
//  ExplicitTrapezoidal.hpp
//  NumCH
//
//  Created by Christian J Howard on 11/22/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef ExplicitTrapezoidal_hpp
#define ExplicitTrapezoidal_hpp

#include "DynamicModel.hpp"
#include "AdaptiveArray.h"

class ExplicitTrapezoidal {
    
public:
    typedef AdaptiveArray<DynamicModel*> DiffeqList;
    
    ExplicitTrapezoidal():numDims(-1),k1(0),k2(0){}
    ~ExplicitTrapezoidal();
    void setNumDimensions( int numDimensions );
    void integrate( double time, double dt , double* inOutState, DiffeqList & list );
    
private:
    void clear();
    void create( int totalNumber );
    void computeNewStep( double * y0, double* dydt, double dt, double * out);
    void computeDerivatives( double time, double * & dqdt, DiffeqList & list );
    double* k1;
    double* k2;
    double* tmp;
    
    int numDims;
    
};

#endif /* ExplicitTrapezoidal_hpp */
