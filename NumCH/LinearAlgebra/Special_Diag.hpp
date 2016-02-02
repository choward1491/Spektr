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

namespace la {
    
    template<typename T>
    class DMat : public Matrix<T, DMat<T> >{
    public:
        
        DMat():Matrix<T,DMat<T>>(){}
        DMat(int numr, int numc, T dval = T() ):Matrix<T,DMat<T>>(numr,numc,dval){}
        DMat(Dims dims, T dval = T() ):Matrix<T,DMat<T>>(dims,dval){}
        ~DMat(){}
        
        /*
        template<class S>
        DMat & operator=( const Matrix<T,S> & m ){
            return Matrix<T,DMat<T>>::operator=(m);
        }
        
        DMat & operator=( const DMat & m ){
            return Matrix<T,DMat<T>>::operator=(m);
        }*/
        
        template <typename E>
        DMat( MatExpression<T,E> const& mat):Matrix<T,DMat<T>>(mat){}
        
    };
}


#endif /* Special_Diag_h */
