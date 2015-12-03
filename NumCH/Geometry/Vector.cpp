//
//  Vector.cpp
//  NumCH
//
//  Created by Christian J Howard on 11/24/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "Vector.hpp"


#ifndef _vector_cpp_
#define _vector_cpp_



template<int D>
Vector<D>::Vector(){
    for (int i = 0; i < D; i++) {
        v[i] = 0.0;
    }
}

// operators
template<int D>
double & Vector<D>::operator[](int index){
    return v[index];
}

template<int D>
const double & Vector<D>::operator[](int index) const{
    return v[index];
}

template<int D>
Vector<D> Vector<D>::operator+( const Vector<D> & vec) const{
    Vector output;
    for (int i = 0; i < D; i++) {
        output[i] = v[i] + vec[i];
    }
    return output;
}

template<int D>
Vector<D> Vector<D>::operator+(double n) const{
    Vector output;
    for (int i = 0; i < D; i++) {
        output[i] = v[i] + n;
    }
    return output;
}

template<int D>
Vector<D> Vector<D>::operator-( const Vector<D> & vec) const{
    Vector output;
    for (int i = 0; i < D; i++) {
        output[i] = v[i] - vec[i];
    }
    return output;
}

template<int D>
Vector<D> Vector<D>::operator-(double n) const{
    Vector output;
    for (int i = 0; i < D; i++) {
        output[i] = v[i] - n;
    }
    return output;
}

template<int D>
Vector<D> Vector<D>::operator*( const Vector<D> & vec) const{
    Vector output;
    for (int i = 0; i < D; i++) {
        output[i] = v[i] * vec[i];
    }
    return output;
}

template<int D>
Vector<D> Vector<D>::operator*(double n) const{
    Vector output;
    for (int i = 0; i < D; i++) {
        output[i] = v[i] * n;
    }
    return output;
}

template<int D>
Vector<D> Vector<D>::operator/( const Vector<D> & vec) const{
    Vector output;
    for (int i = 0; i < D; i++) {
        output[i] = v[i] / vec[i];
    }
    return output;
}

template<int D>
Vector<D> Vector<D>::operator/(double n) const{
    Vector output;
    for (int i = 0; i < D; i++) {
        output[i] = v[i] / n;
    }
    return output;
}


template<int D>
Vector<D> Vector<D>::operator-() const {
    Vector output;
    for (int i = 0; i < D; i++) {
        output[i] = -v[i];
    }
    return output;
}

template<int D>
void Vector<D>::operator+=( const Vector<D> & vec){
    for (int i = 0; i < D; i++) {
        v[i] += vec[i];
    }
}

template<int D>
void Vector<D>::operator-=( const Vector<D> & vec){
    for (int i = 0; i < D; i++) {
        v[i] -= vec[i];
    }
}

template<int D>
void Vector<D>::operator+=(double n){
    for (int i = 0; i < D; i++) {
        v[i] += n;
    }
}

template<int D>
void Vector<D>::operator-=(double n){
    for (int i = 0; i < D; i++) {
        v[i] -= n;
    }
}

template<int D>
void Vector<D>::operator*=(double n){
    for (int i = 0; i < D; i++) {
        v[i] *= n;
    }
}

template<int D>
void Vector<D>::operator/=(double n){
    for (int i = 0; i < D; i++) {
        v[i] /= n;
    }
}

template<int D>
double Vector<D>::dot( const Vector<D> & vec ) const{
    double dotProduct = 0.0;
    for (int i = 0; i < D; i++) {
        dotProduct += v[i]*vec[i];
    }
    return dotProduct;
}


template<int D>
Vector<D> Vector<D>::getUnit() const{
    double mag = getMagnitude();
    return (*this)/mag;
}

template<int D>
void Vector<D>::normalize(){
    double mag = getMagnitude();
    (*this) /= mag;
}

template<int D>
double Vector<D>::getMagnitude() const{
    return sqrt( getSquaredMagnitude() );
}

template<int D>
double Vector<D>::getSquaredMagnitude() const{
    return dot(*this);
}

template<int D>
void Vector<D>::print() const{
    printf("[ %lf",v[0]);
    for (int i = 1; i < D; i++) {
        printf(", %lf",v[i]);
    }printf(" ]\n");
}


#endif
