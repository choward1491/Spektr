//
//  UnconstrainedOptimization.hpp
//  NumCH
//
//  Created by Christian J Howard on 8/10/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef UnconstrainedOptimization_cpp
#define UnconstrainedOptimization_cpp

#include <stdio.h>
#include "Function.hpp"

namespace NumCH {

template<int I, int O, typename T>
class UOptimizer {
    
public:
    
    UOptimizer(){
        numIters = 0;
        maxIters = 100;
        thresh = T(1e-2);
    }
    
    void setMaxIterations( int _maxIters ){ maxIters = _maxIters; }
    void setStopThreshold( T _thresh ){ thresh = _thresh; }
    
    
    
    virtual Vect<T> solve( const Vect<T> & initialGuess, const Function<I, O, T> & func ){
        
        T guess[I];
        T output[O];
        numIters = 0;
        
        for (int i = 0; i < I; i++) {
            guess[i] = initialGuess[i];
        }
        
        func(guess, output);
        
        while ( !solvingIsDone(guess, output, thresh)  ) {
            updateGuess(guess, output, func);
            func(guess, output);
            numIters = numIters + 1;
        }
        
        
        Vect<T> solution(I);
        for (int i = 0; i < I; i++) {
            solution[i] = guess[i];
        }
        
        
        return solution;
        
    }
    
    
    bool check() const { return numIters >= maxIters; }
    unsigned int numIters;
    unsigned int maxIters;
    
    
    
protected:
    
    
    virtual void updateGuess( T * guess, T * evalInfo, const Function<I, O, T> & func ) = 0;
    virtual bool solvingIsDone( T * guess, T * evalInfo, T & threshold ) = 0;
    
private:
    
    T thresh;
    
    
};


    
}


#endif /* UnconstrainedOptimization_cpp */
