//
//  LogisticRegression.hpp
//  NumCH
//
//  Created by Christian J Howard on 2/10/16.
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

#ifndef LogisticRegression_h
#define LogisticRegression_h


#include "Matrix.hpp"
#include <vector>
#include <math.h>

namespace ml {
    
    typedef la::Mat<double> Mat;
    
    template<class Basis>
    class LogisticRegression {
    public:
        
        LogisticRegression():nullPenalty(1),invm(1.0),scalar(0),hasInit(false){}
        
        double operator()( const Mat & in ){
            if( !hasInit ){ init(); hasInit = true; }
            double cost = 0;
            double g = 0;
            grad = 0;
            
            for (int i = 0; i < xdata->size(); i++) {
                g = sigmoid( scalar + basis.evaluate( (*xdata)[i], in ) );
                if( (*ydata)[i] == 1.0 ){
                    cost -= invm * log( g );
                    for (int j = basis.start((*xdata)[i]); j != -1; j = basis.increment() ) {
                        grad[j] -= (invm * (1.0 - g )*basis((*xdata)[i],j));
                    }
                }else{
                    cost -= invm * nullPenalty * log( 1.0 - g );
                    for (int j = basis.start((*xdata)[i]); j != -1; j = basis.increment() ) {
                        grad[j] += (invm * g * nullPenalty * basis((*xdata)[i],j) );
                    }
                }
            }
            
            //grad.print();
            
            return cost;
        }
        
        const Mat & gradient() const { return grad; }
        int numDims() const { return basis.numDims(); }
        void setData( std::vector<Mat> * x, std::vector<double> * y ){
            xdata = x;
            ydata = y;
            invm = 1.0 / static_cast<double>(x->size());
        }
        
        
        void setScalarOffset( double s ){ scalar = s; }
        void setPenaltyForZeroOutput( double penalty ){ nullPenalty = penalty; }
        double sigmoid( double z ){ return 1.0 / (1.0 + exp(-z) ); }
        double s() const { return scalar; }
        
        Basis basis;
        std::vector<Mat>* xdata;
        std::vector<double>* ydata;
        
    private:
        void init(){
            grad.resize(numDims(),1);
            grad = 0;
        }
        bool hasInit;
        double invm;
        double nullPenalty;
        double scalar;
        Mat grad;
    };
    
}




#endif /* LogisticRegression_h */
