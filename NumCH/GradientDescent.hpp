//
//  GradientDescent.hpp
//  Data_Structs
//
//  Created by Christian J Howard on 10/17/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef GradientDescent_hpp
#define GradientDescent_hpp

#include <stdio.h>
#include "Coordinate.h"
#include "CostFunc.h"
#include "GradientDescentStep.hpp"



template<int dim>
class GradientDescent {
public:
    typedef Coordinate<dim> State;
    typedef CostFunc<dim> Cost;
    typedef GradientDescentStep<dim> Stepper;
    
    
    GradientDescent( Cost * costFunc );
    void runOptimization( State & guess );
    
    
    
    
    void setMaxIterations( int _maxIter ){ maxIter = _maxIter; }
    void setStepperFunction( Stepper * stepper ){ step = stepper; }
    void setMomentumCoefficient( double _gamma ){ gamma = _gamma; }
    
    State getBestSolution() const { return bestState; }
    double getBestCost() const { return bestCost; }
    
    
private:
    Cost* func;
    State bestState;
    double bestCost;
    int maxIter;
    Stepper* step;
    State momentum;
    double gamma;
    
    
    
};


#ifndef gd_cpp
#include "GradientDescent.cpp"
#endif


#endif /* GradientDescent_hpp */
