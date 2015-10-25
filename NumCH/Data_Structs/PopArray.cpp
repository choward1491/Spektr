//
//  PopArray.cpp
//  Data_Structs
//
//  Created by Christian J Howard on 9/5/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#include "PopArray.h"

#ifndef _poparray_cpp_
#define _poparray_cpp_


template<typename T>
PopArray<T>::PopArray(int _numElements):numElements(_numElements){
    if( numElements > 0 ){
        data = new T[numElements];
    }else{
        data = 0;
    }
}

template<typename T>
PopArray<T>::~PopArray(){
    clear();
}

template<typename T>
PopArray<T> & PopArray<T>::operator=( const PopArray<T> & arr ){
    if( this != &arr ){
        clear();
        copy( arr );
    }
    return *this;
}


template<typename T>
T PopArray<T>::pop(int index){
    if (index > 0 && index < numElements) {
        T output = data[index];
        numElements--;
        data[index] = data[numElements];
        return output;
    }else{
        return T();
    }
}

template<typename T>
void PopArray<T>::clear(){
    if( data != 0 ){
        delete [] data;
    }
}

template<typename T>
void PopArray<T>::copy( const PopArray<T> & arr ){
    numElements = arr.size();
    data = new T[numElements];
    for( int i = 0; i < numElements; i++ ){
        data[i] = arr[i];
    }
}



#endif