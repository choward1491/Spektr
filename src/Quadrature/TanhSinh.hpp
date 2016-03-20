//
//  TanhSinh.hpp
//  NumCH
//
//  Created by Christian J Howard on 2/17/16.
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

#ifndef TanhSinh_hpp
#define TanhSinh_hpp

#include <stdio.h>

namespace quad {
    
    class TanhSinh {
    public:
        
        template<class Func>
        static double integrate( Func & func, double a, double b, int N){
            if (N % 2 != 0) { N++; }
            double h = computeStep(N);
            double ta = h*(N-1)*0.5;
            double result = 0, t = 0, c = h*(b-a)/2.0;
            Output o;
            for (int i = 0; i < N ; i++) {
                t = -ta + i*h;
                o = computeWeightAbscissa(t);
                result += o.weight* func(S(o.abscissa,a,b));
            }
            return result * c;
        }
        
    private:
        
        struct Output {
            double weight;
            double abscissa;
        };
        
        static double precisionBasedBounds();
        static double computeStep( int N );
        static Output computeWeightAbscissa( double t );
        static double S( double x , double a, double b);
        
    };
    
}

#endif /* TanhSinh_hpp */
