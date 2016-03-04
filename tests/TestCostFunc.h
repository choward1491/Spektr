//
//  TestCostFunc.h
//  Data_Structs
//
//  Created by Christian J Howard on 9/4/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#ifndef Data_Structs_TestCostFunc_h
#define Data_Structs_TestCostFunc_h

#include "CostFunc.h"
#include <math.h>


template<int Dim>
class TestCost : public CostFunc<Dim> {
public:
    typedef Coordinate<Dim> State;
    virtual double operator()( State & x ){
        /*double a1 = cos(x[0]);
        double a2 = exp( -(x[0]*x[0]) );
        return -a1*a2;*/
        
        //double a1 = fabs(x[0]);
        //return a1;
        
        double u = x[0];
        double y = x[1];
        
        return u*u + y*y;
    }
    
};



#endif
