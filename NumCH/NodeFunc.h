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


class NodeFunc {
public:
    virtual double operator()(double input) { return input; }
    virtual double derivative(double input) { return 1; }
    
};

#endif /* defined(__Data_Structs__NodeFunc__) */
