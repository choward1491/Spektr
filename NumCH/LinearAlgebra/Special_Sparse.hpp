//
//  Special_Sparse.hpp
//  NumCH
//
//  Created by Christian J Howard on 2/1/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef Special_Sparse_h
#define Special_Sparse_h

#include "Matrix.hpp"

namespace la {
    
    template<typename T>
    class SpMat : public Matrix<T, SpMat<T> >{
    public:
        
        SpMat():Matrix<T,SpMat<T>>(){}
        SpMat(int numr, int numc, T dval = T() ):Matrix<T,SpMat<T>>(numr,numc,dval){}
        SpMat(Dims dims, T dval = T() ):Matrix<T,SpMat<T>>(dims,dval){}
        ~SpMat(){}
        
        /*template<class S>
        SpMat<T> & operator=( const Matrix<T,S> & m ){
            return Matrix<T,SpMat<T>>::operator=(m);
        }
        
        SpMat<T> & operator=( const SpMat & m ){
            return Matrix<T,SpMat<T>>::operator=(m);
        }*/
        
        template <typename E>
        SpMat( MatExpression<T,E> const& mat):Matrix<T,SpMat<T>>(mat){}
        
    };
    
}

#endif /* Special_Sparse_h */
