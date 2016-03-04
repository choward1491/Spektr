//
//  Quaternion.cpp
//  NumCH
//
//  Created by Christian J Howard on 11/24/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "Quaternion.hpp"
/*

Quaternion::Quaternion(){
    s = 0.0;
    v = Vec3D();
}
Quaternion::Quaternion( double roll, double pitch, double yaw ){
    double c1 = cos(roll);
    double c2 = cos(pitch);
    double c3 = cos(yaw);
    double s1 = sin(roll);
    double s2 = sin(pitch);
    double s3 = sin(yaw);
}
Quaternion::Quaternion( double angle, const Vec3D & axis ){
    s = cos(angle*0.5);
    double t = sin(angle*0.5);
    v = axis;
    v.normalize();
    v *= t;
}


Vec3D Quaternion::rotate( const Vec3D & vec) const{
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
    q.v = -v;
    return q;
}

Quaternion  Quaternion::getDerivative( const Vec3D & omega ) const{
    Quaternion w;
    w.s = 0; w.v = omega/2.0;
    
    return (*this)*w;
}

Vec3D       Quaternion::getAxis() const{
    double t = sqrt(1.0 - s*s);
    return v / t;
}
double      Quaternion::getAmountRotated() const{ return 2.0*acos(s); }

double      Quaternion::getScalarPart() const{ return s; }
Vec3D       Quaternion::getVectorPart() const{ return v; }
void        Quaternion::setScalarPart( double scalar ){ s = scalar; }
void        Quaternion::setVectorPart( const Vec3D & vec ){ v = vec; }


double      Quaternion::getMagnitude() const{
    return sqrt(s*s + v.dot(v));
}


void        Quaternion::normalize(){
    double mag = getMagnitude();
    s /= mag;
    v /= mag;
}

Quaternion  Quaternion::operator*( const Quaternion & q ) const{
    double s2 = q.getScalarPart();
    Vec3D v2 = q.getVectorPart();
    double sn = s*s2 - v.dot(v2);
    Vec3D vn = v2*s + v*s2 + Vec3Dns::cross(v, v2);
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

*/