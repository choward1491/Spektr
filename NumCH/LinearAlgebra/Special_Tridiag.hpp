//
//  Special_Tridiag.hpp
//  NumCH
//
//  Created by Christian J Howard on 2/1/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef Special_Tridiag_h
#define Special_Tridiag_h

#include "Matrix.hpp"

namespace la {
    
    template<typename T>
    class TDMat : public Matrix<T, TDMat<T> >{
    public:
        
        
        TDMat():Matrix<T,TDMat<T>>(){}
        TDMat(int numr, int numc, T dval = T() ):Matrix<T,TDMat<T>>(numr,numc,dval){}
        TDMat(Dims dims, T dval = T() ):Matrix<T,TDMat<T>>(dims,dval){}
        ~TDMat(){}
        
        /*template<class S>
        TDMat<T> & operator=( const Matrix<T,S> & m ){
            return Matrix<T,TDMat<T>>::operator=(m);
        }
        
        TDMat<T> & operator=( const TDMat & m ){
            return Matrix<T,TDMat<T>>::operator=(m);
        }*/
        
        template <typename E>
        TDMat( MatExpression<T,E> const& mat):Matrix<T,TDMat<T>>(mat){}
        
    };
}

#endif /* Special_Tridiag_h */
