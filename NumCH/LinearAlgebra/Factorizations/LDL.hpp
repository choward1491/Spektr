//
//  GenCholesky.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/31/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef LDL_h
#define LDL_h

#include "Matrix.hpp"

namespace la {

//template<class T, MatType C>
template<class T, class C>
void LDL( const Matrix<T,C> & m, LMat<T> & L, DMat<double> & D ){
    
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
    const int numr = L.size().rows;
    
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
