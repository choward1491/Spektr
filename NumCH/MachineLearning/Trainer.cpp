//
//  Trainer.cpp
//  NumCH
//
//  Created by Christian J Howard on 12/29/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "Trainer.hpp"


namespace ANN {
    
    
    Trainer::Trainer():maxiter(1000){
        
    }
    
    void Trainer::setMaxIter( size_t miter ){
        maxiter = miter;
    }
    
    void Trainer::operator()( Network & net , Trainer::Type type ){
        switch (type) {
            case StochGradientDescent:
                stochasticGradientDescent(net);
                
            case PSO:
                particleSwarmOptimization(net);
                
            case UKF:
                unscentedKalmanFilter(net);
                
            case GA:
            default:
                geneticAlgorithm(net);
                break;
        }
    }
    
    void Trainer::train( Network & net, Trainer::Type type ){
        this->operator()(net, type);
    }
    
    void Trainer::stochasticGradientDescent( Network & net ){
        
    }
    
    void Trainer::geneticAlgorithm( Network & net ){
        
    }
    
    void Trainer::particleSwarmOptimization( Network & net ){
        
    }
    
    void Trainer::unscentedKalmanFilter( Network & net ){
        
    }
    
    
}