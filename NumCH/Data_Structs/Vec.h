//
//  Vec.h
//  Data_Structs
//
//  Created by Christian J Howard on 9/4/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#ifndef __Data_Structs__Vec__
#define __Data_Structs__Vec__

#include <stdio.h>



template<typename T>
class Vec {
public:
    Vec( int num = 1 );
    Vec( const Vec<T> & v );
    ~Vec();
    
    T & operator[](int index){ return data[index]; }
    T & operator[](int index) const { return data[index]; }
    Vec<T> & operator=( const Vec<T> & v );
    
    int size() const { return N; }
    
private:
    
    void clear();
    void copy( const Vec<T> & v );
    
    
    T* data;
    int N;
};


#ifndef _vec_cpp_
#include "Vec.cpp"
#endif

#endif /* defined(__Data_Structs__Vec__) */
