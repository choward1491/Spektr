//
//  Vec.cpp
//  Data_Structs
//
//  Created by Christian J Howard on 9/4/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#include "Vec.h"

#ifndef _vec_cpp_
#define _vec_cpp_


template<typename T>
Vec<T>::Vec( int num ){
    N = num;
    data = new T[num];
}

template<typename T>
Vec<T>::Vec( const Vec<T> & v ){
    copy(v);
}

template<typename T>
Vec<T>::~Vec(){
    clear();
}

template<typename T>
Vec<T> & Vec<T>::operator=( const Vec<T> & v ){
    if( this != &v ){
        clear();
        copy( v );
    }
    return *this;
}



template<typename T>
void Vec<T>::clear(){
    if( data != 0 ){
        delete [] data; data = 0;
    }
}

template<typename T>
void Vec<T>::copy( const Vec<T> & v ){
    N = v.size();
    data = new T[N];
    
    for( int i = 0; i < N; i++ ){
        data[i] = v[i];
    }
}




#endif