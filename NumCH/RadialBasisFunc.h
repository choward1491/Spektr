//
//  RadialBasisFunc.h
//  Data_Structs
//
//  Created by Christian J Howard on 9/6/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#ifndef __Data_Structs__RadialBasisFunc__
#define __Data_Structs__RadialBasisFunc__

#include <stdio.h>
#include "Coordinate.h"
#include <math.h>

/*!
* This template class represents a gaussian RBF
* for an N dimensional input
*
*/
template<int Dim>
class RadialBasisFunc {
public:
    
    // Null constructor
    RadialBasisFunc();
    
    
    // Method to allow changing the center of the RBF
    void assignCenter( const Coordinate<Dim> & _center );
    
    
    // Method to allow changing the standard deviation vector.
    // This vector of sigmas represent having a different deviation for
    // each dimension of the input vector
    void assignSigma ( const Coordinate<Dim> & _sigma  );
    
    
    
    // Method to set sigma vector to a constant value
    void assignConstSigma( double newSigma );
    
    
    
    // This is to assign a coefficient to multiply the result
    // of this RBF by
    void assignCoefficient( double _coef );
    
    
    // Operator method to operate on an input N dimensional vector
    double operator()( const Coordinate<Dim> & x );
    
    
    
    
private:
    Coordinate<Dim> sigma;
    Coordinate<Dim> center;
    double coef;
    
    
};



#ifndef _gaussrbf_cpp_
#include "RadialBasisFunc.cpp"
#endif

#endif /* defined(__Data_Structs__RadialBasisFunc__) */
