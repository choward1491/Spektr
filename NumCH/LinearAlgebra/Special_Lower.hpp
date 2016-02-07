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
