//
//  TestLocalRegression1D.hpp
//  Spektr
//
//  Created by Christian J Howard on 6/5/16.
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

#ifndef TestLocalRegression1D_hpp
#define TestLocalRegression1D_hpp

#include <stdio.h>
#include "LocalRegression.hpp"
#include "Timer.hpp"


class Point1D {
public:
    typedef double Type;
    static const int Dims = 1;
    
    Point1D():x(0){}
    Point1D( Type x_ ):x(x_){}
    operator double() {
        return x;
    }
    Type   operator[](int i ) const { return x; }
    Type & operator[](int i )       { return x; }
    
private:
    Type x;
    
};


class PolyBasis1D {
public:
    static int size;
    
    enum BasisSize { Constant=1,Linear,Quadratic,Cubic,Quartic };
    
    PolyBasis1D(){ size = 1; }
    PolyBasis1D( int size_ ){ size = size_; }
    void setSize( int size_ ){ size = size_; }
    
    double operator()(int i, Point1D & pt){
        return pow(pt[0], static_cast<double>(i));
    }
};




class WeightFunc {
public:
    typedef KDTree<Point1D,double,L2_Norm>::NNSet NNSet;
    typedef std::vector<double> vec;
    
    void operator()( vec & v, NNSet & set ){
        double mdist = -1;
        for(int i = 0; i < v.size(); i++ ){
            mdist = fmax(set.getKeyAt(i),mdist);
        }
        
        for(int i = 0; i < v.size(); i++ ){
            double dist = set.getKeyAt(i);
            v[i] = pow(1-pow(dist/mdist,3),3);
            double d = dist/mdist;
            v[i] = exp( - d*d );
        }
    }
    
};
typedef LocalRegression<Point1D,PolyBasis1D,WeightFunc> LR;


bool testLocalRegression1D();






#endif /* TestLocalRegression1D_hpp */
