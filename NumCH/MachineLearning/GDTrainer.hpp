//
//  GDTrainer.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/24/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef GDTrainer_hpp
#define GDTrainer_hpp

#include <stdio.h>
#include "Trainer.hpp"

namespace ANN {
    
    template<class Cost, class Step>
    class GDTrainer : public Trainer<GDTrainer<Cost,Step>> {
    private:
        typedef std::vector<double> vec;
        
        int iter, maxiter;
        vec momentum, dw, y, dE;
        double dstep;
        double mcoef;
        
        

    public:
        GDTrainer();
        Cost cfunc;
        Step sfunc;
        void setMomentumCoef( double mcoef_ );
        void setMaxIterations( int maxiter_ );
        void setDefaultStep( double dstep );
        void init( Network & net);
        bool doneTraining();
        void updateNet( Network & net, DataSet & dset );
    };

    
}

#include "GDTrainerImpl.hpp"

#endif /* GDTrainer_hpp */
