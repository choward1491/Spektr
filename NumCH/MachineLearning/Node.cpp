//
//  Node.cpp
//  NumCH
//
//  Created by Christian J Howard on 12/28/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "Node.hpp"

namespace ANN {
    
    Node::Node(){
        
    }
    void Node::setNetInput( double z ){
        this->z = z;
    }
    
    double Node::getNetInput() const{
        return z;
    }
    
    void Node::setNetOutput( double o ){
        this->o = o;
    }
    double Node::getNetOutput() const{
        return o;
    }
    void Node::setDerivative( double d ){
        deriv = d;
    }
    double Node::getDerivative() const{
        return deriv;
    }
    void Node::setLayer( unsigned int l){
        layer = l;
    }
    unsigned int Node::getLayer() const{
        return layer;
    }
    void Node::makeBias(){
        isBias_ = true;
        z = 1.0;
        o = 1.0;
        deriv = 0.0;
    }
    bool Node::isBias() const{
        return isBias_;
    }
    
/*
    double z;
    double o;
    double deriv;
    unsigned int layer;
    bool isBias_;
 */
}