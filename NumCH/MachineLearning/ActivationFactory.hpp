//
//  ActivationFactory.hpp
//  NumCH
//
//  Created by Christian J Howard on 12/28/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef ActivationFactory_hpp
#define ActivationFactory_hpp

#include <stdio.h>
#include <vector>
#include "ActivationFunc.hpp"
#include "Linear.hpp"
#include "Sigmoid.hpp"


namespace ANN {


class ActivationFactory {
public:
    
    enum Type { Linear = 0, Sigmoid };
    
    
    ActivationFactory():prototypes(2){
        prototypes[0] = new class Linear();
        prototypes[1] = new class Sigmoid();
    }
    ActivationFunc* getNeuron( Type ntype ) const {
        return prototypes[ntype%2];
    }
    
    ~ActivationFactory(){
        for (int i = 0; i < prototypes.size(); i++) {
            if( prototypes[i] != 0 ){
                delete prototypes[i]; prototypes[i] = 0;
            }
        }
    }
    
    
private:
    std::vector<ActivationFunc*> prototypes;
    
};
    
    
    
}

#endif /* ActivationFactory_hpp */
