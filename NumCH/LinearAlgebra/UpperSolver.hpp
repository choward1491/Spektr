//
//  UpperSolver.hpp
//  NumCH
//
//  Created by Christian J Howard on 2/4/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef UpperSolver_h
#define UpperSolver_h



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
    void solve( const UMat<T> & A, const MatExpression<T,C> & b, Matrix<T,O> & x ){
        assert(A.isSquare());
        assert(A.size().cols == b.size().rows);
        Dims dim = b.size();
        if( x.size() != dim ){
            x.resize(dim);
        }
        
        T sum;
        T zero = T();
        
        if( A.isTransposed() ){
            for (int k = 0; k < dim.cols; k++) {
                for (int i = 0; i < dim.rows; i++) {
                    sum = zero;
                    for (int j = 0; j < i; j++) {
                        sum += A(i,j)*x(j,k);
                    }
                    x(i,k) = (b(i,k)-sum)/A(i,i);
                }
            }
        }else{
            int tmp = 0;
            for (int k = 0; k < dim.cols; k++) {
                for (int i = (int)dim.rows-1; i >= 0; i--) {
                    sum = zero;
                    tmp = (int)dim.rows-1;
                    for (int j = tmp; j > i; j--) {
                        sum += A(i,j)*x(j,k);
                    }
                    x(i,k) = (b(i,k)-sum)/A(i,i);
                }
            }
        }
    }
    
    
}

#endif /* UpperSolver_h */
