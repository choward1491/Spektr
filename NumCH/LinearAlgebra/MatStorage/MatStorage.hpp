//
//  MatHashes.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/30/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef MatStorage_h
#define MatStorage_h


#include <vector>
#include "MatTypes.hpp"
#include "MatHashes.hpp"
#include "Dims.hpp"

template< typename T, MatType Type, class Hash = Hasher<Type>  >
class MatStorage {
public:
    
    MatStorage():table(0),nt(0),dims(0,0),dummy(T()){}
    MatStorage(int r, int c, T dval):nt(Hash::netSize(r,c)),table(nt,dval),dims(r,c),dummy(T()){}
    MatStorage(Dims d, T dval):nt(Hash::netSize(d.rows,d.cols)),table(nt,dval),dims(d),dummy(T()){}
    
    void resize(int r, int c){
        nt = r*c;
        dims = Dims(r,c);
        table.resize(nt);
    }
    
    T & operator()(int r, int c){
        size_t k = Hash::hash(r,c,dims.cols,nt);
        if( k < nt ){ return table[k]; }
        else{ dummy = cdummy; return dummy; }
    }
    const T & operator()(int r, int c) const{
        size_t k = Hash::hash(r,c,dims.cols,nt);
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
    
    Dims size() const { return dims; }
    int total() const { return nt; }
    
    
private:
    
    Dims dims;
    int nt;
    T dummy;
    const T cdummy = T();
    std::vector<T> table;
};





#include <map>


template< typename T>
class MatStorage<T,MatType::Sparse,Hasher<MatType::Sparse>> {
public:
    typedef Hasher<MatType::Sparse> Hash;
    MatStorage():table(),nt(0),dims(0,0),dummy(T()){}
    MatStorage(int r, int c, T dval):nt(0),table(),dims(r,c),dummy(T()){}
    MatStorage(Dims d, T dval):nt(0),table(),dims(d),dummy(T()){}
    
    void resize(int r, int c){
        nt = 0;
        dims = Dims(r,c);
        table = std::map<int,std::map<int,T>>();
    }
    
    T & operator()(int r, int c){
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
        getRowAndColumn(k, r, c);
        return this->operator()(r,c);
    }
    const T & operator()(int k) const{
        int r,c;
        getRowAndColumn(k, r, c);
        return this->operator()(r,c);
    }
    
    Dims size() const { return dims; }
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
    
    void getRowAndColumn(int k, int & r, int & c ){
        r = k/dims.cols;
        c = k-r*dims.cols;
    }
    
    std::map<int,std::map<int,T>> table;
};




#endif /* MatHashes_h */
