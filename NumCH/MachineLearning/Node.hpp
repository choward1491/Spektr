//
//  Node.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/23/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include <stdio.h>
#include "ActivationFuncs.hpp"

namespace ANN {
    
    class Network;
    
    class Node {
    public:
        
        Node();
        Node( Activation (*func)(double z) );
        void setActivationFunc( Activation (*func)(double z) );
        void operator()( double z );
        double getDerivative() const;
        double getActivation() const;
        
        void computeBackPropErr( double dEdo );
        double getBackPropErr() const;
        
    protected:
        
    private:
        friend class Network;
        Activation (*a)(double z);
        Activation currentActivation;
        double backPropError;
        
    };
    
    
}

#endif /* Node_hpp */
