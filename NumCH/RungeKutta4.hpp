//
//  RungeKutta4.hpp
//  NumCH
//
//  Created by Christian J Howard on 11/21/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef RungeKutta4_hpp
#define RungeKutta4_hpp

#include <stdio.h>
#include "GenIntegrator.hpp"
#include "Simulator.hpp"

class RungeKutta4 : public GenIntegrator {
    
public:
    RungeKutta4() : GenIntegrator() {}
    virtual ~RungeKutta4();
    virtual void setNumDimensions( int numDimensions );
    virtual void integrate( double time, double dt , double* inOutState, DiffeqList & list );
    
private:
    void clear();
    void create( int totalNumber );
    void computeNewStep( double * y0, double* dydt, double dt, double * out);
    void computeDerivatives( double time, double * & dqdt, DiffeqList & list );
    double* k1;
    double* k2;
    double* k3;
    double* k4;
    double* tmp;
    
};

#endif /* RungeKutta4_hpp */
