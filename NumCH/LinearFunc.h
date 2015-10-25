//
//  ConstFunc.h
//  Data_Structs
//
//  Created by Christian J Howard on 9/16/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#ifndef __Data_Structs__ConstFunc__
#define __Data_Structs__ConstFunc__

#include "NodeFunc.h"

/*!
 * Method to represent linear operator
 * and it's derivative
 *
 */
class LinearFunc : public NodeFunc {
public:
    virtual ~LinearFunc(){ }
    virtual double operator()(double input);
    virtual double derivative(double input);
    
};

#endif /* defined(__Data_Structs__ConstFunc__) */
