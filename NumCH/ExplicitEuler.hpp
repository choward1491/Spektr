//
//  ExplicitEuler.hpp
//  NumCH
//
//  Created by Christian J Howard on 8/9/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef ExplicitEuler_cpp
#define ExplicitEuler_cpp

#include "GenIntegrator.hpp"



class ExplicitEuler : public NumCH::GenIntegrator {
    
public:
    ExplicitEuler( NumCH::Model** & _models, int _numModels );
    virtual ~ExplicitEuler();
    virtual void integrate( double dt );
    
protected:
    virtual void setModels( NumCH::Model** & _models, int _numModels );
    
private:
    Vec * k1;
    
};

#endif /* ExplicitEuler_cpp */
