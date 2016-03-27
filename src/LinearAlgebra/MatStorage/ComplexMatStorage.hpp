//
//  ComplexMatStorage.hpp
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

#ifndef ComplexMatStorage_h
#define ComplexMatStorage_h

#include "MatStorage.hpp"
#include "Complex.hpp"

template<typename S, MatType Type, class Hash >
class MatStorage<Complex<S>, Type, Hash> {
public:
    
    MatStorage():table(0),nt(0),dims(0,0),isT(false){
        
    }
    MatStorage(int r, int c, Complex<S> dval):nt(Hash::netSize(r,c)),
    table(nt,dval),dims(r,c),isT(false){
        
    }
    MatStorage(Dims d, Complex<S> dval):nt(Hash::netSize(d.rows,d.cols)),
    table(nt,dval),dims(d),isT(false){
        
    }
    
    void resize(int r, int c, Complex<S> dval = static_cast<Complex<S>>(0)){
        nt = Hash::netSize(r,c);
        dims = Dims(r,c);
        table.resize(nt,dval);
        isT = false;
    }
    void resize(Dims d, Complex<S> dval = static_cast<Complex<S>>(0)){
        nt = Hash::netSize(d.rows,d.cols);
        dims = Dims(d.rows,d.cols);
        table.resize(nt,dval);
        isT = false;
    }
    
    void transpose(){
        isT = !isT;
        for (int i = 0; table.size(); i++) {
            table[i].conj();
        }
    }
    bool isTransposed() const{
        return isT;
    }
    
    Complex<S> & operator()(int r, int c){
        size_t k = 0;
        if( isT ){
            k = Hash::hash(c,r,dims.cols,nt);
        }else{
            k = Hash::hash(r,c,dims.cols,nt);
        }
        return table[k%nt];
    }
    const Complex<S> & operator()(int r, int c) const{
        size_t k = 0;
        if( isT ){
            k = Hash::hash(c,r,dims.cols,nt);
        }else{
            k = Hash::hash(r,c,dims.cols,nt);
        }
        return table[k%nt];
    }
    Complex<S> & operator()(int k){
        return table[k%nt];
    }
    const Complex<S> & operator()(int k) const{
        return table[k%nt];
    }
    
    Dims size() const{
        if( isT ){
            return Dims(dims.cols,dims.rows);
        } else{ return dims; }
    }
    int total() const{
        return nt;
    }
    
    void print() const{
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
    
    Dims dims;
    int nt;
    bool isT;
    std::vector<Complex<S>> table;
};


#endif /* ComplexMatStorage_h */
