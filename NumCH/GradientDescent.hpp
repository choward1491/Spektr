//
//  GradientDescent.hpp
//  NumCH
//
//  Created by Christian J Howard on 8/16/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef GradientDescent_cpp
#define GradientDescent_cpp

#include <stdio.h>
#include "UOptimizer.hpp"

namespace NumCH {


template<int I, int O>
class GradientDescent : public UOptimizer<I, O, double> {
    
public:
    
    
    
    
    
protected:
    
    typedef Function<I,O, double> Func;
    
    virtual void updateGuess( double * guess, double * evalInfo, const Func & func );
    virtual bool solvingIsDone( double * guess, double * evalInfo, double & threshold );
    
private:
    double findStepSize( double * guess, double * evalInfo, const Func & func ) const;
    
    
    
};




template<int I, int O>
void GradientDescent<I,O>::updateGuess( double * guess, double * gradient, const Func & func ){
    
    //
    // Obtain step size via line search
    //
    double stepsize = findStepSize(guess, gradient, func);
    
    
    
    //
    // Update the guess based on the suboptimal step
    //
    for (int i = 0; i < I; i++) {
        guess[i] = guess[i] - stepsize * gradient[i+1];
    }
}






template<int I, int O>
bool GradientDescent<I,O>::solvingIsDone( double * guess, double * evalInfo, double & threshold ){
    double gradientL2Norm = 0.0;
    
    for (int i = 1; i < O; i++) {
        gradientL2Norm = gradientL2Norm + evalInfo[i]*evalInfo[i];
    }
    
    return  (*this).numIters > 0 && ( (gradientL2Norm <= threshold) || (*this).check());
}








template<int I, int O>
double GradientDescent<I,O>::findStepSize( double * guess, double * gradient, const Func & func ) const{
    
    // Initialize original and best cost
    double origCost = gradient[0];
    double bestCost = origCost;
    
    // Initialize temp arrays
    double in[I];
    double out[O];
    
    // Initialize best alpha and alpha used
    // for line search
    double bestAlpha = 100000.0;
    double alpha = bestAlpha;
    
    // Initialize line search
    bool done = false;
    
    // counter
    bool doneOneIteration = false;
    
    
    
    
    //
    // Iterate through step values until the
    // appropriate suboptimizing step value
    // is located using a simple line search
    //
    while( !done ){
        
        for (int i = 0; i < I; i++) {
            in[i] = guess[i] - alpha * gradient[i+1];
        }
        
        func(in, out);
        
        if( !doneOneIteration || out[0] < bestCost ){
            bestCost = out[0];
            bestAlpha = alpha;
            alpha *= 0.1;
            doneOneIteration = true;
        }else{
            done = true;
        }
    }
    
    
    
    
    
    
    
    
    //
    // Return step size
    //
    return bestAlpha;
}

    
}


#endif /* GradientDescent_cpp */
