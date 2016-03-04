//
//  ConjGrad.hpp
//  NumCH
//
//  Created by Christian J Howard on 2/4/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
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

#ifndef ConjGrad_h
#define ConjGrad_h

#include "Matrix.hpp"

namespace la {
    
    template<class T> class LMat;
    template<class T> class UMat;
    template<class T> class Mat;
    template<class T> class SMat;
    template<class T> class TDMat;
    template<class T> class DMat;
    template<class T> class SpMat;
    
    
    
    template<class T, class S, class C, class O>
    void conjgradSoln( const Matrix<T,S> & A, const MatExpression<T,C> & b, Matrix<T,O> & x , T threshold = T(1e-3) ){
        assert(A.isSquare());
        assert(A.size().cols == b.size().rows);
        Dims dim = b.size();
        if( x.size() != dim ){
            x.resize(dim);
        }
        
        
        Mat<T> r = b - A*x;
        Mat<T> p = r;
        DMat<T> beta(dim.cols,1), alpha(dim.cols,1);
        Mat<T> rdot(dim.cols,1);
        T maxr = T(0);
        for (int i = 0; i < dim.cols; i++) {
            rdot(i) = r.innerProduct(i);
            if( rdot(i) > maxr ){ maxr = rdot(i); }
        }
        
        
        T zero = T(), tmp;
        int N = dim.rows;
        int k = 0, iter = 0;
        while ( iter < N ) {
            maxr = T();
            for (int i = 0; i < dim.cols; i++) {
                alpha(i) = rdot(i) / p.innerProduct(A,i);
            }
            x = x + p*alpha;
            r = r - A*p*alpha;
            
            for (int i = 0; i < dim.cols; i++) {
                if( rdot(i) > maxr ){ maxr = rdot(i); }
            }
            
            if( maxr < threshold ){ break; }
            
            for (int i = 0; i < dim.cols; i++) {
                tmp = r.innerProduct(i);
                beta(i) = tmp/rdot(i);
                rdot(i) = tmp;
            }
            
            p = r + p*beta;
            iter++;
        }
    }
    
    
    
    
}


#endif /* ConjGrad_h */
