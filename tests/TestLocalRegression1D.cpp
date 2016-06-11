//
//  TestLocalRegression1D.cpp
//  Spektr
//
//  Created by Christian J Howard on 6/5/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include "TestLocalRegression1D.hpp"

int PolyBasis1D::size = 1;

bool testLocalRegression1D(){
    
    Timer timer;
    
    
    int n = 1000000;
    double w = 12;
    std::vector<Point1D> x(n);
    std::vector<double> y(n);
    
    for(int i = 0; i < n; i++ ){
        x[i] = i/(double)(n-1);
        y[i] = sin(w*x[i]);
    }
    
    LR::Tree tree(x,y);
    LR localReg( tree );
    localReg.basis.setSize(LR::Basis::Quadratic);
    localReg.setNumNeighborsForFit(2*LR::Basis::size);
    
    timer.start();
    
    for( int i = 0; i < 1001; i++ ){
        Point1D xx = i/(double)1001;
        double yy = localReg( xx );
        double yt = sin(w*xx);
        printf("YY = %lf, Y = %lf, Error = %0.10lf\n",yy,yt, fabs(yt-yy));
    }
    
    timer.stop();
    
    printf("Run time is %lf seconds\n",timer.getDuration());
    
    return true;
}