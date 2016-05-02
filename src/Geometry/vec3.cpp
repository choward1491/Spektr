//
//  vec3.cpp
//  NumCH
//
//  Created by Christian J Howard on 11/25/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "vec3.hpp"

namespace vec3_ops {
    
    vec3 equal( double x, double y, double z){
        vec3 out;
        out[0] = x;
        out[1] = y;
        out[2] = z;
        return out;
    }
    
    vec3 cross( const vec3 & v1, const vec3 & v2 ) {
        vec3 out;
        out[0] = v1[1]*v2[2] - v1[2]*v2[1];
        out[1] = v1[2]*v2[0] - v1[0]*v2[2];
        out[2] = v1[0]*v2[1] - v1[1]*v2[0];
        return out;
    }
    double dot( const vec3 & v1, const vec3 & v2 )  {
        return v1(0)*v2(0) + v1(1)*v2(1) + v1(2)*v2(2);
    }
    double magnitude(const vec3 & v1) {
        return sqrt( dot(v1, v1) );
    }
    
    void normalize( vec3 & v1){
        double mag = magnitude(v1);
        v1(0) /= mag;
        v1(1) /= mag;
        v1(2) /= mag;
    }
}