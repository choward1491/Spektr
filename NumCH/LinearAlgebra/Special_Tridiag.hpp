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
        
        TDMat & operator=( const double v ){
            for (int i = 0; i < this->total(); i++) { (*this)(i) = static_cast<T>(v); }
            return *this;
        }
        
        TDMat & operator=( const int v ){
            for (int i = 0; i < this->total(); i++) { (*this)(i) = static_cast<T>(v); }
            return *this;
        }
        
        TDMat & operator=( const float v ){
            for (int i = 0; i < this->total(); i++) { (*this)(i) = static_cast<T>(v); }
            return *this;
        }
        
        template <typename E>
        TDMat( MatExpression<T,E> const& mat):Matrix<T,TDMat<T>>(mat){}
        
    };
}

#endif /* Special_Tridiag_h */
