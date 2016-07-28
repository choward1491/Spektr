//
//  NetFunctions.cpp
//  Spektr
//
//  Created by Christian J Howard on 7/24/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include "NetFunctions.hpp"
#include <math.h>

namespace NetFunctions {
    
    
    Activation bias::operator()(double z) const{
        return Activation(1.0,0.0);
    }
    std::string bias::name() const{
        return "bias";
    }



    Activation linear::operator()(double z) const{
        return Activation(z,1.0);
    }
    std::string linear::name() const{
        return "linear";
    }


    Activation sigmoid::operator()(double z) const{
        Activation a;
        a.output = 1.0 / ( 1.0 + exp(-z) );
        a.deriv = a.output*(1.0-a.output);
        return a;
    }
    std::string sigmoid::name() const{
        return "sigmoid";
    }


    Activation leakyLU::operator()(double z) const{
        if( z > 0.0 ){
            return Activation(z, 1.0);
        }else{
            return Activation(0.1*z, 0.1);
        }
    }
    std::string leakyLU::name() const{
        return "leakyLU";
    }
    
    
}