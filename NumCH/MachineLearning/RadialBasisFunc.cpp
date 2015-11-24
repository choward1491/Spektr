//
//  RadialBasisFunc.cpp
//  Data_Structs
//
//  Created by Christian J Howard on 9/6/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#include "RadialBasisFunc.h"

#ifndef _gaussrbf_cpp_
#define _gaussrbf_cpp_

// Null constructor
template<int Dim>
RadialBasisFunc<Dim>::RadialBasisFunc(){
    assignConstSigma(1.0);
    coef = 0;
}


// Method to allow changing the center of the RBF
template<int Dim>
void RadialBasisFunc<Dim>::assignCenter( const Coordinate<Dim> & _center ){
    center = _center;
}


// Method to allow changing the standard deviation vector.
// This vector of sigmas represent having a different deviation for
// each dimension of the input vector
template<int Dim>
void RadialBasisFunc<Dim>::assignSigma ( const Coordinate<Dim> & _sigma  ){ sigma  = _sigma;  }



// Method to set sigma vector to a constant value
template<int Dim>
void RadialBasisFunc<Dim>::assignConstSigma( double newSigma ){
    for (int i = 0; i < Dim; i++) {
        sigma[i] = newSigma;
    }
}



// This is to assign a coefficient to multiply the result
// of this RBF by
template<int Dim>
void RadialBasisFunc<Dim>::assignCoefficient( double _coef ){ coef = _coef; }


// Operator method to operate on an input N dimensional vector
template<int Dim>
double RadialBasisFunc<Dim>::operator()( const Coordinate<Dim> & x ){
    double value = 0;
    double tmp = 0;
    
    // If coefficient is 0, return 0
    if( coef == 0.0 ){ return 0.0; };
    
    
    // Loop through each component of the input
    for (int i = 0; i < Dim; i++ ) {
        
        
        // Find normalized value of component radius
        tmp = (center[i]-x[i])/sigma[i];
        
        
        // If this normalized value is >= 5,
        // set the function's value to 0
        if (fabs(tmp) >= 5.0 ) {
            return 0.0;
        }
        
        
        // Otherwise, add the squared value
        // of tmp to the sum
        value += tmp*tmp;
    }
    
    
    // return final value
    return coef*exp( -value );
}


#endif