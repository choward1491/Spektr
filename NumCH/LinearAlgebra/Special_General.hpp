//
//  Special_General.hpp
//  NumCH
//
//  Created by Christian J Howard on 2/1/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef Special_General_h
#define Special_General_h

#include "Matrix.hpp"

namespace la {
    
    template<typename T>
    class Mat : public Matrix<T, Mat<T> >{
    public:
        
        Mat():Matrix<T,Mat<T>>(){}
        Mat(int numr, int numc, T dval = T() ):Matrix<T,Mat<T>>(numr,numc,dval){}
        Mat(Dims dims, T dval = T() ):Matrix<T,Mat<T>>(dims,dval){}
        ~Mat(){}
        
        

        Mat & operator=( const double v ){
            for (int i = 0; i < this->total(); i++) { (*this)(i) = static_cast<T>(v); }
            return *this;
        }
        
        Mat & operator=( const int v ){
            for (int i = 0; i < this->total(); i++) { (*this)(i) = static_cast<T>(v); }
            return *this;
        }
        
        Mat & operator=( const float v ){
            for (int i = 0; i < this->total(); i++) { (*this)(i) = static_cast<T>(v); }
            return *this;
        }
        
        
        template <typename E>
        Mat( MatExpression<T,E> const& mat):Matrix<T,Mat<T>>(mat){}
        
    };
}

#endif /* Special_General_h */
