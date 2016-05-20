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
    void setTolerance( double tol );
    
protected:
    ButcherTable btable;
    virtual double newStepSize( double dt, double error ){ return dt; }
    double tol;
private:
    int numDims;
    void computeNewStep( double * y0, double* dydt, double dt, double * out);
    void computeDerivatives( double time, double * dqdt, DiffeqList & list );
    std::vector<double*> K;
    double * tmp;
    double * err, *y1, *y2; // for adaptive stuff
    std::vector<bool>    hasComputed;
    
    
};

#endif /* ButcherIntegrator_hpp */
