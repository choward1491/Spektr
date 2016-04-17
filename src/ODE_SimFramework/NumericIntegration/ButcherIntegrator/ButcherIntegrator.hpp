//
//  ButcherIntegrator.hpp
//  Spektr
//
//  Created by Christian J Howard on 4/15/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef ButcherIntegrator_hpp
#define ButcherIntegrator_hpp

#include "ButcherTable.hpp"
#include "DynamicModel.hpp"


class ButcherIntegrator {
public:
    typedef std::vector<DynamicModel*> DiffeqList;
    
    ButcherIntegrator();
    ~ButcherIntegrator();
    void setNumDimensions( int numDimensions );
    void integrate( double time, double dt , double* & inOutState, DiffeqList & list);
    
protected:
    ButcherTable btable;
    
private:
    int numDims;
    void computeNewStep( double * y0, double* dydt, double dt, double * out);
    void computeDerivatives( double time, double * dqdt, DiffeqList & list );
    std::vector<double*> K;
    double * tmp;
    std::vector<bool>    hasComputed;
    
    
};

#endif /* ButcherIntegrator_hpp */
