//
//  MatHashes.cpp
//  NumCH
//
//  Created by Christian J Howard on 1/30/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include "MatHashes.hpp"

// template specialization for diagonal matrix
template<>
size_t Hasher<MatType::Diagonal>::hash(int i, int j, int nc, int nt){
    if( i == j ){ return i; }
    else{ return nt; }
}
template<>
size_t Hasher<MatType::Diagonal>::netSize(int r, int c){
    return r < c ? r : c;
}




// template specialization for symmetric matrix
template<>
size_t Hasher<MatType::Symmetric>::hash(int i, int j, int nc, int nt){
    if( i < j ){ return (j*(j+1))/2 + i; }
    else{ return (i*(i+1))/2 + j; }
}
template<>
size_t Hasher<MatType::Symmetric>::netSize(int r, int c){
    int mi = r < c ? r : c;
    return (mi*(mi+1))/2;
}





// template specialization for lower matrix
template<>
size_t Hasher<MatType::Lower>::hash(int i, int j, int nc, int nt){
    if( i < j ){ return nt; }
    else{ return (i*(i+1))/2 + j; }
}
template<>
size_t Hasher<MatType::Lower>::netSize(int r, int c){
    int mi = r < c ? r : c;
    return (mi*(mi+1))/2;
}




// template specialization for Upper matrix
template<>
size_t Hasher<MatType::Upper>::hash(int i, int j, int nc, int nt){
    if( i > j ){ return nt; }
    else{ return (j*(j+1))/2 + i; }
}
template<>
size_t Hasher<MatType::Upper>::netSize(int r, int c){
    int mi = r < c ? r : c;
    return (mi*(mi+1))/2;
}






// template specialization for tridiagonal matrix
template<>
size_t Hasher<MatType::Tridiagonal>::hash(int i, int j, int nc, int nt){
    int del = j-i+1;
    if( del == 0 ){ return 2*nc + j - 1; } // bottom diagonal
    if( del == 1 ){ return i; } // main diagonal
    if( del == 2 ){ return nc + i; } // top diagonal
    else{ return nt; }
}
template<>
size_t Hasher<MatType::Tridiagonal>::netSize(int r, int c){
    int mi = r < c ? r : c;
    return 3*mi - 2;
}





// template specialization for tridiagonal matrix
template<>
size_t Hasher<MatType::Sparse>::hash(int i, int j, int nc, int nt){
    return 0;
}
template<>
size_t Hasher<MatType::Sparse>::netSize(int r, int c){
    return 0;
}


