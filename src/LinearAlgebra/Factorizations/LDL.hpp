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
void LDL( const Matrix<T,C> & m, Matrix<T,E> & L, Matrix<T,F> & D ){
    
    if( !m.isSquare() ){
        printf("Error: Input matrix not square.\n");
        return;
    }
    if (m.size() != L.size() ) {
        L.resize(m.size());
    }
    if (m.size() != D.size() ){
        D.resize(m.size());
    }
    const int numr = static_cast<int>(L.size().rows);
    
    double sum = T();
    for (int i = 0; i < numr; i++) {
        for (int j = 0; j <= i; j++) {
            sum = m(i,j);
            for (int k = 0; k < j; k++) {
                sum -= L(i,k)*L(j,k)*D(k);
            }
            if( i == j ){
                D(i) = sum;
                L(i,i) = 1;
            }else{
                T tmp = D(j);
                if( tmp == T() ){
                    printf("Error: Divide by Zero\n");
                    return;
                }
                L(i,j) = sum / tmp;
            }
        }
    }
}

    
}


#endif /* LDL_h */
