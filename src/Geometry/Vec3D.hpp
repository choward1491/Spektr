//
//  Vec3D.hpp
//  NumCH
//
//  Created by Christian J Howard on 11/25/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef Vec3D_hpp
#define Vec3D_hpp

#include "Matrix.hpp"

typedef la::FastMat<double, 3, 1> Vec3D;

namespace Vec3DOps {
    
    Vec3D cross( const Vec3D & v1, const Vec3D & v2 );
    double dot( const Vec3D & v1, const Vec3D & v2 );
    double magnitude(const Vec3D & v1);
    void normalize( Vec3D & v1);
}

#endif /* Vec3D_hpp */
