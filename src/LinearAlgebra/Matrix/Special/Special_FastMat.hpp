//
//  Special_FastMat.hpp
//  Spektr
//
//  Created by Christian J Howard on 3/25/16.
//
//  The MIT License (MIT)
//    Copyright © 2016 Christian Howard. All rights reserved.
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

#ifndef Special_FastMat_h
#define Special_FastMat_h

#include "Matrix.hpp"
#include "FastStorage.hpp"

#if __cplusplus >= 201103L
#include <initializer_list>
#endif

namespace la {
    
    template<typename T, int Rows, int Cols>
    class FastMat : public Matrix<T, FastMat<T,Rows,Cols>, FastStorage<T,Rows,Cols> >{
    public:
        
        FastMat():Matrix<T, FastMat<T,Rows,Cols>, FastStorage<T,Rows,Cols> >(){}
        FastMat(T dval ){
            for (int i = 0; i < this->data.total(); i++) {
                this->data(i) = dval;
            }
        }
        
        #if __cplusplus >= 201103L
        FastMat( std::initializer_list<T> l){
            int i = 0;
            for (const T* it = begin(l); it != end(l) && i < Rows*Cols ; ++it,i++) {
                this->data(i) = *it;
            }
            
        }
        #endif
        
        ~FastMat(){}
        
        FastMat & operator=( const double v ){
            for (int i = 0; i < this->total(); i++) { (*this)(i) = static_cast<T>(v); }
            return *this;
        }
        
        FastMat & operator=( const int v ){
            for (int i = 0; i < this->total(); i++) { (*this)(i) = static_cast<T>(v); }
            return *this;
        }
        
        FastMat & operator=( const float v ){
            for (int i = 0; i < this->total(); i++) { (*this)(i) = static_cast<T>(v); }
            return *this;
        }
        
        
        template <typename E>
        FastMat( MatExpression<T,E> const& mat):Matrix<T, FastMat<T,Rows,Cols>, FastStorage<T,Rows,Cols> >(mat){}
        
    };
}

#endif /* Special_FastMat_h */
