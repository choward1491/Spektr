//
//  GenCholesky.hpp
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

#ifndef LDL_h
#define LDL_h

#include "Matrix.hpp"

namespace la {

//template<class T, MatType C>
template<class T, class C, class E, class F>
void LDL( const Matrix<T,C> & A, Matrix<T,E> & L, Matrix<T,F> & D ){
    // Algorithm based on one described in:
    // - Matrix Computations 4th Edition by Golub & Van Loan
    // - pg 158 LDL' decomposition
    //
    
    if( !A.isSquare() ){
        printf("Error: Input matrix not square.\n");
        return;
    }
    if (A.size() != L.size() ) {
        L.resize(A.size());
    }
    if (A.size() != D.size() ){
        D.resize(A.size());
    }
    const int numr = static_cast<int>(L.size().rows);
    
    Mat<T> v(A.size().rows,1,0);
    
    double sum = T(),sum2 = T();
    for (int j = 0; j < numr; j++) {
        sum = T();
        
        L(j,j) = 1;
        
        for( int i = 0; i < j; i++){
            v(i) = L(j,i)*D(i,i);
        }
        
        sum = A(j,j);
        for( int i = 0; i < j; i++ ){
            sum -= L(j,i)*v(i);
        }
        
        if( sum != sum ){// check for nan
            D(j,j) = 0;
        }else{
            D(j,j) = sum;
            if( sum == T() ){ sum = 1e-30; }
        }
        
        for( int k = j+1; k < numr; k++){
            sum2 = T();
            for( int i = 0; i < j; i++ ){
                sum2 += L(k,i)*v(i);
            }
            L(k,j) = (A(k,j) - sum2)/sum;
        }
    }
    
}

    
}


#endif /* LDL_h */
