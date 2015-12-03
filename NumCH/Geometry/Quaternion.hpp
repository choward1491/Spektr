//
//  Quaternion.hpp
//  NumCH
//
//  Created by Christian J Howard on 11/24/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef Quaternion_hpp
#define Quaternion_hpp

#include "Vec3D.hpp"
#include "ConstantsSet.hpp"

class Quaternion {
public:
    
    Quaternion();
    Quaternion( double roll, double pitch, double yaw ); // Assumes Euler Rotation Order of X -> Y -> Z
    Quaternion( double angleRadians, const Vec3D & axis );
    
    
    
    Vec3D rotate( const Vec3D & vec) const;
    
    void        normalize();
    Quaternion  getInverse() const;
    Quaternion  getConjugate() const;
    Vec3D       getAxis() const;
    double      getAmountRotated() const;
    
    double      getScalarPart() const;
    Vec3D       getVectorPart() const;
    void        setScalarPart( double scalar );
    void        setVectorPart( const Vec3D & vec );
    
    Quaternion  getDerivative( const Vec3D & omega ) const;
    
    
    double      getMagnitude() const;
    
    
    Quaternion  operator*( const Quaternion & q ) const;
    Quaternion  operator+( const Quaternion & q ) const;
    Quaternion  operator-( const Quaternion & q ) const;
    
    Quaternion operator*( double c ) const;
    Quaternion operator/( double c ) const;
    
    double      operator[](int index) const;
    double &    operator[](int index);
    
    void print() const;
    
private:
    friend Quaternion;
    
    // quaternion defined by:
    // q = s + v
    // where s is scalar part
    // and v is vector part
    double s;
    Vec3D v;
    
    
};

#endif /* Quaternion_hpp */
