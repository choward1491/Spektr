//
//  SymmetricSolver.hpp
//  NumCH
//
//  Created by Christian J Howard on 2/4/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef SymmetricSolver_h
#define SymmetricSolver_h

#include "LDL.hpp"
#include "DiagonalSolver.hpp"
#include "LowerSolver.hpp"

namespace la {
    
    template<class T> class LMat;
    template<class T> class UMat;
    template<class T> class Mat;
    template<class T> class SMat;
    template<class T> class TDMat;
    template<class T> class DMat;
    template<class T> class SpMat;
    

    template<class T, class C, class O>
    void solve( const SMat<T> & A, const MatExpression<T,C> & b, Matrix<T,O> & x ){
        assert(A.isSquare());
        assert(A.size().cols == b.size().rows);
        Dims dim = b.size();
        if( x.size() != dim ){
            x.resize(dim);
        }
        
        LMat<T> L; DMat<T> D;
        Mat<T> y(x),z(x);
        LDL(A, L, D);
        solve(L, b, y);
        solve(D, y, y);
        L.T();
        solve(L, y, x);
    }

    
}
#endif /* SymmetricSolver_h */
