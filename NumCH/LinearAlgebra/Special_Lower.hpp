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
#include "LowerSolver.hpp"

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
        
        
        LMat & operator=( const double v ){
            for (int i = 0; i < this->total(); i++) { (*this)(i) = static_cast<T>(v); }
            return *this;
        }
        
        LMat & operator=( const int v ){
            for (int i = 0; i < this->total(); i++) { (*this)(i) = static_cast<T>(v); }
            return *this;
        }
        
        LMat & operator=( const float v ){
            for (int i = 0; i < this->total(); i++) { (*this)(i) = static_cast<T>(v); }
            return *this;
        }
        
        
        
        template<class C>
        void rankOneUpdate( const Matrix<T,C> & x ){
                
        }
        
        template<class C>
        void rankOneDowndate( const Matrix<T,C> & x ){
            
        }
        
        
    };
}

#endif /* Special_Lower_h */
