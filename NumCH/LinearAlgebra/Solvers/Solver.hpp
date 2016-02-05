//
//  Solver.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/31/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef Solver_h
#define Solver_h

#include "LowerSolver.hpp"
#include "UpperSolver.hpp"
#include "DiagonalSolver.hpp"
#include "SymmetricSolver.hpp"
#include "ConjGrad.hpp"

namespace la {
    
    template<class T> class LMat;
    template<class T> class UMat;
    template<class T> class Mat;
    template<class T> class SMat;
    template<class T> class TDMat;
    template<class T> class DMat;
    template<class T> class SpMat;
    
    template<class T, class E>
    Mat<T> operator/( const MatExpression<T, E> & b, const LMat<T> & A){
        Mat<T> x;
        conjgradSoln(A, b, x);
        return x;
    }
    
    template<class T, class E>
    Mat<T> operator/( const MatExpression<T, E> & b, const UMat<T> & A){
        Mat<T> x;
        solve(A, b, x);
        return x;
    }
    
    template<class T, class E>
    Mat<T> operator/( const MatExpression<T, E> & b, const DMat<T> & A){
        Mat<T> x;
        solve(A, b, x);
        return x;
    }
    
    template<class T, class E>
    Mat<T> operator/( const MatExpression<T, E> & b, const SMat<T> & A){
        Mat<T> x;
        solve(A, b, x);
        return x;
    }
    
    template<class T, class E>
    Mat<T> operator/( const MatExpression<T, E> & b, const Mat<T> & A){
        Mat<T> x;
        conjgradSoln(A, b, x);
        return x;
    }
    
    template<class T, class E>
    SpMat<T> operator/( const MatExpression<T, E> & b, const SpMat<T> & A){
        SpMat<T> x;
        conjgradSoln(A, b, x);
        return x;
    }
    
    
    
}


#endif /* Solver_h */
