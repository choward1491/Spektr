//
//  ComplexFastStorage.hpp
//  Spektr
//
//  Created by Christian J Howard on 3/27/16.
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

#ifndef ComplexFastStorage_h
#define ComplexFastStorage_h

#include "FastStorage.hpp"
#include "Complex.hpp"

template<typename S,int Rows, int Cols  >
class FastStorage<Complex<S>,Rows,Cols> {
public:
    
    FastStorage(Complex<S> dval = Complex<S>() ):dims(Rows,Cols){
        nt = Rows*Cols+1;
        isT = false;
        for (int i = 0; i < nt; i++) {
            data[i] = dval;
        }
    }
    FastStorage(int dummyRows, int dummyCols, Complex<S> dval = Complex<S>() ):dims(Rows,Cols){
        nt = Rows*Cols+1;
        isT = false;
        for (int i = 0; i < nt; i++) {
            data[i] = dval;
        }
    }
    
    void transpose(){
        isT = !isT;
        for (int i = 0; i < nt; i++) {
            data[i].conj();
        }
    }
    bool isTransposed() const{
        return isT;
    }
    
    Complex<S> & operator()(int r, int c){
        int k = 0;
        if( isT ){
            k = Hash::hash(c,r,Cols,nt);
        }else{
            k = Hash::hash(r,c,Cols,nt);
        }
        return data[k%nt];
    }
    const Complex<S> & operator()(int r, int c) const{
        int k = 0;
        if( isT ){
            k = Hash::hash(c,r,Cols,nt);
        }else{
            k = Hash::hash(r,c,Cols,nt);
        }
        return data[k%nt];
    }
    Complex<S> & operator()(int k){
        return data[k%nt];
    }
    const Complex<S> & operator()(int k) const{
        return data[k%nt];
    }
    
    Dims size() const{
        if( isT ){ return Dims(Cols,Rows); }
        return dims;
    }
    int total() const{
        return nt;
    }
    
    void print() const {
        
        Dims d = size();
        for (size_t ir=0; ir < d.rows; ir++) {
            printf("| ");
            for (size_t ic=0; ic < d.cols; ic++) {
                if( ic != 0 ){ printf(", "); }
                (*this)(ir,ic).print();
                
            }
            printf(" |\n");
        }
        printf("\n");
    }
    
    
private:
    
    typedef Hasher<General> Hash;
    Dims dims;
    Complex<S> data[Rows*Cols+1];
    int nt;
    bool isT;
};


#endif /* ComplexFastStorage_h */
