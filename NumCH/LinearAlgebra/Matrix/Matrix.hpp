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
    
    
    template<typename S , class Type, MatType MT = MType<S,Type>::Type, class Storage = MatStorage<S,MT> >
    class Matrix : public MatExpression<S, Matrix<S,Type> >{
    public:
        
        Matrix():data(){}
        Matrix(int numr, int numc, S dval = S() ):data(numr,numc,dval){}
        Matrix(Dims dims, S dval = S() ):data(dims,dval){}
        ~Matrix(){}
        
        void T(){
            data.transpose();
        }
        
        bool isTransposed() const {
            return data.isTransposed();
        }
        
        template <typename E>
        Matrix( MatExpression<S,E> const& mat) : data(mat.size().rows,mat.size().cols,0.0) {
            Dims dims = data.size();
            for (size_t ir = 0; ir < dims.rows; ir++) {
                for (size_t ic=0; ic < dims.cols; ic++) {
                    data(ir,ic) = mat(ir,ic);
                }
            }
        }
        
        
        template <typename E>
        void setColumn( MatExpression<S,E> const& mat, int col = 0 ){
            if( mat.size().rows == data.size().rows ){
                for (int i = 0; i < data.size().rows; i++) {
                    data(i,col) = mat(i,0);
                }
            }
        }
        
        template <typename E>
        void getColumn( Matrix<S,E> & mat, int col = 0 ){
            if( mat.size().rows == data.size().rows ){
                for (int i = 0; i < data.size().rows; i++) {
                    mat(i,0) = data(i,col);
                }
            }
        }
        
        
        S innerProduct( int col = 0 ){
            S sum = S(), tmp;
            for (int i = 0; i < data.size().rows; i++) {
                tmp = data(i,col);
                sum += tmp*tmp;
            }
            return sum;
        }
        
        template <typename E>
        S innerProduct( const MatExpression<S,E> & A, int col = 0 ){
            Dims dim = data.size();
            assert(A.size().rows == A.size().cols);
            assert(A.size().cols == dim.rows);
            
            S sum = S();
            for (int i = 0; i < dim.rows; i++) {
                for (int j = 0; j < dim.rows; j++) {
                    sum += (data(i,col)*data(j,col)*A(i,j));
                }
            }
            
            return sum;
        }
        
        
        void resize( int numr, int numc ){ data.resize(numr,numc); }
        void resize( Dims d ){ data.resize(d.rows,d.cols); }
        
        
        S & operator()(int r, int c){return data(r,c);}
        const S & operator()(int r, int c) const{return data(r,c);}
        
        S & operator()(int k){return data(k);}
        const S & operator()(int k) const{return data(k);}
        
        S & operator[](int k){return data(k);}
        const S & operator[](int k) const{return data(k);}
        
        
        
        
        Dims size() const{return data.size();}
        size_t total() const { return data.total(); }
        bool isSquare() const { return data.size().rows == data.size().cols; }
        
        
        //template<MatType C>
        template<class C>
        void convertTo( Matrix<S,C> & m ) const{
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
                    printf("%6.6lf",(double)(*this)(ir,ic));
                }
                printf(" |\n");
            }
            printf("\n");
        }
        
        
        Matrix<S,Type> & operator=( const Matrix<S,Type> & m ){
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
        
        //template<MatType C>
        template<class C>
        Matrix<S,Type> & operator=( const MatExpression<S,C> & m ){
                
            if( !(data.size() == m.size()) ){
                resize(m.size().rows, m.size().cols);
            }
            
            for (int i = 0; i < data.size().rows; i++) {
                for (int j = 0; j < data.size().cols; j++ ){
                    data(i,j) = m(i,j);
                }
            }
            
            return *this;
        }
        
        
        
    private:
        Storage data;
        
    };
    
    
    /*
        template<typename S, class Type, typename S>
        void operator=( Matrix<S,Type> & m, const S & val ){
            for (int i = 0; i < m.total(); i++) {
                m(i) = static_cast<S>(val);
            }
        }
    */
    
    
}







#include "Special_General.hpp"
#include "Special_Lower.hpp"
#include "Special_Upper.hpp"
#include "Special_Diag.hpp"
#include "Special_Tridiag.hpp"
#include "Special_Sparse.hpp"
#include "Special_Symmetric.hpp"



#endif /* Matrix_hpp */
