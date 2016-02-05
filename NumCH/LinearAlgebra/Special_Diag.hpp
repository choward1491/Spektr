//
//  Special_Diag.hpp
//  NumCH
//
//  Created by Christian J Howard on 2/1/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef Special_Diag_h
#define Special_Diag_h

#include "Matrix.hpp"
#include "DiagonalSolver.hpp"

namespace la {
    
    template<typename T>
    class DMat : public Matrix<T, DMat<T> >{
    public:
        
        DMat():Matrix<T,DMat<T>>(){}
        DMat(int numr, int numc, T dval = T() ):Matrix<T,DMat<T>>(numr,numc,dval){}
        DMat(Dims dims, T dval = T() ):Matrix<T,DMat<T>>(dims,dval){}
        ~DMat(){}
        
        DMat & operator=( const double v ){
            for (int i = 0; i < this->total(); i++) { (*this)(i) = static_cast<T>(v); }
            return *this;
        }
        
        DMat & operator=( const int v ){
            for (int i = 0; i < this->total(); i++) { (*this)(i) = static_cast<T>(v); }
            return *this;
        }
        
        DMat & operator=( const float v ){
            for (int i = 0; i < this->total(); i++) { (*this)(i) = static_cast<T>(v); }
            return *this;
        }
        
        
        template <typename E>
        DMat( MatExpression<T,E> const& mat):Matrix<T,DMat<T>>(mat){}
        
    };
}


#endif /* Special_Diag_h */
