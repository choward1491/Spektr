//
//  Function.hpp
//  NumCH
//
//  Created by Christian J Howard on 8/10/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef Function_cpp
#define Function_cpp

#include <stdio.h>

#include "Vect.hpp"

namespace NumCH {

template< int NumInput, int NumOutput, typename NumType>
class Function {
    
public:
    
    Function(){}
    
    
    void operator()( const Vect<NumType> & input, Vect<NumType> & output ) const {
        if( input.size() == NumInput && output.size() == NumOutput ){
            compute(input.elements, output.elements);
        }
    }
    void operator()( const NumType * input, NumType * output ) const {
        compute(input, output);
    }
    
    void calc( NumType * input, NumType * output ) const {
        compute(input, output);
    }
    
    int dimensionOfInput() const { return NumInput; }
    int dimensionOfOutput() const { return NumOutput; }
    bool isNumberOfInput( const int number ) const { return number == NumInput; }
    bool isNumberOfOutput( const int number ) const { return number == NumOutput; }
    
protected:
    virtual void compute( const NumType * & input, NumType * & output ) const = 0;
    
    
};






class Quadratic : public Function<1, 2, double> {
public:
        
protected:
    virtual void compute( const double * & input, double * & output ) const {
        double dx = input[0] - 50;
        //output[0] = dx*dx*dx*dx;
        //output[1] = 4*dx*dx*dx;
        output[0] = dx*dx;
        output[1] = 2*dx;
    }
    
    
};
    
}

#endif /* Function_cpp */
