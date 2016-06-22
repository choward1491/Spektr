//
//  LocalRegression2D.cpp
//  Spektr
//
//  Created by Christian J Howard on 6/6/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include "TestLocalRegression2D.hpp"

int PolyBasis2D::size = 1;

double BealesFunc( double x, double y){
    return pow(1.5 - x + x*y,2.0) + pow(2.25 - x + x*y*y,2.0) + pow(2.625-x+x*y*y*y,2.0);
}

bool testLocalRegression2D(){
    
    Timer timer;
    
    
    int n = 50;
    std::vector<Point2D> x(n*n);
    std::vector<double> y(n*n);
    
    for(int i = 0; i < n; i++ ){
        for( int j = 0; j < n; j++ ){
            int k = i*n+j;
            x[k][0] = -4.5 + 4.5*i/(double)(n-1);
            x[k][1] = -4.5 + 4.5*j/(double)(n-1);
            y[k] = BealesFunc( x[k][0], x[k][1]);
        }
    }
    
    LR::Tree tree(x,y);
    LR localReg( tree );
    localReg.basis.setSize(LR::Basis::Quadratic);
    localReg.setNumNeighborsForFit(2*LR::Basis::size);
    
    timer.start();
    
    for( int i = 0; i < 101; i++ ){
        for( int j = 0; j < 101; j++ ){
        Point2D xx(-4.5 + 4.5*i/(double)101,-4.5 + 4.5*j/(double)101);
        double yy = localReg( xx );
        double yt = BealesFunc( xx[0], xx[1]);
        printf("YY = %lf, Y = %lf, Error = %0.10lf\n",yy,yt, fabs(yt-yy));
        }
    }
    
    timer.stop();
    
    printf("Run time is %lf seconds\n",timer.getDuration());
    
    return true;
}