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

template<int Dim>
class RadialBasisFunc {
public:
    RadialBasisFunc(){
        assignConstSigma(1.0);
        coef = 0;
    }
    void assignCenter( const Coordinate<Dim> & _center ){
        center = _center;
    }
    void assignSigma ( const Coordinate<Dim> & _sigma  ){ sigma  = _sigma;  }
    void assignConstSigma( double newSigma ){
        for (int i = 0; i < Dim; i++) {
            sigma[i] = newSigma;
        }
    }
    void makeConstant(){ constant = true; }
    void assignCoefficient( double _coef ){ coef = _coef; }
    
    double operator()( const Coordinate<Dim> & x ){
        double value = 0;
        double tmp = 0;
        if( coef == 0.0 ){ return 0.0; };
        if( constant ){
            return -3.0;
        }
        
        for (int i = 0; i < Dim; i++ ) {
            tmp = (center[i]-x[i])/sigma[i];
            if (fabs(tmp) >= 5.0 ) {
                return 0.0;
            }
            value += tmp*tmp;
        }
        
        return coef*exp( -value );
    }
    
    
    Coordinate<Dim> sigma;
    Coordinate<Dim> center;
    double coef;
    bool constant = false;
    
private:
    //double sigma;
    
    
    
};

#endif /* defined(__Data_Structs__RadialBasisFunc__) */
