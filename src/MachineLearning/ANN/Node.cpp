//
//  Node.cpp
//  NumCH
//
//  Created by Christian J Howard on 1/23/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include "Node.hpp"

namespace ANN {
    
    Node::Node(){
        setActivationFunc(leakyReLU);
    }
    
    Node::Node( Activation (*func)(double z) ){
        setActivationFunc(func);
    }
    void Node::setActivationFunc( Activation (*func)(double z) ){
        a = func;
    }
    void Node::operator()( double z ){
        currentActivation = a(z);
    }
    double Node::getDerivative() const{
        return currentActivation.d;
    }
    double Node::getActivation() const{
        return currentActivation.o;
    }
    
    void Node::computeBackPropErr( double dEdo ){
        backPropError = dEdo * currentActivation.d;
    }
    double Node::getBackPropErr() const{
        return backPropError;
    }
    
    void Node::setOutputGrad( double og ){
        outputGrad = og;
    }
    double Node::getOutputGrad(){
        return outputGrad;
    }
    
    
}