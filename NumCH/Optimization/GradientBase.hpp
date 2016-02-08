//
//  GradientBase.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/28/16.
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

#ifndef GradientBase_h
#define GradientBase_h

#include "Optimizer.hpp"

namespace opt {
    
    template< class Function, class Step >
    class gradient  : public optimizer< gradient<Function,Step> > {
    public:
        
        gradient():numIter(0),maxIter(100),cost(1e100),bcost(1e100),
                   tol(1e-2),err(1e10),mom_coef(0.1){}
        
        void setGuess( const Mat & m ){ x = m; }
        void setMaxIter( int mi ){ maxIter = mi; }
        void setTolerance( double eps ){ tol = eps; }
        void setMomentumCoef( double mc ){ mom_coef = mc; }
        
        Mat & soln(){ return xbest; }
        const Mat & soln() const { return xbest; }
        double bestCost() const { return bcost; }
        
        Step step;
        Function func;
        
    protected:
        
        void init_(){
            step.setFunc(&func);
            initStateSize();
        }
        virtual bool isComplete_(){
            return (numIter >= maxIter || err < tol );
        }
        void update_(){
            update();
            numIter++;
        }
        void giveStatus_(){
            printf("Iteration Count: %i, Best Cost: %0.8lf\n",numIter,bcost);
        }
        
        virtual void finalize_(){}
    private:
        template<class T> friend class optimizer;
        
        void update(){
            cost = func(x);
            if( cost < bcost ){
                xbest = x;
                bcost = cost;
            }
            double s = step(numIter);
            dx = mom_coef*dx - s*func.gradient();
            x = x + dx;
        }
        
        void initStateSize(){
            int Nx = func.numDims();
            if( x.size() != Dims(Nx,1) ){
                x.resize(Nx,1);
            }
            xbest.resize(Nx,1);
            dx.resize(Nx,1);
        }
        
        
        
        
        int numIter;
        int maxIter;
        
        double cost;
        double bcost;
        double tol;
        double err;
        double mom_coef;
        
        Mat x;
        Mat xbest;
        Mat dx;
        
    };
    
    
    
}





#endif /* GradientBase_h */
