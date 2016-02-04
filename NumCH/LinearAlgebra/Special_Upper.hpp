//
//  Special_Upper.hpp
//  NumCH
//
//  Created by Christian J Howard on 2/1/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef Special_Upper_h
#define Special_Upper_h

#include "Matrix.hpp"

namespace la {
    
    template<typename T>
    class UMat : public Matrix<T, UMat<T> >{
    public:
        
        UMat():Matrix<T,UMat<T>>(){}
        UMat(int numr, int numc, T dval = T() ):Matrix<T,UMat<T>>(numr,numc,dval){}
        UMat(Dims dims, T dval = T() ):Matrix<T,UMat<T>>(dims,dval){}
        ~UMat(){}
        
        UMat & operator=( const double v ){
            for (int i = 0; i < this->total(); i++) { (*this)(i) = static_cast<T>(v); }
            return *this;
        }
        
        UMat & operator=( const int v ){
            for (int i = 0; i < this->total(); i++) { (*this)(i) = static_cast<T>(v); }
            return *this;
        }
        
        UMat & operator=( const float v ){
            for (int i = 0; i < this->total(); i++) { (*this)(i) = static_cast<T>(v); }
            return *this;
        }
        
        template <typename E>
        UMat( MatExpression<T,E> const& mat):Matrix<T,UMat<T>>(mat){}
        
    };
}

#endif /* Special_Upper_h */
