//
//  Special_Lower.hpp
//  NumCH
//
//  Created by Christian J Howard on 2/1/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//
//  The MIT License (MIT)
//  Copyright © 2016 Christian Howard. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
//
//

#ifndef Special_Lower_h
#define Special_Lower_h

#include "Matrix.hpp"
#include "LowerSolver.hpp"
#include "Cholesky.hpp"
#include "LDL.hpp"

namespace la {
    
    template<typename T>
    class LMat : public Matrix<T, LMat<T> >{
    public:
        
        LMat():Matrix<T,LMat<T>>(){}
        LMat(int numr, int numc, T dval = T() ){
            this->data.resize(numr,numc,dval);
        }
        LMat(Dims dims, T dval = T() ){
            this->data.resize(dims,dval);
        }
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
            if( x.size().rows == this->size().rows && (x.size().cols == 1 || x.isSquare()) ){
                if( x.size().cols == 1 ){
                    Dims d = this->size();
                    Matrix<T,C> xt = x;
                    
                    for( int k = 0; k < d.rows; k++ ){
                        T lkk = (*this)(k,k);
                        T xk  = xt(k);
                        T r = static_cast<T>(sqrt(static_cast<double>(lkk*lkk+xk*xk)));
                        T c = r / lkk;
                        T s = xk / lkk;
                        (*this)(k,k) = r;
                        for(int l = k+1; l < d.rows; l++){
                            (*this)(l,k) = ( (*this)(l,k) + s*xt(l) ) / c;
                            xt(l) = c*xt(l) - s*(*this)(l,k);
                        }
                    }
                }else{
                    Dims d = this->size();
                    LMat L(d,0);
                    cholesky(x, L);
                    
                    for( int i = 0; i < d.rows; i++ ){
                        for( int k = 0; k < d.rows; k++ ){
                            T lkk = (*this)(k,k);
                            T xk  = L(k,i);
                            T r = static_cast<T>(sqrt(static_cast<double>(lkk*lkk+xk*xk)));
                            T c = r / lkk;
                            T s = xk / lkk;
                            (*this)(k,k) = r;
                            for(int l = k+1; l < d.rows; l++){
                                (*this)(l,k) = ( (*this)(l,k) + s*L(l,i) ) / c;
                                L(l,i) = c*L(l,i) - s*(*this)(l,k);
                            }
                        }
                    }
                    
                    
                }
                
            }else{ assert(false); }
        }
        
        template<class C>
        void rankOneDowndate( const Matrix<T,C> & x ){
            if( x.size().rows == this->size().rows && (x.size().cols == 1 || x.isSquare()) ){
                if( x.size().cols == 1 ){
                    Dims d = this->size();
                    Matrix<T,C> xt = x;
                    
                    for( int k = 0; k < d.rows; k++ ){
                        T lkk = (*this)(k,k);
                        T xk  = xt(k);
                        T r = static_cast<T>(sqrt(static_cast<double>(lkk*lkk-xk*xk)));
                        T c = r / lkk;
                        T s = xk / lkk;
                        (*this)(k,k) = r;
                        for(int l = k+1; l < d.rows; l++){
                            (*this)(l,k) = ( (*this)(l,k) - s*xt(l) ) / c;
                            xt(l) = c*xt(l) - s*(*this)(l,k);
                        }
                    }
                }else{
                    Dims d = this->size();
                    LMat L(d,0);
                    DMat<T> D(d,0);
                    //cholesky(x, L);
                    LDL(x, L, D);
                    
                    for( int i = 0; i < d.rows; i++ ){
                        for( int k = 0; k < d.rows; k++ ){
                            L(i,k) *= sqrt(fmax(D(k,k),0));
                        }
                    }
                    
                    for( int i = 0; i < d.rows; i++ ){
                        if( fmax(D(i,i),0) != 0 ){
                            for( int k = 0; k < d.rows; k++ ){
                                T lkk = (*this)(k,k);
                                T xk  = L(k,i);
                                T r = static_cast<T>(sqrt(static_cast<double>(lkk*lkk-xk*xk)));
                                T c = r / lkk;
                                T s = xk / lkk;
                                (*this)(k,k) = r;
                                for(int l = k+1; l < d.rows; l++){
                                    (*this)(l,k) = ( (*this)(l,k) - s*L(l,i) ) / c;
                                    L(l,i) = c*L(l,i) - s*(*this)(l,k);
                                }
                            }
                        }
                    }
                    
                    
                }

            }else{ assert(false); }
        }
        
        
    };
}

#endif /* Special_Lower_h */
