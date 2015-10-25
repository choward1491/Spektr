//
//  NodeFunc.h
//  Data_Structs
//
//  Created by Christian J Howard on 9/16/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#ifndef __Data_Structs__NodeFunc__
#define __Data_Structs__NodeFunc__

#include <stdio.h>
#include <math.h>

/*!
 * This class represents a nodal function
 * for a Neural Network. It will have a normal
 * operator and a derivative operator defined
 *
 * Defaults as a linear operator
 *
 */
class NodeFunc {
public:
    
    virtual ~NodeFunc(){ }
    
    // Normal nonlinear operator on scalar input
    virtual double operator()(double input) { return input; }
    
    // Derivative of the normal operator, as a function of a scalar input
    virtual double derivative(double input) { return 1; }
    
};

#endif /* defined(__Data_Structs__NodeFunc__) */
