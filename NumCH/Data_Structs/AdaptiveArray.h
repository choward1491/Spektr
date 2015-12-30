//
//  AdaptiveArray.h
//  Data_Structs
//
//  Created by Christian J Howard on 9/6/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#ifndef __Data_Structs__AdaptiveArray__
#define __Data_Structs__AdaptiveArray__

#include <stdio.h>


template<typename T>
class AdaptiveArray {
public:
    AdaptiveArray();
    AdaptiveArray(int _numElements);
    AdaptiveArray( const AdaptiveArray<T> & arr );
    ~AdaptiveArray();
    AdaptiveArray<T> & operator=( const AdaptiveArray<T> & arr );
    T & operator[](int index){ return data[index]; }
    T & operator[](int index) const { return data[index]; }
    void push( const T & input );
    int size() const { return usedCount; }
    
private:
    template< typename U>
    friend class AdaptiveArray;
    
    void resize();
    void clear();
    void copy( const AdaptiveArray<T> & arr );
    
    T* data;
    int usedCount;
    int totalCount;
    
};


#ifndef _adaptivearray_cpp_
#include "AdaptiveArray.cpp"
#endif

#endif /* defined(__Data_Structs__AdaptiveArray__) */
