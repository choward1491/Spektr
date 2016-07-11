//
//  MatHashes.cpp
//  NumCH
//
//  Created by Christian J Howard on 1/30/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include "MatHashes.hpp"


//namespace la {

// template specialization for diagonal matrix
size_t Hasher<Diagonal>::hash(int i, int j, int nc, int nt){
    if( i == j ){ return i; }
    else{ return nt; }
}

size_t Hasher<Diagonal>::netSize(int r, int c){
    return r < c ? r : c;
}




// template specialization for symmetric matrix
size_t Hasher<Symmetric>::hash(int i, int j, int nc, int nt){
    if( i < j ){ return (j*(j+1))/2 + i; }
    else{ return (i*(i+1))/2 + j; }
}

size_t Hasher<Symmetric>::netSize(int r, int c){
    int mi = r < c ? r : c;
    return (mi*(mi+1))/2;
}





// template specialization for lower matrix
size_t Hasher<Lower>::hash(int i, int j, int nc, int nt){
    if( i < j ){ return nt; }
    else{ return (i*(i+1))/2 + j; }
}

size_t Hasher<Lower>::netSize(int r, int c){
    int mi = r < c ? r : c;
    return (mi*(mi+1))/2;
}




// template specialization for Upper matrix
size_t Hasher<Upper>::hash(int i, int j, int nc, int nt){
    if( i > j ){ return nt; }
    else{ return (j*(j+1))/2 + i; }
}

size_t Hasher<Upper>::netSize(int r, int c){
    int mi = r < c ? r : c;
    return (mi*(mi+1))/2;
}






// template specialization for tridiagonal matrix
size_t Hasher<Tridiagonal>::hash(int i, int j, int nc, int nt){
    int del = j-i+1;
    if( del == 0 ){ return 2*nc + j - 1; } // bottom diagonal
    if( del == 1 ){ return i; } // main diagonal
    if( del == 2 ){ return nc + i; } // top diagonal
    else{ return nt; }
}

size_t Hasher<Tridiagonal>::netSize(int r, int c){
    int mi = r < c ? r : c;
    return 3*mi - 2;
}





// template specialization for tridiagonal matrix
size_t Hasher<Sparse>::hash(int i, int j, int nc, int nt){
    return 0;
}

size_t Hasher<Sparse>::netSize(int r, int c){
    return 0;
}
    
    
//}


