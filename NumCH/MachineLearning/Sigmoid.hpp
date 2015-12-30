//
//  Sigmoid.hpp
//  NumCH
//
//  Created by Christian J Howard on 12/28/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef Sigmoid_hpp
#define Sigmoid_hpp

#include "ActivationFunc.hpp"

namespace ANN {
    
    class Sigmoid : public ActivationFunc {
    public:
        Sigmoid(){}
        virtual Output operator()(double input){
            double phi = 1.0 / ( 1 + exp(-input) );
            return Output{phi,phi*(1-phi)};
        }
        virtual ~Sigmoid(){}
    };
    
    
}

#endif /* Sigmoid_hpp */
