//
//  GDTrainerImpl.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/24/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include "GDTrainer.hpp"

#ifndef GDTrainer_impl_hpp_
#define GDTrainer_impl_hpp_

namespace ANN {
    
    
    template<class Cost, class Step>
    void GDTrainer<Cost,Step>::init( Network & net ){
        
        if( momentum.size() != net.numWeights() ){
            momentum.resize(net.numWeights());
        }
        
        if( dw.size() != net.numWeights() ){
            dw.resize(net.numWeights());
        }
        
        if( y.size() != net.numOutputs() ){
            y.resize(net.numOutputs());
        }
        
        if( dE.size() != net.numOutputs()){
            dE.resize(net.numOutputs());
        }
        
        sfunc.setNetwork(&net);
        sfunc.setGradient(&dw);
        sfunc.setOutputVec(&y);
        
        iter = 0;
    }
    
    template<class Cost, class Step>
    bool GDTrainer<Cost,Step>::doneTraining(){
        return iter >= maxiter;
    }
    
    template<class Cost, class Step>
    void GDTrainer<Cost,Step>::updateNet( Network & net, DataSet & dset ){
        double cost = 0, step = dstep;
        iter++;
        
        for (int i = 0; i < dset.in.size(); i++) {
            net(dset.in[i],y);
            cost = cfunc(dset.out[i],y,dE);
            net.backprop(dE, dw);
        }
        cfunc.regularization(net.w(), dw);
        step = sfunc(step, dset);
        
        for (int i = 0; i < dw.size(); i++) {
            dw[i] *= step;
            net.weightAt(i) -= (dw[i] + mcoef*momentum[i]);
            momentum[i] = dw[i]; dw[i] = 0.0;
        }
        
    }
    
    template<class Cost, class Step>
    GDTrainer<Cost,Step>::GDTrainer(){
        dstep = 1e-3;
    }
    
    template<class Cost, class Step>
    void GDTrainer<Cost,Step>::setMomentumCoef( double mcoef_ ){
        mcoef = mcoef_;
    }
    
    template<class Cost, class Step>
    void GDTrainer<Cost,Step>::setMaxIterations( int maxiter_ ){
        maxiter = maxiter_;
    }
    
    template<class Cost, class Step>
    void GDTrainer<Cost,Step>::setDefaultStep( double ds ){
        dstep = ds;
    }


}

#endif