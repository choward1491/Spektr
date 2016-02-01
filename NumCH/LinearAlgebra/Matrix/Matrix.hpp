//
//  Matrix.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/30/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <stdio.h>
#include "MatrixExpression.hpp"
#include "MatStorage.hpp"
#include "AllMatExprs.hpp"


namespace la {
    
    
    template<typename T , MatType Type , class Storage = MatStorage<T,Type> >
    class Matrix : public MatExpression<T, Matrix<T,Type> >{
    public:
        static const enum MatType type = Type;
        
        
        Matrix():data(){}
        Matrix(int numr, int numc, T dval = T() ):data(numr,numc,dval){}
        Matrix(Dims dims, T dval = T() ):data(dims,dval){}
        ~Matrix(){}
        
        template <typename E>
        Matrix( MatExpression<T,E> const& mat) : data(mat.size().rows,mat.size().cols,0.0) {
            Dims dims = data.size();
            for (size_t ir = 0; ir < dims.rows; ir++) {
                for (size_t ic=0; ic < dims.cols; ic++) {
                    data(ir,ic) = mat(ir,ic);
                }
            }
        }
        
        void resize( int numr, int numc ){ data.resize(numr,numc); }
        void resize( Dims & d ){ data.resize(d.rows,d.cols); }
        void resize( Dims d ){ data.resize(d.rows,d.cols); }
        
        
        T & operator()(int r, int c){return data(r,c);}
        const T & operator()(int r, int c) const{return data(r,c);}
        
        T & operator()(int k){return data(k);}
        const T & operator()(int k) const{return data(k);}
        
        T & operator[](int k){return data(k);}
        const T & operator[](int k) const{return data(k);}
        
        
        
        
        Dims size() const{return data.size();}
        bool isSquare() const { return data.size().rows == data.size().cols; }
        
        
        template<MatType S>
        void convertTo( Matrix<T,S> & m ) const{
            Dims dims = data.size();
            if( !( dims == m.size() ) ){ m.resize(dims.rows,dims.cols); }
            for (size_t ir=0; ir < dims.rows; ir++) {
                for (size_t ic=0; ic < dims.cols; ic++) {
                    m(ir,ic) = (*this)(ir,ic);
                }
            }
        }
        
        
        void print() const{
            Dims dims = data.size();
            for (size_t ir=0; ir < dims.rows; ir++) {
                printf("| ");
                for (size_t ic=0; ic < dims.cols; ic++) {
                    if( ic != 0 ){ printf(", "); }
                    printf("%6.3lf",(double)(*this)(ir,ic));
                }
                printf(" |\n");
            }
            printf("\n");
        }
        
        
        void operator=( const T & val ){
            for (int i = 0; i < data.total(); i++) {
                data(i) = val;
            }
        }
        
        template<MatType S>
        Matrix<T,Type> & operator=( const Matrix<T,S> & m ){
            if( this != & m ){
                
                if( !(data.size() == m.size()) ){
                    resize(m.size().rows, m.size().cols);
                }
                
                for (int i = 0; i < data.size().rows; i++) {
                    for (int j = 0; j < data.size().cols; j++ ){
                        data(i,j) = m(i,j);
                    }
                }
            }
            
            return *this;
        }
        
        
    private:
        Storage data;
        
    };
    
    
}

#endif /* Matrix_hpp */
