//
//  vec3.hpp
//  NumCH
//
//  Created by Christian J Howard on 11/25/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef Vec3D_hpp
#define Vec3D_hpp

#include "Matrix.hpp"

typedef la::FastMat<double, 3, 1> vec3;

namespace vec3_ops {
    
    vec3 equal( double x, double y, double z);
    vec3 cross( const vec3 & v1, const vec3 & v2 );
    double dot( const vec3 & v1, const vec3 & v2 );
    double magnitude(const vec3 & v1);
    void normalize( vec3 & v1);
}

#endif /* Vec3D_hpp */
