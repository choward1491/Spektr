//
//  Mat.cpp
//  NumCH
//
//  Created by Christian J Howard on 11/24/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "Mat.hpp"

#ifndef mat_cpp_
#define mat_cpp_

template<int R, int C>
Mat<R,C>::Mat(){
    
}

template<int R, int C>
double & Mat<R,C>::operator()(int row, int col){
    return m[row][col];
}

template<int R, int C>
double   Mat<R,C>::operator()(int row, int col) const{
    return m[row][col];
}

template<int R, int C>
Mat<R,C> Mat<R,C>::operator+( const Mat & v) const{
    Mat out;
    for (int r = 0; r < R ; r++) {
        for (int c = 0; c < C; c++) {
            out(r,c) = out[r][c] + v(r,c);
        }
    }
    return out;
}

template<int R, int C>
Mat<R,C> Mat<R,C>::operator+(double n) const{
    
}

template<int R, int C>
Mat<R,C> Mat<R,C>::operator-( const Mat & v) const{
    Mat out;
    for (int r = 0; r < R ; r++) {
        for (int c = 0; c < C; c++) {
            out(r,c) = out[r][c] - v(r,c);
        }
    }
    return out;
}

template<int R, int C>
Mat<R,C> Mat<R,C>::operator-(double n) const{
    
}


template<int R, int C>
template<int C2>
Mat<R,C2> Mat<R,C>::operator*( const Mat<C,C2> & v) const{
    
}


template<int R, int C>
Mat<R,C> Mat<R,C>::operator*(double n) const{
    
}

template<int R, int C>
Mat<R,C> Mat<R,C>::operator/(double n) const{
    
}

template<int R, int C>
Vector<R> Mat<R,C>::operator*(Vector<C> & v) const{
    Vector<R> out;
    for (int r = 0; r < R ; r++) {
        for (int c = 0; c < C; c++) {
            out[r] += out[r][c]*v[c];
        }
    }
    return out;
}

template<int R, int C>
void Mat<R,C>::operator+=( const Mat & v ){
    
}

template<int R, int C>
void Mat<R,C>::operator-=( const Mat & v){
    
}

template<int R, int C>
void Mat<R,C>::operator+=(double n){
    
}

template<int R, int C>
void Mat<R,C>::operator-=(double n){
    
}

template<int R, int C>
void Mat<R,C>::operator*=(double n){
    
}

template<int R, int C>
void Mat<R,C>::operator/=(double n){
    
}


template<int R, int C>
Mat<C,R> Mat<R,C>::getTranspose() const{
    
}



#endif


