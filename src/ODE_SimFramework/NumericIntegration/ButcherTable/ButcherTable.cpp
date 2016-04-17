//
//  ButcherTable.cpp
//  Spektr
//
//  Created by Christian J Howard on 4/15/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include "ButcherTable.hpp"

/*
 int dim;
 bool is_explicit;
 std::vector<double> c_;
 std::vector<double> a_;
 std::vector<double> b_;
 */

ButcherTable::ButcherTable(){
    
}
ButcherTable::ButcherTable( int size, int num_compute ){
    resize(size,num_compute);
}

void ButcherTable::resize( int size, int num_compute ){
    dim = size;
    num_estimates = num_compute;
    c_.resize(size);
    a_.resize(size*size);
    b_.resize(num_compute*size);
}

int ButcherTable::numSteps() const {
    return dim;
}
int ButcherTable::numEstimates() const {
    return num_estimates;
}

double & ButcherTable::c(int i){
    return c_[i];
}
double & ButcherTable::b(int row, int column){
    return b_[column + row*dim];
}
double & ButcherTable::a(int row, int column){
    return a_[column + row*dim];
}
const double & ButcherTable::c(int i) const{
    return c_[i];
}
const double & ButcherTable::b(int row, int column) const{
    return b_[column + row*dim];
}
const double & ButcherTable::a(int row, int column) const{
    return a_[column + row*dim];
}

bool ButcherTable::isImplicit() const{
    for(int i = 0; i < dim; i++ ){
        for(int j = i; j < dim; j++){
            if( a(i,j) != 0.0 ){
                return true;
            }
        }
    }
    return false;
}
bool ButcherTable::isExplicit() const{
    return !isImplicit();
}


