//
//  Node.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/23/16.
//
//  The MIT License (MIT)
//  Copyright © 2016 Christian Howard. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
//
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
        
        void setOutputGrad( double og );
        double getOutputGrad();
        
    protected:
        
    private:
        friend class Network;
        Activation (*a)(double z);
        Activation currentActivation;
        double backPropError;
        double outputGrad;
        
    };
    
    
}

#endif /* Node_hpp */
