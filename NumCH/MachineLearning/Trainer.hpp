//
//  Trainer.hpp
//  NumCH
//
//  Created by Christian J Howard on 12/29/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef Trainer_hpp
#define Trainer_hpp

#include <stdio.h>
#include "ANN.hpp"

namespace ANN {
    
    template< class CostFunc >
    class Trainer {
    public:
        enum Type { StochGradientDescent = 0, GA, PSO, UKF };
        
        Trainer();
        void operator()( Network & net , Trainer::Type type );
        void setMaxIter( size_t miter );
        void train( Network & net, Trainer::Type type );
        
    private:
        void stochasticGradientDescent( Network & net );
        void geneticAlgorithm( Network & net );
        void particleSwarmOptimization( Network & net );
        void unscentedKalmanFilter( Network & net );
        size_t maxiter;
        
    };
    
    
}



#endif /* Trainer_hpp */
