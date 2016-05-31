//
//  ButcherIntegrator.cpp
//  Spektr
//
//  Created by Christian J Howard on 4/15/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include "ButcherIntegrator.hpp"
#include <math.h>
//ButcherTable btable;
//int numDims;
//std::vector<double*> K;
//std::vector<bool>    hasComputed;

void deleteVectorPointers( std::vector<double*> & vec ){
    if( vec.size() != 0 ){
        for(int i = 0; i < vec.size(); i++ ){
            if( vec[i] ){
                delete [] vec[i];
                vec[i] = 0;
            }
        }
    }
    
}

void allocVectorPointers( std::vector<double*> & vec , int num ){
    if( vec.size() != 0 ){
        for(int i = 0; i < vec.size(); i++ ){
            vec[i] = new double[num]();
        }
    }
}

void ButcherIntegrator::setTolerance( double tol ){
    
}

ButcherIntegrator::ButcherIntegrator():numDims(-1),tmp(0),y1(0),y2(0),tol(1e-5){

}

ButcherIntegrator::~ButcherIntegrator(){
    deleteVectorPointers(K);
    if( tmp ){delete [] tmp; tmp = 0;}
    if( y1 ){ delete [] y1; y1 = 0; }
    if( y2 ){ delete [] y2; y2 = 0; }
}
void ButcherIntegrator::setNumDimensions( int numDimensions ){
    numDims = numDimensions;
    deleteVectorPointers(K);
    K.resize(btable.numSteps());
    for(int i = 0; i < K.size(); i++ ){ K[i] = 0; }
    allocVectorPointers(K, numDims);
    if( tmp ){
        delete [] tmp; tmp = 0;
    }
    tmp = new double[numDims]();
    
    // allocate adaptive stuff if needed
    if( btable.isAdaptive() ){
        
        if( y1 ){ delete [] y1; y1 = 0; }
        y1 = new double[numDims]();
        
        if( y2 ){ delete [] y2; y2 = 0; }
        y2 = new double[numDims]();
    }
    
}

void ButcherIntegrator::adaptiveIntegration( double time, double dt , double* & inOutState, DiffeqList & list ){
    double finalTime = time + dt;
    double newTime = time;
    double maxErr = 0.0;
    double * tmpState = inOutState;
    bool isNotDone = true;
    inOutState = tmp;
    
    while( isNotDone ){
        maxErr = -1.0;
        newTime = time;
        
        for(int i = 0; i < numDims; i++ ){
            y1[i] = tmpState[i];
            y2[i] = tmpState[i];
        }
        
        if( btable.isExplicit() ){
            for(int i = 0; i < btable.numSteps(); i++){
                
                // set tmp = y_n
                for(int j = 0; j < numDims; j++ ){
                    tmp[j] = tmpState[j];
                }
                
                // compute Y = y_n + sum_{j} a(i,j) K_j
                for(int j = 0; j < i; j++ ){
                    if( btable.a(i,j) != 0.0 ){
                        for(int k = 0; k < numDims; k++ ){
                            tmp[k] += (dt*btable.a(i, j))*K[j][k];
                        }
                    }
                }
                
                if( i != 0 ){
                    for (int k = 0; k < list.size(); k++) {
                        list[k]->update();
                    }
                }
                
                // compute K_i = f( t + ci*dt, Y )
                computeDerivatives( time + btable.c(i)*dt, K[i], list );
            }
        }
        
        
        // Compute y_{n+1} = y_{n} + sum_{l} b(l)*K_l
        for(int i = 0; i < numDims; i++ ){
            for( int l = 0; l < btable.numSteps(); l++ ){
                if( btable.b(0, l) != 0.0 ){
                    y1[i] += (dt*btable.b(0, l)*K[l][i]);
                }
                if( btable.b(1, l) != 0.0 ){
                    y2[i] += (dt*btable.b(1, l)*K[l][i]);
                }
            }
            maxErr = fmax(fabs( (y2[i] - y1[i]) / y1[i] ),maxErr);
        }
        
        double new_dt = newStepSize(dt, maxErr );
        
        newTime += new_dt;
        if( new_dt >= dt ){
            if( time + dt >= finalTime ){
                isNotDone = false;
            }
            
            for(int i = 0; i < numDims; i++ ){
                tmpState[i] = y2[i];
            }
            if( isNotDone ){
                for (int i = 0; i < list.size(); i++) {
                    (*list[i]).update();
                }
            }
            time += dt;
        }
        
        dt = fmin(new_dt,finalTime - time);
    }
    
    // reassign correct pointer
    inOutState = tmpState;

}
void ButcherIntegrator::nominalIntegration( double time, double dt , double* & inOutState, DiffeqList & list ){
    double * tmpState = inOutState;
    inOutState = tmp;
    
    if( btable.isExplicit() ){
        for(int i = 0; i < btable.numSteps(); i++){
            
            // set tmp = y_n
            for(int j = 0; j < numDims; j++ ){
                tmp[j] = tmpState[j];
            }
            
            // compute Y = y_n + sum_{j} a(i,j) K_j
            for(int j = 0; j < i; j++ ){
                if( btable.a(i,j) != 0.0 ){
                    for(int k = 0; k < numDims; k++ ){
                        tmp[k] += (dt*btable.a(i, j))*K[j][k];
                    }
                }
            }
            
            if( i != 0 ){
                for (int k = 0; k < list.size(); k++) {
                    list[k]->update();
                }
            }
            
            // compute K_i = f( t + ci*dt, Y )
            computeDerivatives( time + btable.c(i)*dt, K[i], list );
        }
    }else{
        
    }
    
    
    // Compute y_{n+1} = y_{n} + sum_{l} b(l)*K_l
    for( int l = 0; l < btable.numSteps(); l++ ){
        if( btable.b(0, l) != 0.0 ){
            for(int i = 0; i < numDims; i++ ){
                tmpState[i] += (dt*btable.b(0, l)*K[l][i]);
            }
        }
    }
    
    // reassign correct pointer
    inOutState = tmpState;

}

void ButcherIntegrator::integrate( double time, double dt , double* & inOutState, DiffeqList & list){
    if( btable.isAdaptive() ){
        adaptiveIntegration(time, dt, inOutState, list);
    }else{
        nominalIntegration(time, dt, inOutState, list);
    }
}

void ButcherIntegrator::computeNewStep( double * y0, double* dydt, double dt, double * out){
    for (int i = 0; i < numDims; i++) {
        out[i] = y0[i] + dt*dydt[i];
    }
}

void ButcherIntegrator::computeDerivatives( double time, double * dqdt, DiffeqList & list ){
    ModelState dqdt_;
    size_t ndim, offset = 0;
    
    dqdt_.setAddress(&dqdt);
    for (int i = 0; i < list.size(); i++) {
        ndim = list[i]->numDims();
        dqdt_.setNumDims(ndim);
        dqdt_.setOffset(offset);
        (*list[i])(time, dqdt_);
        offset += ndim;
    }
}
    