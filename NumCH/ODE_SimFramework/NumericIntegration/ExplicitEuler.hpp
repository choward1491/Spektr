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



class ExplicitEuler : public GenIntegrator {
    
public:
    ExplicitEuler() : GenIntegrator() {}
    virtual ~ExplicitEuler();
    virtual void setNumDimensions( int numDimensions );
    virtual void integrate( double time, double dt , double* inOutState, DiffeqList & list );

private:
    void clear();
    void create( int totalNumber );
    double* tmp;
    
};

#endif /* ExplicitEuler_cpp */
