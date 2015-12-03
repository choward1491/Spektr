//
//  Mat.hpp
//  NumCH
//
//  Created by Christian J Howard on 11/24/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef Mat_hpp
#define Mat_hpp

#include <stdio.h>
#include "Vector.hpp"


template<int R, int C>
class Mat {
public:
    
    Mat();
    
    // operators
    double & operator()(int row, int col);
    double   operator()(int row, int col) const;
    
    Mat operator+( const Mat & v) const;
    Mat operator+(double n) const;
    Mat operator-( const Mat & v) const;
    Mat operator-(double n) const;
    
    template<int C2>
    Mat<R,C2> operator*( const Mat<C,C2> & v) const;
    
    Mat operator*(double n) const;
    Mat operator/(double n) const;
    
    Vector<R> operator*(Vector<C> & v) const;
    
    void operator+=( const Mat & v);
    void operator-=( const Mat & v);
    void operator+=(double n);
    void operator-=(double n);
    void operator*=(double n);
    void operator/=(double n);
    
    int numRows() const { return R; }
    int numCols() const { return C; }
    
    Mat<C,R> getTranspose() const;
    
    
protected:
    
    double m[R][C];
    
};





#ifndef mat_cpp_
#include "Mat.cpp"
#endif

#endif /* Mat_hpp */
