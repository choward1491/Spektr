//
//  Sigmoid.cpp
//  Data_Structs
//
//  Created by Christian J Howard on 9/16/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#include "Sigmoid.h"

double Sigmoid::operator()(double input){
    return 1.0 / (1 + exp(-input));
}

double Sigmoid::derivative(double input){
    double y = (*this)(input);
    return y*(1-y);
}