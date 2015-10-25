//
//  Coordinate.cpp
//  Data_Structs
//
//  Created by Christian J Howard on 9/4/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#include "Coordinate.h"

#ifndef _coordinate_cpp_
#define _coordinate_cpp_

template<int D>
void Coordinate<D>::fprint( FILE * file) const{
    fprintf(file, "{ ");
    for(int i = 0; i < D; i++ ){
        if( i == 0 ){
            fprintf(file, "%lf",point[i]);
        }else{
            fprintf(file, ", %lf",point[i]);
        }
    }
    fprintf(file, " }");
}
template<int D>
void Coordinate<D>::fprintln( FILE * file) const{
    fprint(file); fprintf(file, "\n");
}


template<int D>
void Coordinate<D>::print() const{
    
    printf("{ ");
    for(int i = 0; i < D; i++ ){
        if( i == 0 ){
            printf("%lf",point[i]);
        }else{
            printf(", %lf",point[i]);
        }
    }
    printf(" }");
    
}


template<int D>
void Coordinate<D>::println() const{
    print(); printf("\n");
}

template<int D>
Coordinate<D> & Coordinate<D>::operator=( const Coordinate<D> & coord ){
    if( this != &coord ){
        for (int i = 0; i < D; i++) {
            point[i] = coord[i];
        }
    }
    
    return *this;
}


#endif