//
//  Cholesky.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/31/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef Cholesky_h
#define Cholesky_h


#include "Matrix.hpp"

namespace la {

template<class T, MatType Type>
void cholesky( const Matrix<T,Type> & m, Matrix<T,Lower> & L ){
    if( !m.isSquare() ){
        printf("Error: Input matrix not square.\n");
        return;
    }
    
    if (m.size() != L.size() ) {
        L.resize(m.size());
    }
    const int numr = L.size().rows;
    
    double sum = T();
    for (int i = 0; i < numr; i++) {
        for (int j = 0; j <= i; j++) {
            sum = m(i,j);
            for (int k = 0; k < j; k++) {
                sum -= L(i,k)*L(j,k);
            }
            if( i == j ){
                if( sum < 0 ){
                    printf("Error: Non-Positive Definite Input Matrix\n");
                    return;
                }
                L(i,j) = sqrt(sum);
            }else{
                T tmp = L(j,j);
                if( tmp == T() ){
                    printf("Error: Divide by Zero\n");
                    return;
                }
                L(i,j) = sum / tmp;
            }
        }
    }
    
    
}


template<class T, MatType Type>
Matrix<T,Lower> cholesky( const Matrix<T,Type> & m ){
    Matrix<T,Lower> L(m.size());
    cholesky<T,Type>( m, L);
    return L;
}


}




#endif /* Cholesky_h */
