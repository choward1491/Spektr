//
//  Solver.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/31/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef Solver_h
#define Solver_h

#include <stdio.h>
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
void solve( const LMat<T> & A, const MatExpression<T,C> & b, Matrix<T,O> & x ){
    assert(A.isSquare());
    assert(A.size().cols == b.size().rows);
    Dims dim = b.size();
    if( x.size() != dim ){
        x.resize(dim);
    }
    
    T sum;
    T zero = T();
    for (int k = 0; k < dim.cols; k++) {
        for (int i = 0; i < dim.rows; i++) {
            sum = zero;
            for (int j = 0; j < i; j++) {
                sum += A(i,j)*x(j,k);
            }
            x(i,k) = (b(i,k)-sum)/A(i,i);
        }
    }
}


}

#endif /* Solver_h */
