//
//  Special_Symmetric.hpp
//  NumCH
//
//  Created by Christian J Howard on 2/1/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef Special_Symmetric_h
#define Special_Symmetric_h

#include "Matrix.hpp"

namespace la {
    
    template<typename T>
    class SMat : public Matrix<T, SMat<T>>{
    public:
        
        SMat():Matrix<T,SMat<T>>(){}
        SMat(int numr, int numc, T dval = T() ):Matrix<T,SMat<T>>(numr,numc,dval){}
        SMat(Dims dims, T dval = T() ):Matrix<T,SMat<T>>(dims,dval){}
        ~SMat(){}
        
        /*template<class S>
        SMat & operator=( const Matrix<T,S> & m ){
            return Matrix<T,SMat<T>>::operator=(m);
        }
        
        SMat & operator=( const SMat & m ){
            return Matrix<T,SMat<T>>::operator=(m);
        }*/
        
        template <typename E>
        SMat( MatExpression<T,E> const& mat):Matrix<T,SMat<T>>(mat){}
        
    };
}

#endif /* Special_Symmetric_h */
