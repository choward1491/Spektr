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

/*!
 * This is a class that represents a cost function.
 * This cost function can be inherited and, depending on the optimization algorithm,
 * different methods could be overwritten.
 *
 * For derivative free methods, just overwrite the operator() method
 * For gradient based methods, overwrite both the operator() and gradient methods.
 * Note that for gradient methods, you don't have to use a Hessian
 *
 */
template<int Dim>
class CostFunc {
public:
    typedef Coordinate<Dim>                 State;
    typedef Coordinate<(Dim*(Dim+1))/2>     Hessian;
    
    virtual ~CostFunc(){ }
    virtual double operator()( State & x ) = 0;
    virtual double gradient( State & x , State & gradient, Hessian * hessian = 0 ) { return 0; }
    
};

#endif /* defined(__Data_Structs__CostFunc__) */
