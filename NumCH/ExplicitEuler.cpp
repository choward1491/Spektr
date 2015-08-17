//
//  ExplicitEuler.cpp
//  NumCH
//
//  Created by Christian J Howard on 8/9/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "ExplicitEuler.hpp"




ExplicitEuler::ExplicitEuler( NumCH::Model** & _models, int _numModels ){
    models      = &_models;
    numModels   = _numModels;
    setModels(_models, _numModels);
    
}
ExplicitEuler::~ExplicitEuler(){
    models = 0;
    if( k1 != 0 ){
        delete [] k1;
    }
}
void ExplicitEuler::integrate( double dt ){
    for (int i = 0; i < numModels; i++) {
        (*models)[i]->equationsOfMotion( k1[i] );
        
        for (int j = 0; j < k1[i].size(); j++) {
            (*(*models)[i])[j] = (*(*models)[i])[j] + dt * k1[i][j];
        }
    }
    
}
void ExplicitEuler::setModels( NumCH::Model** & _models, int _numModels ){
    k1 = new Vec[_numModels];
    for (int i = 0; i < _numModels; i++) {
        k1[i] = Vec((_models[i])->numDims());
    }
}
    