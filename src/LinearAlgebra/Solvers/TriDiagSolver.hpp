//
//  TriDiagSolver.hpp
//  NumCH
//
//  Created by Christian J Howard on 2/20/16.
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

#ifndef TriDiagSolver_hpp
#define TriDiagSolver_hpp

#include "Matrix.hpp"

namespace la {
    
    template<class T> class LMat;
    template<class T> class UMat;
    template<class T> class Mat;
    template<class T> class SMat;
    template<class T> class TDMat;
    template<class T> class DMat;
    template<class T> class SpMat;
    
    
    template<class T, class C, class O>
    void solve( const TDMat<T> & A, const MatExpression<T,C> & b, Matrix<T,O> & x ){
        assert(A.isSquare());
        assert(A.size().cols == b.size().rows);
        Dims dim = b.size();
        Dims adim = A.size();
        if( x.size() != dim ){
            x.resize(dim);
        }
        
        TDMat<T> Ac  = A;
        Mat<T>  d   = b;
        
        // forward pass
        Ac(0,1) = Ac(0,1) / Ac(0,0);
        Ac(0,0) = 1;
        for (int i = 1; i < (adim.rows-1); i++ ) {
            Ac(i,i+1) = Ac(i,i+1) / ( Ac(i,i) - Ac(i+1,i)*Ac(i-1,i) );
            Ac(i,i) = 1;
        }
        Ac(adim.rows-1,adim.rows-1) = 1;
        
        
        // compute modified vector on RHS
        T ai;
        for (int j = 0; j < dim.cols; j++) {
            for (int i = 0; i < dim.rows; i++) {
                if( i == 0 ){
                    d(i,j) = b(i,j)/A(i,i);
                }else{
                    ai = A(i+1,i);
                    d(i,j) = (b(i,j)-ai*d(i-1,j))/(A(i,i)-ai*Ac(i-1,i));
                }
            }
        }
        
        // compute solution
        int n = dim.rows-1;
        for (int j = 0; j < dim.cols; j++) {
            for (int i = n; i >= 0; i-- ) {
                if( i == n ){
                    x(i,j) = d(i,j);
                }else{
                    x(i,j) = d(i,j) - Ac(i,i+1)*x(i+1,j);
                }
            }
        }
        
    }
    
    
}

#endif /* TriDiagSolver_hpp */
