//
//  NeuralNet.cpp
//  Spektr
//
//  Created by Christian J Howard on 7/24/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include "NeuralNet.hpp"
#include "NetFunc.hpp"
#include "NetLayer.hpp"


//typedef la::Mat<double> Mat;
//std::vector<NetLayer> layers;
//std::vector<Mat> weights;

// constructor/destructor stuff
NeuralNet::NeuralNet(){
    
}
NeuralNet::NeuralNet( const std::vector<int> & layers ){
    
}
NeuralNet::NeuralNet( const NeuralNet & net ){
    
}
NeuralNet::~NeuralNet(){
    
}

// set layer dimensions
void NeuralNet::setLayers( const std::vector<int> & layers ){
    
}

// operator
typename NeuralNet::Mat NeuralNet::operator()(Mat & input ){
    Mat output;
    this->operator()(input, output);
    return output;
}
void NeuralNet::operator()(Mat & input , Mat & output ){
    layers[0].getLayerInput() = input;
    layers[0].computeActivation();
    
    for( int i = 1; i < layers.size(); ++i ){
        layers[i].getLayerInput() = weights[i-1]*layers[i-1].getLayerOutput();
        layers[i].computeActivation();
    }
    
    output = layers[layers.size()-1].getLayerOutput();
}
void NeuralNet::operator()(std::vector<double> & input , std::vector<double> & output ){
    Mat & in = layers[0].getLayerInput();
    for( int i = 0; i < input.size(); ++i ){ in[i] = input[i]; }
    layers[0].computeActivation();
    
    for( int i = 1; i < layers.size(); ++i ){
        layers[i].getLayerInput() = weights[i-1]*layers[i-1].getLayerOutput();
        layers[i].computeActivation();
    }
    
    Mat & out = layers[layers.size()-1].getLayerOutput();
    if( output.size() != out.size().rows ){ output.resize(out.size().rows); }
    for( int i = 0; i < output.size(); ++i ){ output[i] = out[i]; }
}
NeuralNet & NeuralNet::operator=( const NeuralNet & net ){
    
}

// back propogation
void NeuralNet::backprop( const Mat & dEdO,Mat & gradient ){
    
}
typename NeuralNet::Mat NeuralNet::backprop( const Mat & dEdO ){
    
}

// get gradient with respect to input
void NeuralNet::grad( Mat & gradient ){
    
}




// weight stuff
size_t NeuralNet::numWeights() const{
    
}
const double & NeuralNet::weightAt(int index) const{
    
}
double & NeuralNet::weightAt(int index){
    
}
const double & NeuralNet::weightAt(int layer, int li, int ri) const {
    
}
double & NeuralNet::weightAt(int layer, int li, int ri){
    
}



// node stuff
size_t NeuralNet::numNodes( int layer ){
    return layers[layer].numNodes();
}
size_t NeuralNet::numNodes() const{
    
}
void NeuralNet::setActivationFunc( int layer, NetFunc * func){
    layers[layer].setLayerFunc(func);
}

size_t NeuralNet::numInputs() const{
    return layers[0].numNodesWithoutBias();
}
size_t NeuralNet::numOutputs() const{
    return layers[layers.size()-1].numNodesWithoutBias();
}
size_t NeuralNet::numLayers() const{
    return layers.size();
}
    
