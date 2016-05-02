//
//  EulerAngles.hpp
//  Spektr
//
//  Created by Christian J Howard on 4/29/16.
//
//  The MIT License (MIT)
//    Copyright © 2016 Christian Howard. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
//
//

#ifndef EulerAngles_hpp
#define EulerAngles_hpp

#include <stdio.h>
#include "vec3.hpp"
typedef la::FastMat<double, 3, 3> mat3;


class EulerAngles {
public:
    
    // Assumes X->Y->Z rotation sequence
    EulerAngles();
    EulerAngles(double a1, double a2, double a3);
    double & operator[](int i);
    const double & operator[](int i) const;
    mat3 getRotationMatrix() const;
    vec3 operator*( const vec3 & input ) const;
    
public:
    double angles[3];
};


#endif /* EulerAngles_hpp */
