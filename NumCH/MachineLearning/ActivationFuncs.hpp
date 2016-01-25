//
//  ActivationFuncs.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/23/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef ActivationFuncs_hpp
#define ActivationFuncs_hpp

#include <stdio.h>
#include <math.h>

namespace ANN {
    
    struct Activation {
        double o; // activation output
        double d; // derivative
    };
    
    
    Activation sigmoid( double z );
    Activation linear( double z );
    Activation bias( double z );
    
    
}

#endif /* ActivationFuncs_hpp */
