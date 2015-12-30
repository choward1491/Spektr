//
//  ANN.cpp
//  NumCH
//
//  Created by Christian J Howard on 12/28/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "ANN.hpp"


namespace ANN {
    
    Network::Network(){
        
    }
    void Network::buildNetwork( const std::vector<int> & layers ){
        layerSizes = layers;
        int tot = 0;
        int numW = 0;
        numIn = layers[0];
        numOut = layers[layers.size()-1];
        
        startIndices.push_back(0);
        
        for (int i = 0; i < layerSizes.size()-1 ; i++) {
            numW += (layerSizes[i]+1) * layerSizes[i+1];
            layerSizes[i]++;
            tot += layerSizes[i];
            startIndices.push_back(tot);
        }tot += layerSizes[layerSizes.size()-1];
        
        nbrs.resize(tot);
        nodes.resize(tot);
        funcs.resize(tot);
        w = Weights(numW);
    }
    
    Network::Network( const std::vector<int> & layers ){
        buildNetwork(layers);
    }
    
    void Network::setLayers( const std::vector<int> & layers ){
        buildNetwork(layers);
    }
    
    void Network::setWeight( double value, int leftLayer, int lnode, int rightLayer, int rnode ){
        Pair p;
        p.iFrom = startIndices[leftLayer] + lnode;
        p.iTo   = startIndices[rightLayer] + rnode;
        w(p) = value;
    }
    void Network::setWeight( double value, int index){
        w[index] = value;
    }
    void Network::randomizeWeights(){
        w.randomWeights();
    }
    
    void Network::addPair( Pair & p ){
        nbrs[p.iFrom].connectForwardNode(p.iTo);
        nbrs[p.iTo].connectBackwardNode(p.iFrom);
        w.addPair(p);
    }
    
    void Network::addPair( int leftLayer, int ln, int rightLayer, int rn ){
        Pair p;
        p.iFrom = startIndices[leftLayer] + ln;
        p.iTo   = startIndices[rightLayer] + rn;
        addPair(p);
    }
    
    void Network::setNodeFunc( unsigned int nodeID, FuncType type ){
        funcs[nodeID] = factory.getNeuron(type);
    }
    void Network::setNodeFunc( int layer, int localnode, FuncType type ){
        setNodeFunc(startIndices[layer]+localnode, type);
    }
    void Network::setLayerFunc( int layer , FuncType type ){
        for (int i = 0; i < layerSizes[layer]; i++) {
            setNodeFunc(startIndices[layer]+i, type);
        }
    }
    
    void Network::print() const{
        int iter = 0;
        for (int i = 0; i < layerSizes.size(); i++) {
            for (int in = 0; in < layerSizes[i]; in++) {
                if( nodes[iter].isBias() ){
                    printf(" [%i] ",iter);
                }else{
                    printf(" (%i) ",iter);
                }iter++;
            }printf("\n");
        }
    }

    
    std::vector<double> Network::operator()( const std::vector<double> & input ){
        if( setInput( input ) ){
            Neighbors::Iter it;
            ActivationFunc::Output out;
            w.print();
            for (int i = layerSizes[0]; i < funcs.size(); i++) {
                it = nbrs[i].beginBackward();
                if( !nodes[i].isBias() ){
                    nodes[i].setNetInput(funcs[i]->Z(i, it, nodes, w));
                    out = (*funcs[i])(nodes[i].getNetInput());
                    nodes[i].setNetOutput(out.activation);
                    nodes[i].setDerivative(out.derivative);
                }
            }
            return getOutput();
        }
        return std::vector<double>();
    }
    
    bool Network::setInput( const std::vector<double> & in){
        if( in.size() == numIn ){
            for (int i = 0; i < numIn; i++) {
                nodes[i].setNetInput(in[i]);
                nodes[i].setNetOutput(in[i]);
            }
            return true;
        }else{ return false; }
    }
    std::vector<double> Network::getOutput(){
        int N = static_cast<int>(layerSizes.size()) - 1;
        std::vector<double> output(numOut);
        
        for (int i = 0; i < numOut; i++) {
            output[i] = nodes[i + startIndices[N]].getNetOutput();
        }
        return output;
    }

    /*
    std::vector<Neighbors> nbrs;
    std::vector<Node> nodes;
    std::vector<ActivationFunc*> funcs;
    ActivationFactory factory;
    std::vector<int> layerSizes;
    Weights w;
     */
    
    
    
    
}