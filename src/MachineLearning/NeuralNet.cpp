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
#include "NeuralPrototypes.hpp"


//typedef la::Mat<double> Mat;
//std::vector<NetLayer> layers;
//std::vector<Mat> weights;

// constructor/destructor stuff
NeuralNet::NeuralNet(){
    
}
NeuralNet::NeuralNet( const std::vector<int> & layers ){
    setLayers(layers);
}
NeuralNet::NeuralNet( const NeuralNet & net ){
    
}
NeuralNet::~NeuralNet(){
    
}

// set layer dimensions
void NeuralNet::setLayers( const std::vector<int> & layers_cnt ){
    
    if( layers_cnt.size() != layers.size() ){
        layers.resize(layers_cnt.size());
        weights.resize(layers_cnt.size()-1);
        weight_count.resize(layers_cnt.size(),0);
    }
    
    total_nodes = total_weights = 0;
    layers[0] = NetLayer(layers_cnt[0]+1);
    total_nodes = layers_cnt[0];
    weight_count[0] = 0;
    
    for(int i = 1; i < layers_cnt.size(); i++ ){
        layers[i] = NetLayer(layers_cnt[i]+1);
        total_nodes += layers_cnt[i]+1;
        weights[i-1].resize(layers_cnt[i],layers_cnt[i-1]+1);
        total_weights += layers_cnt[i]*(layers_cnt[i-1]+1);
        weight_count[i] = total_weights;
    }
    
    layers[layers.size()-1].setLayerFunc( NeuralPrototypes::prototypes.getFunction( NeuralPrototypes::Linear ) );
    
    
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
    
    const Mat & o = layers[layers.size()-1].getLayerOutput();
    if( output.size() != o.size() ){ output.resize( o.size().rows-1, 1 ); }
    for( int i = 0; i < o.size().rows-1; ++i ){
        output[i] = o[i];
    }
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
    if( this != &net ){
        
    }
    
    return *this;
}

// back propogation

void NeuralNet::computeOuterLayerErrors( NetLayer & ol, const Mat & dEdO ) {
    int num_inputs = ol.numNodesWithoutBias();
    Mat & derivs = ol.getLayerDerivatives();
    Mat & errors = ol.getLayerBackPropError();
    
    for( int i = 0; i < num_inputs; ++i ){
        errors[i] = dEdO[i]*derivs[i];
    }
}
void NeuralNet::computeInnerLayerErrors( NetLayer & il, NetLayer & next_layer, const Mat & w ) {
    int num_inputs = il.numNodesWithoutBias();
    Mat & derivs = il.getLayerDerivatives();
    Mat & errors = il.getLayerBackPropError();
    Mat & next_errs = next_layer.getLayerBackPropError();
    
    for( int i = 0; i < num_inputs; ++i ){
        errors[i] = 0.0;
        for (int m = 0; m < next_errs.size().rows; ++m) {
            errors[i] += next_errs[m]*w(m,i);
        }
        errors[i] *= derivs[i];
    }
}

void NeuralNet::computeLayerWeightGradient( int layer, Mat & grad ) {
    Mat & errors = layers[layer+1].getLayerBackPropError();
    Mat & out    = layers[layer].getLayerOutput();
    Dims dims    = weights[layer].size();
    int start_dx = weight_count[layer];
    int k = 0;
    
    for( int i = 0; i < dims.rows; ++i ){
        for( int j = 0; j < dims.cols; ++j ){
            grad[start_dx+k] += errors[i]*out[j];
            ++k;
        }
    }
    
}

void NeuralNet::backprop( const Mat & dEdO,Mat & gradient ){
    // create backprop error based on outer layer
    int lastlayer = static_cast<int>(layers.size()-1);
    computeOuterLayerErrors(layers[lastlayer], dEdO);
    
    // propogate error and compute gradient of weights
    int num_weight_maps = static_cast<int>(weights.size()-1);
    for(int i = num_weight_maps; i > 0; --i ){
        computeInnerLayerErrors(layers[i], layers[i+1], weights[i]);
        computeLayerWeightGradient(i, gradient);
    }
    
    // compute final gradient portion for first weight map
    computeLayerWeightGradient(0, gradient);
    
}
typename NeuralNet::Mat NeuralNet::backprop( const Mat & dEdO ){
    Mat grad((int)this->numWeights(),1,0);
    this->backprop(dEdO, grad);
    return grad;
}

// get gradient with respect to input
void NeuralNet::grad( Mat & gradient ){
    
}


int NeuralNet::binarySearchWeightIdx( int index, int & mat_idx ) const {
    if( index < 0 ){ mat_idx = 0; return 0; }
    if( index < weight_count[weight_count.size()-1] ){
        
        int cidx = static_cast<int>(weight_count.size()/2);
        int li = 0, ri = static_cast<int>(weight_count.size()-1);
        
        while( (cidx-li)>1 && (ri-cidx)>1 ){
            if( weight_count[cidx] > index ){
                ri = cidx;
                cidx = ( cidx + li )/2;
            }else {
                li = cidx;
                cidx = (cidx + ri)/2;
            }
        }
        
        if( weight_count[cidx] > index ){ mat_idx = li; }
        if( weight_count[cidx] <= index ){ mat_idx = cidx; }
        return index - weight_count[mat_idx];
        
    }else{
        mat_idx = static_cast<int>(weights.size()-1);
        return weight_count[mat_idx+1] - weight_count[mat_idx] - 1;
    }
}



// weight stuff
size_t NeuralNet::numWeights() const{
    return static_cast<size_t>(total_weights);
}
const double & NeuralNet::weightAt(int index) const{
    int mat_idx = 0;
    int del_idx = binarySearchWeightIdx(index, mat_idx);
    return weights[mat_idx](del_idx);
}
double & NeuralNet::weightAt(int index){
    int mat_idx = 0;
    int del_idx = binarySearchWeightIdx(index, mat_idx);
    return weights[mat_idx](del_idx);
}
const double & NeuralNet::weightAt(int layer, int li, int ri) const {
    return weights[layer](ri,li);
}
double & NeuralNet::weightAt(int layer, int li, int ri){
    return weights[layer](ri,li);
}

void NeuralNet::printWeights() const {
    for(int i = 0; i < weights.size(); ++i ){
        printf("Weight Matrix #%i\n",i+1);
        weights[i].print();
    }
}



// node stuff
size_t NeuralNet::numNodes( int layer ){
    return layers[layer].numNodes();
}
size_t NeuralNet::numNodes() const{
    return static_cast<size_t>(total_nodes);
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
    
