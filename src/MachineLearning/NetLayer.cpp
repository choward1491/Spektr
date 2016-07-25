//
//  NetLayer.cpp
//  Spektr
//
//  Created by Christian J Howard on 7/24/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include "NetLayer.hpp"
#include "NetFunc.hpp"


//typedef la::Mat<double> Mat;
//Mat out, in, err;
//std::vector<NetFunc*> node_funcs;
NetLayer::NetLayer( int num_nodes_):num_nodes(num_nodes_),
                                    inputs(num_nodes-1,1,0.0),
                                    derivs(num_nodes-1,1,0.0),
                                    outputs(num_nodes,1,0.0),
                                    err(num_nodes-1,1,0.0)
{
    // need something here to initialize node functions
}
NetLayer::~NetLayer(){
    
}

int NetLayer::numNodes() const{
    return num_nodes;
}
int NetLayer::numNodesWithoutBias() const{
    return num_nodes-1;
}

NetLayer::Mat & NetLayer::getLayerInput(){
    return inputs;
}
NetLayer::Mat & NetLayer::getLayerOutput(){
    return outputs;
}
NetLayer::Mat & NetLayer::getLayerBackPropError(){
    return err;
}

NetLayer::Mat & NetLayer::getLayerDerivatives(){
    return derivs;
}

void NetLayer::computeActivation(){
    Activation a;
    for(int i = 0; i < num_nodes-1; ++i ){
        a = (*node_funcs[i])(inputs[i]);
        outputs[i] = a.output;
        derivs[i]  = a.deriv;
    }
    outputs[num_nodes-1] = 1.0;
}

void NetLayer::setFuncAt( int index, NetFunc * func ){
    if( index >= 0 && index < static_cast<int>(node_funcs.size()) ){
        node_funcs[index] = func;
    }
}
void NetLayer::setLayerFunc( NetFunc * func){
    for(int i = 0; i < static_cast<int>(node_funcs.size()-1); ++i ){
        node_funcs[i] = func;
    }
    
}
    


