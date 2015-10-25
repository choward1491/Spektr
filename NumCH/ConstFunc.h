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

class ConstFunc : public NodeFunc {
public:
    virtual double operator()(double input);
    virtual double derivative(double input);
    
    
    
};

#endif /* defined(__Data_Structs__ConstFunc__) */
