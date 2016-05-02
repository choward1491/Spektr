//
//  Quaternion.cpp
//  NumCH
//
//  Created by Christian J Howard on 11/24/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "Quaternion.hpp"
#include "EulerAngles.hpp"

Quaternion::Quaternion(){
    s = 0.0;
    v = vec3();
}
Quaternion::Quaternion( double roll, double pitch, double yaw ){
    Quaternion q1( roll, vec3_ops::equal(1.0, 0.0, 0.0));
    Quaternion q2( pitch, vec3_ops::equal(0.0, 1.0, 0.0));
    Quaternion q3( yaw, vec3_ops::equal(0.0, 0.0, 1.0));
    *this = q3*q2*q1;
}

Quaternion::Quaternion( const EulerAngles & angles ){
    Quaternion q1( angles[0], vec3_ops::equal(1.0, 0.0, 0.0));
    Quaternion q2( angles[1], vec3_ops::equal(0.0, 1.0, 0.0));
    Quaternion q3( angles[2], vec3_ops::equal(0.0, 0.0, 1.0));
    *this = q3*q2*q1;
}

EulerAngles Quaternion::getEulerAngles() const{
    EulerAngles angles;
    angles[0] = atan2( 2.0*(s*v[0]+v[1]*v[2]), 1.0 - 2.0*(v[0]*v[0]+v[1]*v[1] ) );
    angles[1] = asin( 2.0*(s*v[1]-v[0]*v[2] ) );
    angles[2] = atan2( 2.0*(s*v[2]+v[1]*v[0]), 1.0 - 2.0*(v[2]*v[2]+v[1]*v[1] ) );
    return angles;
}

Quaternion::Quaternion( double angle, const vec3 & axis ){
    s = cos(angle*0.5);
    double t = sin(angle*0.5);
    v = axis;
    vec3_ops::normalize(v);
    v = v * t;
}


vec3 Quaternion::rotate( const vec3 & vec) const{
    Quaternion P;
    P.v = vec;
    Quaternion q = (*this) * P * (*this).getInverse();
    return q.getVectorPart();
}

Quaternion  Quaternion::getInverse() const{
    return getConjugate();
}
Quaternion  Quaternion::getConjugate() const{
    Quaternion q;
    q.s = s;
    q.v = -1*v;
    return q;
}

Quaternion  Quaternion::getDerivative( const vec3 & omega ) const{
    Quaternion w;
    w.s = 0; w.v = omega/2.0;
    
    return (*this)*w;
}

vec3       Quaternion::getAxis() const{
    double t = sqrt(1.0 - s*s);
    return v / t;
}
double      Quaternion::getAmountRotated() const{ return 2.0*acos(s); }

double      Quaternion::getScalarPart() const{ return s; }
vec3       Quaternion::getVectorPart() const{ return v; }
void        Quaternion::setScalarPart( double scalar ){ s = scalar; }
void        Quaternion::setVectorPart( const vec3 & vec ){ v = vec; }


double      Quaternion::getMagnitude() const{
    return sqrt(s*s + vec3_ops::dot(v,v));
}


void        Quaternion::normalize(){
    double mag = getMagnitude();
    s /= mag;
    v = v / mag;
}

Quaternion  Quaternion::operator*( const Quaternion & q ) const{
    double s2 = q.getScalarPart();
    vec3 v2 = q.getVectorPart();
    double sn = s*s2 - vec3_ops::dot(v,v2);
    vec3 vn = v2*s + v*s2 + vec3_ops::cross(v,v2);
    Quaternion out;
    out.s = sn;
    out.v = vn;
    return out;
}
Quaternion  Quaternion::operator+( const Quaternion & q ) const{
    Quaternion qn;
    qn.s = s + q.getScalarPart();
    qn.v = v + q.getVectorPart();
    qn.normalize();
    return qn;
}
Quaternion  Quaternion::operator-( const Quaternion & q ) const{
    Quaternion qn;
    qn.s = s - q.getScalarPart();
    qn.v = v - q.getVectorPart();
    qn.normalize();
    return qn;
}


Quaternion Quaternion::operator*( double c ) const{
    Quaternion out;
    out.s = s*c;
    out.v = v*c;
    return out;
}
Quaternion Quaternion::operator/( double c ) const{
    Quaternion out;
    out.s = s/c;
    out.v = v/c;
    return out;
}


double      Quaternion::operator[](int index) const{
    if( index == 0 ){
        return s;
    }else{
        return v[index-1];
    }
}
double &    Quaternion::operator[](int index){
    if( index == 0 ){
        return s;
    }else{
        return v[index-1];
    }
}



void Quaternion::print() const{
    printf("%lf + %lfi + %lfj + %lfk\n",s,v[0],v[1],v[2]);
}

