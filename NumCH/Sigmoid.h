//
//  Sigmoid.h
//  Data_Structs
//
//  Created by Christian J Howard on 9/16/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#ifndef __Data_Structs__Sigmoid__
#define __Data_Structs__Sigmoid__

#include "NodeFunc.h"

/*!
 * This represents a Sigmoid operator
 * for a nodal function in a ANN
 *
 * Operator is expressed as:
 * f(x) = (1 + exp(-x))^(-1)
 * where f(x) is bounded by 0 and 1, regardless of x value
 */
class Sigmoid : public NodeFunc {
public:
    virtual ~Sigmoid(){ }
    virtual double operator()(double input);
    virtual double derivative(double input);
};

#endif /* defined(__Data_Structs__Sigmoid__) */
