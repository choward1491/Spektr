//
//  MatHashes.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/30/16.
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

#ifndef MatStorage_h
#define MatStorage_h


#include <vector>
#include "MatTypes.hpp"
#include "MatHashes.hpp"
#include "Dims.hpp"

//namespace la {


template< typename T, MatType Type, class Hash = Hasher<Type>  >
class MatStorage {
public:
    
    MatStorage():table(0),nt(0),dims(0,0),dummy(T()),isT(false){}
    MatStorage(int r, int c, T dval):nt(Hash::netSize(r,c)),
                                     table(nt,dval),dims(r,c),dummy(T()),isT(false){}
    MatStorage(Dims d, T dval):nt(Hash::netSize(d.rows,d.cols)),
                               table(nt,dval),dims(d),dummy(T()),isT(false){}
    
    void resize(int r, int c){
        nt = r*c;
        dims = Dims(r,c);
        table.resize(nt);
        isT = false;
    }
    
    void transpose(){ isT = !isT; }
    bool isTransposed() const { return isT; }
    
    T & operator()(int r, int c){
        size_t k = 0;
        if( isT ){
            k = Hash::hash(c,r,dims.cols,nt);
        }else{
            k = Hash::hash(r,c,dims.cols,nt);
        }
        if( k < nt ){ return table[k]; }
        else{ dummy = cdummy; return dummy; }
    }
    const T & operator()(int r, int c) const{
        size_t k = 0;
        if( isT ){
            k = Hash::hash(c,r,dims.cols,nt);
        }else{
            k = Hash::hash(r,c,dims.cols,nt);
        }
        if( k < nt ){ return table[k]; }
        else{ return cdummy; }
    }
    T & operator()(int k){
        if( k < nt ){ return table[k]; }
        else{ dummy = cdummy; return dummy; }
    }
    const T & operator()(int k) const{
        if( k < nt ){ return table[k]; }
        else{ return cdummy; }
    }
    
    Dims size() const { if( isT ){ return Dims(dims.cols,dims.rows); } else{ return dims; } }
    int total() const { return nt; }
    
    
private:
    
    Dims dims;
    int nt;
    T dummy;
    bool isT;
    const T cdummy = T();
    std::vector<T> table;
};





#include <map>


template< typename T>
class MatStorage<T,MatType::Sparse,Hasher<MatType::Sparse>> {
public:
    typedef Hasher<MatType::Sparse> Hash;
    MatStorage():table(),nt(0),dims(0,0),dummy(T()),isT(false){}
    MatStorage(int r, int c, T dval):nt(0),table(),dims(r,c),dummy(T()),isT(false){}
    MatStorage(Dims d, T dval):nt(0),table(),dims(d),dummy(T()),isT(false){}
    
    void resize(int r, int c){
        nt = 0;
        dims = Dims(r,c);
        table = std::map<int,std::map<int,T>>();
        isT = false;
    }
    
    void transpose(){ isT = !isT; }
    bool isTransposed() const { return isT; }
    
    T & operator()(int r, int c){
        if( isT ){
            int tmp = c;
            c = r;
            r = tmp;
        }
        it1 row = table.find(r);
        if( row != table.end() ){
            it2 col = row->second.find(c);
            if( col != row->second.end() ){
                return col->second;
            }else{
                nt++;
                return row->second[c];
            }
        }else{
            nt++;
            return table[r][c];
            
        }
        dummy = cdummy; return dummy;
    }
    const T & operator()(int r, int c) const{
        if( isT ){
            int tmp = c;
            c = r;
            r = tmp;
        }
        cit1 row = table.find(r);
        if( row != table.end() ){
            cit2 col = row->second.find(c);
            if( col != row->second.end() ){
                return col->second;
            }
        }
        return cdummy;
    }
    T & operator()(int k){
        int r,c;
        if( isT ){
            getRowAndColumn(k, c, r);
        }else{
            getRowAndColumn(k, r, c);
        }
        return this->operator()(r,c);
    }
    const T & operator()(int k) const{
        int r,c;
        if( isT ){
            getRowAndColumn(k, c, r);
        }else{
            getRowAndColumn(k, r, c);
        }
        return this->operator()(r,c);
    }
    
    Dims size() const { if( isT ){ return Dims(dims.cols,dims.rows); } else{ return dims; } }
    int total() const { return nt; }
    
    
private:
    typedef typename std::map<int,std::map<int,T>>::iterator it1;
    typedef typename std::map<int,T>::iterator it2;
    typedef typename std::map<int,std::map<int,T>>::const_iterator cit1;
    typedef typename std::map<int,T>::const_iterator cit2;
    
    Dims dims;
    int nt;
    T dummy;
    const T cdummy = T();
    bool isT;
    void getRowAndColumn(int k, int & r, int & c ){
        r = k/dims.cols;
        c = k-r*dims.cols;
    }
    
    std::map<int,std::map<int,T>> table;
};


    
//}


#endif /* MatHashes_h */
