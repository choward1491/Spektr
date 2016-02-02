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
        
        
        /*template<class S>
        Mat<T> & operator=( const Matrix<T,S> & m ){
            return Matrix<T,Mat<T>>::operator=(m);
        }*/
        
       /* Mat<T> & operator=( const Mat & m ){
            return Matrix<T,Mat<T>>::operator=(m);
        }
        */
        
        
        template <typename E>
        Mat( MatExpression<T,E> const& mat):Matrix<T,Mat<T>>(mat){}
        
    };
}

#endif /* Special_General_h */
