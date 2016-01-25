//
//  ActivationFuncs.cpp
//  NumCH
//
//  Created by Christian J Howard on 1/23/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include "ActivationFuncs.hpp"

namespace ANN {
    Activation sigmoid( double z ){
        Activation a;
        a.o = 1.0 / ( 1.0 + exp(-z) );
        a.d = a.o*(1.0-a.o);
        return a;
    }
    
    Activation linear( double z ){
        Activation a;
        a.o = z;
        a.d = 1.0;
        return a;
    }
    
    Activation bias( double z ){
        Activation a;
        a.o = 1.0;
        a.d = 0.0;
        return a;
    }
    
}