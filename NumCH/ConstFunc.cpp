//
//  ConstFunc.cpp
//  Data_Structs
//
//  Created by Christian J Howard on 9/16/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#include "ConstFunc.h"


double ConstFunc::operator()(double input){
    return input;
}
double ConstFunc::derivative(double input){
    return 1;
}