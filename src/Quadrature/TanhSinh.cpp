//
//  TanhSinh.cpp
//  NumCH
//
//  Created by Christian J Howard on 2/17/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include "TanhSinh.hpp"
#include <math.h>

namespace quad {
    
    double TanhSinh::precisionBasedBounds(){
        return pow(10.0, 0.46);
    }
    double TanhSinh::computeStep( int N ){
        return 2.0*precisionBasedBounds()/static_cast<double>((N-1));
    }
    TanhSinh::Output TanhSinh::computeWeightAbscissa( double t ){
        double c = M_PI_2;
        double d = c*sinh(t);
        double e = 1.0/cosh(d);
        Output o;
        o.abscissa = tanh(d);
        o.weight   = c*cosh(t)*e*e;
        return o;
    }
    double TanhSinh::S( double x , double a, double b){
        return 0.5*( (b+a) + x*(b-a));
    }
    
    
    
}