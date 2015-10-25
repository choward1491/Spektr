//
//  NeuralNetwork.cpp
//  Data_Structs
//
//  Created by Christian J Howard on 9/16/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#include "NeuralNetwork.h"


#ifndef _ann_cpp_
#define _ann_cpp_


/*!
 * Null constructor for neural network
 *
 * Intialize weights and activation functions
 * and compute any values associated with efficiently
 * processing the ANN
 *
 */
template<int I, int O, int Nh, int Nn>
NeuralNetwork<I,O,Nh,Nn>::NeuralNetwork(){
    
    // allocate the weights
    weights = new Weights;
    
    
    // allocate the activation funcs
    funcs = new ActivationFuncs*[Nh+1];
    
    
    // assign num inputs to first nodes per layer element
    nodesPerLayer[0] = I;
    layerIndexTracker[0] = 0;
    
    
    // set first layer's activation func to address of default func
    funcs[0] = &defaultfunc;
    
    
    // Loop and compute index tracking values,
    // assign the nodes per layer,
    // and set default value for activation funcs
    for (int i = 1; i < Nh+1; i++) {
        nodesPerLayer[i] = Nn;
        funcs[i] = &defaultfunc;
        if( i == 1 ){
            layerIndexTracker[i] = Nn*(I+1);
        }else{
            layerIndexTracker[i] = Nn*(Nn+1) + layerIndexTracker[i-1];
        }
    }
    nodesPerLayer[Nh+1] = O;
}







// Neural Network Destructor
template<int I, int O, int Nh, int Nn>
NeuralNetwork<I,O,Nh,Nn>::~NeuralNetwork(){
    if( weights != 0 ){
        delete weights; weights = 0;
    }

    
    if( funcs != 0 ){
        delete [] funcs; funcs = 0;
    }
}









// Operator to compute value based on input
template<int I, int O, int Nh, int Nn>
typename NeuralNetwork<I,O,Nh,Nn>::Output NeuralNetwork<I,O,Nh,Nn>::operator()( const Input & input ) const
{
    Output out;
    (*this)(input, out);
    return out;
}








// Main operator of Neural Network
//
// Take input, compute values based on it,
// and assign resulting value to output variable passed in as an argument
template<int I, int O, int Nh, int Nn>
void NeuralNetwork<I,O,Nh,Nn>::operator()( const Input & input, Output & output ) const{
    
    // represents the last layer computation was done on
    Coordinate<Nn> preLayerValues;
    
    // represents latest layer computation was done for
    Coordinate<Nn> postLayerValues;

    
    // If the activation functions are null, don't proceed
    if( funcs == 0 ){ return; }
    
    
    
    // Specify number of layers where computation occurs
    int numLayerComputations = Nh + 1;
    int numConnections = 0;
    int counter = 0;
    double sum = 0;

    
    
    
    // Loop through the layers that do computation
    for(int iL = 0; iL < numLayerComputations; iL++ ){

        // Compute number of nodes for layers
        int preLayerCnt = nodesPerLayer[iL]+1;
        int nextLayerCnt = nodesPerLayer[iL+1];
        
        // Compute the number of connections
        numConnections = preLayerCnt * nextLayerCnt;

        // Initialize counter to left layer's tracker value
        counter = layerIndexTracker[iL];
        
        
        
        // If the current right layer is also the output layer
        if( iL+1 == numLayerComputations ){
            
            // If the ANN is only an input and output layer
            // and there's no hidden layers
            if( numLayerComputations == 1 ){
                
                // Loop through connections between layers
                // and do appropriate computation
                for(int nN = 0; nN < nextLayerCnt; nN++ ){
                    sum = 0.0;
                    for( int oN = 0; oN < preLayerCnt-1; oN++ ){
                        sum += (*weights)[counter]*input[oN];
                        counter++;
                    }
                    sum += (*weights)[counter];
                    counter++;
                    output[nN] = (*funcs[iL])(sum);
                }
                
            // If the ANN has some hidden layer
            }else{
            
                // Loop through connections between layers
                // and do appropriate computation
                for(int nN = 0; nN < nextLayerCnt; nN++ ){
                    sum = 0.0;
                    for( int oN = 0; oN < preLayerCnt-1; oN++ ){
                        sum += (*weights)[counter]*preLayerValues[oN];
                        counter++;
                    }
                    sum += (*weights)[counter];
                    counter++;
                    output[nN] = (*funcs[iL])(sum);
                }
            }
            
            
            
        // If the current left layer is the input layer
        }else if( iL == 0 ){
            
            // Loop through connections between layers
            // and do appropriate computation
            for(int nN = 0; nN < nextLayerCnt; nN++ ){
                sum = 0.0;
                for( int oN = 0; oN < preLayerCnt-1; oN++ ){
                    sum += (*weights)[counter]*input[oN];
                    counter++;
                }
                sum += (*weights)[counter];
                counter++;
                postLayerValues[nN] = (*funcs[iL])(sum);
            }
            preLayerValues = postLayerValues;
            
            
            
            
        // If the layer pair doesn't include the input or output layer
        }else{
            
            // Loop through connections between layers
            // and do appropriate computation
            for(int nN = 0; nN < nextLayerCnt; nN++ ){
                sum = 0.0;
                for( int oN = 0; oN < preLayerCnt-1; oN++ ){
                    sum += (*weights)[counter]*preLayerValues[oN];
                    counter++;
                }
                sum += (*weights)[counter];
                counter++;
                postLayerValues[nN] = (*funcs[iL])(sum);
            }
            preLayerValues = postLayerValues;
        }
        
    }// end for loop

}// end operator( , )





/*!
 * Method to do back propogation.
 * Currently not complete.
 *
 */
template<int I, int O, int Nh, int Nn>
void NeuralNetwork<I,O,Nh,Nn>::backPropogate( const Input & input, const Output & output ){
    Coordinate<Nn> layerValues;
    Output approx;
    (*this)(input, approx);
    
}



/*!
 * Method to assign a value to a weight, based on the left layer the weight stems from,
 * the node number in the left layer, and the node number in the right layer
 *
 */
template<int I, int O, int Nh, int Nn>
double & NeuralNetwork<I,O,Nh,Nn>::operator()(int preLayer, int nodeLeft, int nodeRight){
    int n = 0;
    if( preLayer == 0 ){ n = I; }
    else{ n = Nn; }
    int index = layerIndexTracker[preLayer] + n*nodeRight + nodeLeft;
    return (*weights)[index];
}




/*!
 * Method to grab a weight, based on the left layer it stems from,
 * the node number in the left layer, and the node number in the right layer
 *
 */
template<int I, int O, int Nh, int Nn>
const double & NeuralNetwork<I,O,Nh,Nn>::operator()(int preLayer, int nodeLeft, int nodeRight) const{
    int n = 0;
    if( preLayer == 0 ){ n = I; }
    else{ n = Nn; }
    int index = layerIndexTracker[preLayer] + n*nodeRight + nodeLeft;
    return (*weights)[index];
}



/*!
 * This method changes the value of a weight by referencing it's 1D index
 *
 */
template<int I, int O, int Nh, int Nn>
double & NeuralNetwork<I,O,Nh,Nn>::operator[](int index){
    return (*weights)[index];
}



/*!
 * This method obtains the value of a weight by referencing it's 1D index
 *
 */
template<int I, int O, int Nh, int Nn>
const double & NeuralNetwork<I,O,Nh,Nn>::operator[](int index) const{
    return (*weights)[index];
}


#endif