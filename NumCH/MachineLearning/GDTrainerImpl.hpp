//
//  GDTrainerImpl.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/24/16.
//
//  The MIT License (MIT)
//  Copyright © 2016 Christian Howard. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
//
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