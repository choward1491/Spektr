//
//  TargetMeas.hpp
//  NumCH
//
//  Created by Christian J Howard on 2/5/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef TargetMeas_h
#define TargetMeas_h

#include "Matrix.hpp"

class TargetMeas {
public:
    typedef la::Mat<double> Mat;
    static const int Nz = 2;
    
    Mat operator()(const Mat & xi ){
        Mat z(Nz,1);
        z[0] = xi[0];
        z[1] = xi[1];
        
        return z;
    }
    
};

#endif /* TargetMeas_h */
