//
//  Vec3D.cpp
//  NumCH
//
//  Created by Christian J Howard on 11/25/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "Vec3D.hpp"



Vector<3> cross( const Vector<3> & v, const Vector<3> & vec ) {
    Vector<3> out;
    out[0] = v[1]*vec[2] - v[2]*vec[1];
    out[1] = v[2]*vec[0] - v[0]*vec[2];
    out[2] = v[0]*vec[1] - v[1]*vec[0];
    return out;
}