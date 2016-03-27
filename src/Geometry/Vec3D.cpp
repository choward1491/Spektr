//
//  Vec3D.cpp
//  NumCH
//
//  Created by Christian J Howard on 11/25/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "Vec3D.hpp"

namespace Vec3DOps {
    
    
    Vec3D cross( const Vec3D & v1, const Vec3D & v2 ) {
        Vec3D out;
        out[0] = v1[1]*v2[2] - v1[2]*v2[1];
        out[1] = v1[2]*v2[0] - v1[0]*v2[2];
        out[2] = v1[0]*v2[1] - v1[1]*v2[0];
        return out;
    }
    double dot( const Vec3D & v1, const Vec3D & v2 )  {
        return v1(0)*v2(0) + v1(1)*v2(1) + v1(2)*v2(2);
    }
    double magnitude(const Vec3D & v1) {
        return sqrt( dot(v1, v1) );
    }
    
    void normalize( Vec3D & v1){
        double mag = magnitude(v1);
        v1(0) /= mag;
        v1(1) /= mag;
        v1(2) /= mag;
    }
}