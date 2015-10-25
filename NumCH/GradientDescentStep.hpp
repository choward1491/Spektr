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



/*!
 * This class represents the functionality that will
 * product a gradient descent step size. This version
 * defaults to a constant step size value.
 *
 */
template<int D>
class GradientDescentStep {
    
public:
    // useful typedefs
    typedef Coordinate<D> Gradient;
    typedef Coordinate<(D*(D+1))/2> Hessian;
    
    
    // Constructor
    GradientDescentStep():alpha(1e-3){}
    virtual ~GradientDescentStep(){}
    
    // method to get a step, which can be based on a gradient and hessian
    virtual double getStep( double cost = 0, Gradient * grad = 0, Hessian * hessian = 0 ) const {
        return alpha;
    }
    
    // method to set the alpha to a constant value
    void setConstantStep( double _alpha ){ alpha = _alpha; }
    
private:
    double alpha;
    
};

#ifndef stepper_cpp
#include "GradientDescentStep.cpp"
#endif


#endif /* GradientDescentStep_hpp */
