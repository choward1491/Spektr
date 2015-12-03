//
//  Vector.hpp
//  NumCH
//
//  Created by Christian J Howard on 11/24/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef Vector_hpp
#define Vector_hpp

#include <math.h>
#include <stdio.h>


template<int D>
class Vector {
public:
    
    Vector();
    
    // operators
    double & operator[](int index);
    const double & operator[](int index) const;
    
    Vector operator+( const Vector & v) const;
    Vector operator+(double n) const;
    Vector operator-( const Vector & v) const;
    Vector operator-(double n) const;
    Vector operator*( const Vector & v) const;
    Vector operator*(double n) const;
    Vector operator/( const Vector & v) const;
    Vector operator/(double n) const;
    Vector operator-() const;
    
    void operator+=( const Vector & v);
    void operator-=( const Vector & v);
    void operator+=(double n);
    void operator-=(double n);
    void operator*=(double n);
    void operator/=(double n);
    
    
    int size() const { return D; }
    
    double dot( const Vector & v ) const;
    Vector getUnit() const;
    void normalize();
    double getMagnitude() const;
    double getSquaredMagnitude() const;
    void print() const;
    
    
protected:
    double v[D];
    
};



#ifndef _vector_cpp_
#include "Vector.cpp"
#endif


#endif /* Vector_hpp */
