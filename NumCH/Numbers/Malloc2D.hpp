//
//  Malloc2D.cpp
//  NumCH
//
//  Created by Christian J Howard on 11/4/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include <stdlib.h>


template<typename T>
T** malloc2D( int rows, int cols ){
    int pointers = rows * sizeof(T*); // will point to start of given row
    int data = rows * cols * sizeof(T); // holds all the matrix data
    T** matrix = (T**)malloc(pointers + data);
    if( matrix == 0 ){ return 0; }
    
    T* buffer = (T*) (matrix + rows);
    for(int i = 0; i < rows; i++){
        matrix[i] = buffer + i*cols;
    }
    return matrix;
    
}