//
//  Rosenbrock.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/27/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef Rosenbrock_h
#define Rosenbrock_h

#include <vector>

namespace opt {
    
    class Rosenbrock {
        
    public:
        //f(x,y) = (a-x)^2 + b*(y-x^2)^2
        double operator()( const std::vector<double> & in ){
            double x = in[0], y = in[1];
            double d1 = x-a, d2 = y - x*x;
            return d1*d1 + b*d2*d2;
        }
        
        double operator()( const std::vector<double> & in, std::vector<double> & grad ){
            double x = in[0], y = in[1];
            double d1 = x-a, d2 = y - x*x;
            grad[0] = 2.0*(d1 - 2.0*x*b*d2);
            grad[1] = 2.0*b*d2;
            return d1*d1 + b*d2*d2;
        }
        
        
    private:
        const double a = 1;
        const double b = 100;
    };
    
}

#endif /* Rosenbrock_h */
