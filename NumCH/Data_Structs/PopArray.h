//
//  PopArray.h
//  Data_Structs
//
//  Created by Christian J Howard on 9/5/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#ifndef __Data_Structs__PopArray__
#define __Data_Structs__PopArray__

#include <stdio.h>

template<typename T>
class PopArray {
public:
    PopArray(int _numElements=0);
    ~PopArray();
    PopArray<T> & operator=( const PopArray<T> & arr );
    T & operator[](int index){ return data[index]; }
    T & operator[](int index) const { return data[index]; }
    T pop(int index);
    int size() const { return numElements; }
    
private:
    void clear();
    void copy( const PopArray<T> & arr );
    T* data;
    int numElements;
};


#ifndef _poparray_cpp_
#include "PopArray.cpp"
#endif

#endif /* defined(__Data_Structs__PopArray__) */
