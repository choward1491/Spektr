//
//  ModelState.cpp
//  Spektr
//
//  Created by Christian J Howard on 3/15/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include "ModelState.hpp"
#include "SimExceptions.hpp"
/*
double * ref;
size_t ndim;
 */

ModelState::ModelState():ref(0),ndim(0){
    
}
ModelState::ModelState(double ** address, size_t numDims, size_t offset_ ){
    try {
        ref = address;
        ndim = numDims;
        offset = offset_;
        if( !ref ){ throw sim::exception("Invalid Model State Address"); }
        if( ndim == 0 ){ throw sim::exception("Model State of Invalid Size 0"); }
        
    } catch (std::exception & e) {
        printf("Error. Msg = '%s'\n",e.what());
    }
    
}

double & ModelState::operator[](size_t i){
    return (*ref)[offset + (i%ndim)];
}
const double & ModelState::operator[](size_t i) const{
    return (*ref)[offset + (i%ndim)];
}

void ModelState::setAddress( double ** address ){
    ref = address;
}
void ModelState::setNumDims( size_t numDims ){
    ndim = numDims;
}

void ModelState::setOffset( size_t offset_ ){
    offset = offset_;
}

    