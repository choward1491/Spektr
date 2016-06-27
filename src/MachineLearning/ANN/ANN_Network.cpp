//
//  ANN_Network_v2.cpp
//  Spektr
//
//  Created by Christian J Howard on 6/24/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include "ANN_Network.hpp"
#include "DefaultMaps.hpp"

namespace ANN {
    
    Network::Network(){
        inputMap  = nullMap;
        outputMap = nullMap;
    }
    Network::Network( const std::vector<int> & layers ){
        setLayers(layers);
        inputMap  = nullMap;
        outputMap = nullMap;
    }
    Network::Network( const Network & net ){
        copy(net);
        
    }
    Network::~Network(){
        
    }
    
    
    
    size_t Network::numInputs() const{
        return layers[0]-1;
    }
    size_t Network::numOutputs() const{
        return layers[layers.size()-1]-1;
    }
    size_t Network::numLayers() const {
        return layers.size();
    }
    
    
    void Network::setLayers( const std::vector<int> & l ){
        layers = l;
        num_layers = layers.size();
        layerSums.resize(layers.size());
        wsums.resize(layers.size());
        weights.resize(l.size()-1);
        layer_outputs.resize(layers.size());
        layer_inputs.resize(layers.size());
        
        
        layer_inputs[0].resize(layers[0], 1);
        layers[0]++;
        layer_outputs[0].resize(layers[0], 1);
        layerSums[0] = 0;
        wsums[0] = 0;
        int totWeights = 0;
        int totNodes = layers[0];
        for (int i = 1; i < layers.size(); i++) {
            totWeights += layers[i-1]*layers[i];
            weights[i-1].resize(layers[i],layers[i-1]);
            wsums[i] = totWeights;
            layer_inputs[i].resize(layers[i], 1);
            layers[i]++;
            layer_outputs[i].resize(layers[i], 1);
            totNodes += layers[i];
            layerSums[i] = layerSums[i-1] + layers[i-1];
        }
        
        nodes.resize(totNodes);
        for (int i = 0, ind = 0; i < layers.size()-1; i++) {
            ind = layerSums[i]+layers[i]-1;
            nodes[ind].setActivationFunc(bias);
            nodes[ind].currentActivation.o = 1.0;
            nodes[ind].currentActivation.d = 0.0;
        }
        
        setActivationFunc(static_cast<int>(layers.size()-1), linear);
    }
    
    void Network::setInputMap( void (*im)( la::Mat<double> & in ) ){
        inputMap=im;
    }
    void Network::setOutputMap( void (*om)( la::Mat<double> & out ) ){
        outputMap=om;
    }
    
    void Network::print() const{
        for( int i = 0; i < weights.size(); i++ ){
            printf("Mapping #%i:\n",i+1);
            weights[i].print();
        }
    }
    
    
    void Network::operator()( la::Mat<double> & in , la::Mat<double> & output_ ){
        
        // get the properly transformed input
        for (int i = 0; i < layers[0]-1 ; i++) {
            layer_outputs[0][i] = in[i];
        }
        layer_outputs[0][layers[0]-1] = 1.0;
        inputMap(layer_outputs[0]);
        
        // embed input into input layer nodes
        for( int i = 0; i < layers[0]-1; i++ ){
            nodes[i].currentActivation.o = layer_outputs[0][i];
        }
        
        // loop through layer and do appropriate chain of mappings
        for (int i = 1; i < layers.size(); i++) {
            layer_inputs[i] = weights[i-1]*layer_outputs[i-1];
            for (int k = 0, nc = layerSums[i]; k < layers[i]; k++) {
                if( k < layers[i]-1 ){
                    nodes[nc+k](layer_inputs[i][k]);
                }
                layer_outputs[i][k] = nodes[nc+k].getActivation();
            }
        }
        
        // get the output vector based on output layer activation values
        for (int i = 0, n = layerSums[layers.size()-1]; i < layers[layers.size()-1]-1; i++) {
            output_[i] = nodes[n+i].getActivation();
        }
        
        // transform output appropriately
        outputMap(output_);
    }
    
    Network & Network::operator=( const Network & net ){
        if( this != &net ){
            clear();
            copy(net);
        }
        return *this;
    }
    
    // get input gradient
    void Network::grad( la::Mat<double> & gradient ){
        
        // resize gradient vector if necessary
        if( gradient.size().rows != numInputs() ){
            gradient.resize(numInputs(),1);
        }
        
        // get number of layers
        size_t N = layers.size();
        
        // set output layer to using an output gradient of 1
        for (int i = 0, start = layerSums[N-1]; i < layers[N-1]-1; i++) {
            nodes[start+i].setOutputGrad(1.0);
        }
        
        // init loop variables
        Connection c;
        Node * n;
        double sum = 0, del;
        int start =static_cast<int>(N-2);
        c.layer = start;
        
        // loop through layers starting at layer layers
        // and moving backward and execute the following
        // algorithm:
        //
        // First Non-Output Layer:
        // dydo(N-1,j) = dydo(N,i)*dodz(N,i)*w(N-1,i,j)
        //
        // Other Layers:
        // dydo(N,j)   = sum_{k} [dydo(N+1,k)*dodz(N+1,k)*w(N,k,j)]
        //
        
        // do first non-output layer computation
        for (int j = 0, nj=layerSums[start]; j < layers[start]; j++) {
            c.li = j;
            sum = 0.0;
            n = &nodes[nj+j];
            int l = 0, nl = layerSums[start+1];
            c.ri = l;
            del = nodes[nl+l].getOutputGrad();
            double d = nodes[nl+l].getDerivative();
            double w = weightAt(c.layer, c.li, c.ri);
            sum = del*w*d;
            n->setOutputGrad(sum);
        }
        
        
        // loop through remaining layers doing
        // recursive relationship
        for (int i = start-1; i >= 0 ; i--) {
            c.layer = i;
            for (int j = 0, nj=layerSums[i]; j < layers[i]; j++) {
                c.li = j;
                sum = 0.0;
                n = &nodes[nj+j];
                for (int l = 0, nl = layerSums[i+1]; l < layers[i+1]-1; l++) {
                    c.ri = l;
                    del = nodes[nl+l].getOutputGrad();
                    sum += del*weightAt(c.layer, c.li, c.ri)*nodes[nl+l].getDerivative();
                }
                n->setOutputGrad(sum);
            }
        }
        
        // output dydx where x is each input variable
        for( int i = 0; i < numInputs(); i++ ){
            gradient[i] = nodes[i].getOutputGrad();
        }
    }
    
    void Network::backprop( const la::Mat<double> & dEdO, la::Mat<double> & gradient ){
        size_t N = layers.size(); // get number of layers
        
        // initialize output layer backprop error
        for (int i = 0, start = layerSums[N-1]; i < layers[N-1]-1; i++) {
            nodes[start+i].computeBackPropErr(dEdO[i]);
        }
        
        // do recursive backprop error (in an iterative fashion)
        // and compute resulting gradient
        double sum = 0, del;
        Connection c;
        Node * n;
        for (int i = static_cast<int>(N-2); i >= 0 ; i--) {
            c.layer = i;
            for (int j = 0, nj=layerSums[i]; j < layers[i]; j++) {
                c.li = j;
                sum = 0.0;
                n = &nodes[nj+j];
                for (int l = 0, nl = layerSums[i+1]; l < layers[i+1]-1; l++) {
                    c.ri = l;
                    del = nodes[nl+l].getBackPropErr();
                    sum += del*weightAt(i, j, l);
                    gradient[hashfunc(c)] += del * n->getActivation();
                }
                n->computeBackPropErr(sum);
            }
        }
        
        
    }
    la::Mat<double> Network::backprop( const la::Mat<double> & dEdO ){
        static la::Mat<double> grad(this->numWeights(),1,0);
        backprop(dEdO,grad);
        return grad;
    }
    
    size_t Network::numWeights() const{
        return wsums[wsums.size()-1];
    }
    
    const double & Network::weightAt(int index) const{
        int net = 0, layer = 0;
        for( int i = 0; i < wsums.size(); i++ ){
            if( index < wsums[i] ){
                layer = i-1;
                net = index - wsums[layer];
                break;
            }
        }
        return weights[layer](net);
    }
    double & Network::weightAt(int index){
        int net = 0, layer = 0;
        for( int i = 0; i < wsums.size(); i++ ){
            if( index < wsums[i] ){
                layer = i-1;
                net = index - wsums[layer];
                break;
            }
        }
        return weights[layer](net);
    }
    
    const double & Network::weightAt(int layer, int li, int ri) const{
        return weights[layer](ri, li);
    }
    double & Network::weightAt(int layer, int li, int ri){
        return weights[layer](ri, li);
    }
    
    size_t Network::hashfunc( const Connection & c ) const{
        return wsums[c.layer] + c.li + c.ri*layers[c.layer];
    }
    void Network::clear(){
        
    }
    void Network::copy( const Network & net ){
        setLayers(net.layers);
        weights = net.weights;
    }
    
    
    size_t Network::numNodes( int layer ){
        return layers[layer];
    }
    size_t Network::numNodes() const{
        size_t N = layerSums.size()-1;
        return layerSums[N] + layers[N] - 1;
    }
    void Network::setActivationFunc( int layer , Activation (*f)(double z)){
        size_t start = layerSums[layer];
        size_t end = layers[layer]-1;
        for (int i = 0; i < end; i++) {
            nodes[start+i].setActivationFunc(f);
        }
    }
    Node & Network::getNode(int layer, int n){
        return nodes[layerSums[layer]+n];
    }
    
    Node & Network::getNode(int n){
        return nodes[n];
    }
    
    
}