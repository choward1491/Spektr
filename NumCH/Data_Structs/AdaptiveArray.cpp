//
//  AdaptiveArray.cpp
//  Data_Structs
//
//  Created by Christian J Howard on 9/6/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#include "AdaptiveArray.h"

#ifndef _adaptivearray_cpp_
#define _adaptivearray_cpp_

template<typename T>
AdaptiveArray<T>::AdaptiveArray(int _numElements ){
    totalCount = _numElements;
    usedCount = 0;
    data = new T[totalCount];
}

template<typename T>
AdaptiveArray<T>::AdaptiveArray( const AdaptiveArray<T> & arr ){
    copy( arr );
}

template<typename T>
AdaptiveArray<T>::~AdaptiveArray(){
    clear();
}

template<typename T>
AdaptiveArray<T> & AdaptiveArray<T>::operator=( const AdaptiveArray<T> & arr ){
    if( this != &arr ){
        clear();
        copy(arr);
    }
    return *this;
}


template<typename T>
void AdaptiveArray<T>::push( const T & input ){
    if( totalCount == usedCount ){ resize(); }
    data[usedCount] = input;
    usedCount++;
}


template<typename T>
void AdaptiveArray<T>::resize(){
    totalCount *= 2;
    T * tmp = new T[totalCount];
    
    for (int i = 0; i < usedCount; i++) {
        tmp[i] = data[i];
    }
    
    clear();
    data = tmp;
    tmp = 0;
}

template<typename T>
void AdaptiveArray<T>::clear(){
    if( data != 0 ){
        delete [] data; data = 0;
    }
}

template<typename T>
void AdaptiveArray<T>::copy( const AdaptiveArray<T> & arr ){
    totalCount = arr.totalCount;
    usedCount = arr.usedCount;
    
    data = new T[totalCount];
    
    for (int i = 0; i < usedCount; i++) {
        data[i] = arr.data[i];
    }
}

//T data;
//int usedCount;
//int totalCount;
    





#endif