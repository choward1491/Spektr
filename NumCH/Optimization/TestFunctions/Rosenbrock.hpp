//
//  Rosenbrock.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/27/16.
//
//  The MIT License (MIT)
//  Copyright © 2016 Christian Howard. All rights reserved.
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

#ifndef Rosenbrock_h
#define Rosenbrock_h

#include <vector>
#include "Matrix.hpp"

namespace opt {
    
    typedef la::Mat<double> vec;
    
    class Rosenbrock {
        
    public:
        //f(x,y) = (a-x)^2 + b*(y-x^2)^2
        double operator()( const vec & in ){
            double x = in[0], y = in[1];
            double d1 = x-a, d2 = y - x*x;
            return d1*d1 + b*d2*d2;
        }
        
        double operator()( const vec & in, vec & grad ){
            double x = in[0], y = in[1];
            double d1 = x-a, d2 = y - x*x;
            grad[0] = 2.0*(d1 - 2.0*x*b*d2);
            grad[1] = 2.0*b*d2;
            return d1*d1 + b*d2*d2;
        }
        
        int numDims() const { return 2; }
        
        
    private:
        const double a = 1;
        const double b = 100;
    };
    
}

#endif /* Rosenbrock_h */
