//
//  TargetDyn.hpp
//  NumCH
//
//  Created by Christian J Howard on 2/5/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef TargetDyn_h
#define TargetDyn_h

#include "Matrix.hpp"

class TargetDyn {
public:
    typedef la::Mat<double> Mat;
    static const int Nx = 4;
    
    Mat operator()(double dt, const Mat & xi ){
        Mat dqdt(xi);
        dqdt[0] = xi[2];
        dqdt[1] = xi[3];
        dqdt[2] = xi[4];
        dqdt[3] = xi[5];
        
        
        return xi + dt*dqdt;
    }
    
};


#endif /* TargetDyn_h */
