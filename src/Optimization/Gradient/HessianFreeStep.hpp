//
//  HessianFreeStep.hpp
//  Spektr
//
//  Created by Christian J Howard on 6/26/16.
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

#ifndef HessianFreeStep_h
#define HessianFreeStep_h

#include "Matrix.hpp"

namespace opt {
    
    template<class Function>
    class HessianFreeStep {
    public:
        HessianFreeStep():stepsize(0.01){}
        
        double operator()(int iterationCount){
            
            grad1 = func->gradient();
            double mag = 0.0;
            for( int i = 0; i < grad1.size().rows; i++ ){
                mag += grad1[i]*grad1[i];
            }
            //u = grad1/sqrt(mag);
            //u.print();
            la::Mat<double> in = *x + 1e-5*grad1;
            double cost = (*func)( in );
            grad2 = func->gradient();
            double denom = 0.0;
            for( int i = 0; i < grad1.size().rows; i++ ){
                denom += fabs(grad1[i]*(grad2[i]-grad1[i])/1e-5);
            }
            
            //printf("num = %lf, denom = %lf\n",mag, denom);
            
            stepsize = 1e-1*mag/denom;
            
            //printf("stepsize = %lf\n",stepsize);
            
            return stepsize;
        }
        
        void setFunc( Function * func_ ){ func = func_; }
        void setState( la::Mat<double> * state_ ){ x = state_; }
        
        
    private:
        double stepsize;
        Function * func;
        la::Mat<double> * x;
        la::Mat<double> grad1;
        la::Mat<double> grad2;
        la::Mat<double> u;
        
    };
    
}

#endif /* HessianFreeStep_h */
