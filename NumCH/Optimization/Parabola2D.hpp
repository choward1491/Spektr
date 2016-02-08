//
//  Parabola2D.hpp
//  NumCH
//
//  Created by Christian J Howard on 2/7/16.
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

#ifndef Parabola2D_h
#define Parabola2D_h

#include "Matrix.hpp"

namespace opt {
    
    typedef la::Mat<double> vec;
    
    class Parabola2D {
        
    public:
        //f(x,y) = (x-a)^2 + (y-b)^2
        
        Parabola2D():grad(numDims(),1,0){}
        
        double operator()( const vec & in ){
            double x = in[0], y = in[1];
            double d1 = x-a, d2 = y - b;
            grad[0] = 2.0*d1;
            grad[1] = 2.0*d2;
            return d1*d1 + d2*d2;
        }
        
        const Mat & gradient() const { return grad; }
        int numDims() const { return 2; }
        
        
    private:
        Mat grad;
        const double a = 1;
        const double b = 1;
    };
    
}

#endif /* Parabola2D_h */
