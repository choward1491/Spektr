//
//  RungeKutta4.hpp
//  NumCH
//
//  Created by Christian J Howard on 11/21/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef RungeKutta4_hpp
#define RungeKutta4_hpp

#include "DynamicModel.hpp"
#include "AdaptiveArray.h"

class RungeKutta4  {
    
public:
    typedef AdaptiveArray<DynamicModel*> DiffeqList;
    
    RungeKutta4():numDims(-1),k1(0),k2(0),k3(0),k4(0),tmp(0){}
    ~RungeKutta4();
    void setNumDimensions( int numDimensions );
    void integrate( double time, double dt , double* inOutState, DiffeqList & list );
    
private:
    void clear();
    void create( int totalNumber );
    void computeNewStep( double * y0, double* dydt, double dt, double * out);
    void computeDerivatives( double time, double * & dqdt, DiffeqList & list );
    double* k1;
    double* k2;
    double* k3;
    double* k4;
    double* tmp;
    int numDims;
    
};

#endif /* RungeKutta4_hpp */
