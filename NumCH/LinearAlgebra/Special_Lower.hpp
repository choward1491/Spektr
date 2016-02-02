//
//  Special_Lower.hpp
//  NumCH
//
//  Created by Christian J Howard on 2/1/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef Special_Lower_h
#define Special_Lower_h

#include "Matrix.hpp"

namespace la {
    
    template<typename T>
    class LMat : public Matrix<T, LMat<T> >{
    public:
        
        LMat():Matrix<T,LMat<T>>(){}
        LMat(int numr, int numc, T dval = T() ):Matrix<T,LMat<T>>(numr,numc,dval){}
        LMat(Dims dims, T dval = T() ):Matrix<T,LMat<T>>(dims,dval){}
        ~LMat(){}
        
        template <typename E>
        LMat( MatExpression<T,E> const& mat):Matrix<T,LMat<T>>(mat){}
        
        
        /*template<class S>
        LMat<T> & operator=( const Matrix<T,S> & m ){
            return Matrix<T,LMat<T>>::operator=(m);
        }
        
        LMat<T> & operator=( const LMat & m ){
            return Matrix<T,LMat<T>>::operator=(m);
        }*/
        
        
        template<class C>
        void rankOneUpdate( const Matrix<T,C> & x ){
                
        }
        
        template<class C>
        void rankOneDowndate( const Matrix<T,C> & x ){
            
        }
        
        
    };
}

#endif /* Special_Lower_h */
