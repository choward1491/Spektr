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
//#include "Vect.hpp"




/*!
 * This is a template class to represent a M-D -> N-D mapping
 *
 */
/*template< int NumInput, int NumOutput, typename NumType>
class Function {
    
public:
    
    // Default constructor and destructor
    Function(){}
    virtual ~Function(){}
    
    
    
    
    // Operators for computing an output given an input
    void operator()( const Vect<NumType> & input, Vect<NumType> & output ) const {
        if( input.size() == NumInput && output.size() == NumOutput ){
            compute(input.elements, output.elements);
        }
    }
    void operator()( const NumType * input, NumType * output ) const {
        compute(input, output);
    }
    
    void calc( const NumType * input, NumType * output ) const {
        compute(input, output);
    }
    
    
    
    // Get the input and output dimensions
    int dimensionOfInput() const { return NumInput; }
    int dimensionOfOutput() const { return NumOutput; }
    
    // check if a value is the number of inputs/outputs
    bool isNumberOfInput( const int number ) const { return number == NumInput; }
    bool isNumberOfOutput( const int number ) const { return number == NumOutput; }
    
protected:
    
    // virtual method to be rewritten
    virtual void compute( const NumType * & input, NumType * & output ) const = 0;
    
    
};

    */


#endif /* Function_cpp */
