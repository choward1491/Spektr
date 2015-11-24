//
//  GradientDescent.cpp
//  Data_Structs
//
//  Created by Christian J Howard on 10/17/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "GradientDescent.hpp"

#ifndef gd_cpp
#define gd_cpp

template<int D>
GradientDescent<D>::GradientDescent( Cost * costFunc ){
    func = costFunc;
    maxIter = 100;
    bestCost = 1e100;
    gamma = 0.5;
}

template<int D>
void GradientDescent<D>::runOptimization( State & guess ){
    int iter = 0;
    double cost = 0;
    State curr = guess;
    State grad;
    typename Stepper::Hessian hessian;
    double alpha = 1e-2;
    double del;
    
    if( func != 0 ){
    
        while( iter < maxIter ){
            cost = (*func).gradient(curr, grad, &hessian);
            
            if( cost < bestCost ){
                bestCost = cost;
                bestState = curr;
            }
            
            alpha = (*step).getStep( cost, &grad, &hessian );
            
            for (int i = 0; i < D; i++) {
                del = -alpha*grad[i];
                curr[i] = gamma*momentum[i] + curr[i] + del;
                momentum[i] = del;
            }
            
            iter++;
            printf("Gradient Descent Step %i\n", iter);
            printf("Current Cost = %lf\n", cost);
            printf("Best Gradient Descent Cost = %lf\n\n", bestCost);
        }
        
    }
}

#endif