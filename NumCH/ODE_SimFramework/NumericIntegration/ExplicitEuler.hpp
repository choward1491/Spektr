//
//  ExplicitEuler.hpp
//  NumCH
//
//  Created by Christian J Howard on 8/9/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef ExplicitEuler_cpp
#define ExplicitEuler_cpp


#include "DynamicModel.hpp"
#include "AdaptiveArray.h"


class ExplicitEuler  {
    
public:
    typedef AdaptiveArray<DynamicModel*> DiffeqList;
    
    ExplicitEuler():numDims(-1),tmp(0){}
    ~ExplicitEuler();
    void setNumDimensions( int numDimensions );
    void integrate( double time, double dt , double* inOutState, DiffeqList & list);

private:
    void clear();
    void create( int totalNumber );
    double* tmp;
    int numDims;
    
};

#endif /* ExplicitEuler_cpp */
