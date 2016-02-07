//
//  Solver.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/31/16.
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
