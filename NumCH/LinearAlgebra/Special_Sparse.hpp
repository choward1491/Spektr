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
        
        SpMat & operator=( const double v ){
            for (int i = 0; i < this->total(); i++) { (*this)(i) = static_cast<T>(v); }
            return *this;
        }
        
        SpMat & operator=( const int v ){
            for (int i = 0; i < this->total(); i++) { (*this)(i) = static_cast<T>(v); }
            return *this;
        }
        
        SpMat & operator=( const float v ){
            for (int i = 0; i < this->total(); i++) { (*this)(i) = static_cast<T>(v); }
            return *this;
        }
        
        template <typename E>
        SpMat( MatExpression<T,E> const& mat):Matrix<T,SpMat<T>>(mat){}
        
    };
    
}

#endif /* Special_Sparse_h */
