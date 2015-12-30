//
//  Linear.hpp
//  NumCH
//
//  Created by Christian J Howard on 12/28/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef Linear_hpp
#define Linear_hpp

#include "ActivationFunc.hpp"

namespace ANN {

class Linear : public ActivationFunc {
public:
    
    Linear(){}
    virtual Output operator()(double input){
        return Output{input,1.0};
    }
    virtual ~Linear(){}
    
};
    
    
}

#endif /* Linear_hpp */
