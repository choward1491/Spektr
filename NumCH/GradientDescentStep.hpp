//
//  GradientDescentStep.hpp
//  Data_Structs
//
//  Created by Christian J Howard on 10/17/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef GradientDescentStep_hpp
#define GradientDescentStep_hpp

#include <stdio.h>
#include "Coordinate.h"

template<int D>
class GradientDescentStep {
    
public:
    typedef Coordinate<D> Gradient;
    typedef Coordinate<(D*(D+1))/2> Hessian;
    
    
    
    GradientDescentStep():alpha(1e-3){}
    
    virtual double getStep( double cost = 0, Gradient * grad = 0, Hessian * hessian = 0 ) const {
        return alpha;
    }
    void setConstantStep( double _alpha ){ alpha = _alpha; }
    
private:
    double alpha;
    
};

#ifndef stepper_cpp
#include "GradientDescentStep.cpp"
#endif


#endif /* GradientDescentStep_hpp */
