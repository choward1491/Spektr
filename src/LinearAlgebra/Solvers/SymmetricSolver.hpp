//
//  SymmetricSolver.hpp
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
        L.t();
        solve(L, y, x);
    }

    
}
#endif /* SymmetricSolver_h */
