//
//  Network.cpp
//  NumCH
//
//  Created by Christian J Howard on 1/21/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include "Network.hpp"
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
        layerSums.resize(layers.size());
        
        input.resize(layers[0]);
        layers[0]++;
        layerSums[0] = 0;
        int totWeights = 0;
        int totNodes = layers[0];
        for (int i = 1; i < layers.size(); i++) {
            totWeights += layers[i-1]*layers[i];
            layers[i]++;
            totNodes += layers[i];
            layerSums[i] = layerSums[i-1] + layers[i-1];
        }
        output.resize(layers[layers.size()-1]-1);
        
        nodes.resize(totNodes);
        for (int i = 0, ind = 0; i < layers.size()-1; i++) {
            ind = layerSums[i]+layers[i]-1;
            nodes[ind].setActivationFunc(bias);
            nodes[ind].currentActivation.o = 1.0;
            nodes[ind].currentActivation.d = 0.0;
        }
        
        setActivationFunc(static_cast<int>(layers.size()-1), linear);
        
        weights.resize(totWeights);
    }
    
    void Network::setInputMap( void (*im)( std::vector<double> & in ) ){
        inputMap=im;
    }
    void Network::setOutputMap( void (*om)( std::vector<double> & out ) ){
        outputMap=om;
    }
    
    
    void Network::operator()(std::vector<double> & in , std::vector<double> & output_ ){
        
        for (int i = 0; i < layers[0]-1 ; i++) {
            input[i] = in[i];
        }
        inputMap(input);
        
        for (int i = 0; i < layers[0]-1 ; i++) {
            nodes[i].currentActivation.o = input[i];
        }
        
        double sum;
        for (int i = 1; i < layers.size(); i++) {
            for (int k = 0, nc = layerSums[i]; k < layers[i]-1; k++) {
                sum = 0.0;
                for (int j = 0, no = layerSums[i-1] ; j < layers[i-1]; j++) {
                    sum += nodes[no+j].getActivation()*weightAt(i-1, j, k);
                }
                nodes[nc+k](sum);
            }
        }
        
        for (int i = 0, n = layerSums[layers.size()-1]; i < layers[layers.size()-1]-1; i++) {
            output_[i] = nodes[n].getActivation();
        }
        outputMap(output);
    }
    
    std::vector<double> Network::operator()(std::vector<double> & input ){
        this->operator()(input, output);
        return output;
    }
    Network & Network::operator=( const Network & net ){
        if( this != &net ){
            clear();
            copy(net);
        }
        return *this;
    }
    
    void Network::backprop( const std::vector<double> & dEdO, std::vector<double> & gradient ){
        size_t N = layers.size();
        for (int i = 0, start = layerSums[N-1]; i < layers[N-1]-1; i++) {
            nodes[start+i].computeBackPropErr(dEdO[i]);
        }
        
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
    std::vector<double> Network::backprop( const std::vector<double> & dEdO ){
        static std::vector<double> grad(this->numWeights());
        backprop(dEdO,grad);
        return grad;
    }
    
    size_t Network::numWeights() const{
        return weights.size();
    }
    const std::vector<double> & Network::w() const{
        return weights;
    }
    std::vector<double> & Network::w(){
        return weights;
    }
    const double & Network::weightAt(int index) const{
        return weights[index];
    }
    double & Network::weightAt(int index){
        return weights[index];
    }
    
    const double & Network::weightAt(int layer, int li, int ri) const{
        Connection c {layer, li, ri};
        return weights[hashfunc(c)];
    }
    double & Network::weightAt(int layer, int li, int ri){
        Connection c {layer, li, ri};
        return weights[hashfunc(c)];
    }
    
    
    //std::vector<double> weights
    //std::vector<int> layers;
    //std::vector<int> layerSums;
    
    /*
    struct Connection {
        int layer;
        int li;
        int ri;
    };*/
    
    size_t Network::hashfunc( const Connection & c ) const{
        return layerSums[c.layer] + c.li + c.ri*layers[c.layer];
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