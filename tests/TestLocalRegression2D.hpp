//
//  LocalRegression2D.hpp
//  Spektr
//
//  Created by Christian J Howard on 6/6/16.
//
//  The MIT License (MIT)
//    Copyright © 2016 Christian Howard. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
//
//

#ifndef LocalRegression2D_hpp
#define LocalRegression2D_hpp

#include <stdio.h>
#include "LocalRegression.hpp"
#include "Timer.hpp"


class Point2D {
public:
    typedef double Type;
    static const int Dims = 2;
    
    Point2D(){ x[0] = 0; x[1] = 0; }
    Point2D( Type x_ , Type y_){x[0] = x_; x[1] = y_;}
    Type   operator[](int i ) const { return x[i%2]; }
    Type & operator[](int i )       { return x[i%2]; }
    
private:
    Type x[2];
    
};


class PolyBasis2D {
public:
    static int size;
    
    enum BasisSize { Constant=1,Linear= 3,Quadratic= 6,Cubic,Quartic };
    
    PolyBasis2D(){ size = 1; }
    PolyBasis2D( int size_ ){ size = size_; }
    void setSize( int size_ ){ size = size_; }
    
    double operator()(int i, Point2D & pt){
        switch (i){
            case 0:
                return 1.0;
            case 1:
                return pt[0];
            case 2:
                return pt[1];
            case 3:
                return pt[0]*pt[0];
            case 4:
                return pt[1]*pt[1];
            case 5:
                return pt[0]*pt[1];
            default:
                return 1.0;
        }
    }
};




class WeightFunc {
public:
    typedef KDTree<Point2D,double,L2_Norm>::NNSet NNSet;
    typedef std::vector<double> vec;
    
    void operator()( vec & v, NNSet & set ){
        double mdist = -1;
        for(int i = 0; i < v.size(); i++ ){
            mdist = fmax(set.getKeyAt(i),mdist);
        }
        mdist = sqrt(mdist);
        for(int i = 0; i < v.size(); i++ ){
            double dist = sqrt(set.getKeyAt(i));
            v[i] = pow(1-pow(dist/mdist,3),3);
            double d = dist/mdist;
            v[i] = exp( - d*d );
        }
    }
    
};
typedef LocalRegression<Point2D,PolyBasis2D,WeightFunc> LR;
bool testLocalRegression2D();


#endif /* LocalRegression2D_hpp */
