//
//  CostFunc.h
//  Data_Structs
//
//  Created by Christian J Howard on 9/4/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#ifndef __Data_Structs__CostFunc__
#define __Data_Structs__CostFunc__

#include <stdio.h>
#include "Coordinate.h"

template<int Dim>
class CostFunc {
public:
    typedef Coordinate<Dim> State;
    typedef Coordinate<(Dim*(Dim+1))/2> Hessian;
    virtual double operator()( State & x ) = 0;
    virtual double gradient( State & x , State & gradient, Hessian * hessian = 0 ) { return 0; }
    
};

#endif /* defined(__Data_Structs__CostFunc__) */
