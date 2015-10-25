//
//  Coordinate.h
//  Data_Structs
//
//  Created by Christian J Howard on 9/4/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#ifndef __Data_Structs__Coordinate__
#define __Data_Structs__Coordinate__

#include <stdio.h>

template<int D>
class Coordinate {
public:
    
    double & operator[](int index){ return point[index]; }
    const double & operator[](int index) const { return point[index]; }
    Coordinate<D> & operator=( const Coordinate<D> & coord );
    void fprint( FILE * file) const;
    void fprintln( FILE * file) const;
    void print() const;
    void println() const;
    double point[D];
    int size() const { return D; }
    
    
};

#ifndef _coordinate_cpp_
#include "Coordinate.cpp"
#endif


#endif /* defined(__Data_Structs__Coordinate__) */
