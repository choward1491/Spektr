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


/*!
 * Class designed to compute the Gradient Descent optimization
 * of some particular cost function
 *
 */
template<int dim>
class GradientDescent {
public:
    // useful typedefs
    typedef Coordinate<dim>             State;
    typedef CostFunc<dim>               Cost;
    typedef GradientDescentStep<dim>    Stepper;
    
    
    
    
    
    // Initialize gradient descent object via cost function reference
    GradientDescent( Cost * costFunc );
    
    // method to run the optimization
    void runOptimization( State & guess );
    
    
    
    
    
    // Set max iterations
    void setMaxIterations( int _maxIter ){ maxIter = _maxIter; }
    
    // Set stepsize function (must be set before running optimiztion)
    void setStepperFunction( Stepper * stepper ){ step = stepper; }
    
    // Set momentum coefficient
    void setMomentumCoefficient( double _gamma ){ gamma = _gamma; }
    
    
    
    
    
    
    // Method to get best solution over whole optimization process
    State getBestSolution() const { return bestState; }
    
    // Method to get the best cost for the associated best solution
    double getBestCost() const { return bestCost; }
    
    
private:
    // cost func reference
    Cost* func;
    
    // best state and best cost
    State bestState;
    double bestCost;
    
    // max number of iterations
    int maxIter;
    
    // Gradient Descent Step Size functor reference
    Stepper* step;
    
    // Momentum state
    State momentum;
    
    // Momentum coefficient (weighs how much of momentum to use in update)
    double gamma;
    
    
    
};


#ifndef gd_cpp
#include "GradientDescent.cpp"
#endif


#endif /* GradientDescent_hpp */
