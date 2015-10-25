//
//  GenIntegrator.hpp
//  NumCH
//
//  Created by Christian J Howard on 8/8/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef GenIntegrator_cpp
#define GenIntegrator_cpp

//#include <stdio.h>
#include "Model.hpp"




class GenIntegrator {
    
public:
    
    
    virtual ~GenIntegrator();
    virtual void integrate( double dt ) = 0;
    
protected:
    
    int numModels;
    Model*** models;
    virtual void setModels( Model** & _models, int _numModels ) = 0;
    
    
};




#endif /* GenIntegrator_cpp */
