//
//  ExplicitTrapezoidal.hpp
//  NumCH
//
//  Created by Christian J Howard on 11/22/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef ExplicitTrapezoidal_hpp
#define ExplicitTrapezoidal_hpp

#include "GenIntegrator.hpp"
#include "Simulator.hpp"

class ExplicitTrapezoidal : public GenIntegrator {
    
public:
    ExplicitTrapezoidal() : GenIntegrator() {}
    virtual ~ExplicitTrapezoidal();
    virtual void setNumDimensions( int numDimensions );
    virtual void integrate( double time, double dt , double* inOutState, DiffeqList & list );
    
private:
    void clear();
    void create( int totalNumber );
    void computeNewStep( double * y0, double* dydt, double dt, double * out);
    void computeDerivatives( double time, double * & dqdt, DiffeqList & list );
    double* k1;
    double* k2;
    double* tmp;
    
};

#endif /* ExplicitTrapezoidal_hpp */
