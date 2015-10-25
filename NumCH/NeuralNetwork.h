//
//  NeuralNetwork.h
//  Data_Structs
//
//  Created by Christian J Howard on 9/16/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#ifndef __Data_Structs__NeuralNetwork__
#define __Data_Structs__NeuralNetwork__

#include <stdio.h>
#include "Coordinate.h"
#include "NodeFunc.h"



// preprocessoer method to compute the total number of weights
#define NumWeights(I,O,Nh,Nn) (Nh>0)*( (1+I)*Nn + (Nn+1)*Nn*(Nh-1) + (Nn+1)*O) + (Nh<1)*(I+1)*O




/*!
 * This class represents a multi-layer Artificial Neural Network.
 * This template class works by specifying the number of inputs, the number of outputs,
 * the number of hidden layers, and the number of nodes per hidden layer.
 *
 * This approach does assume the hidden layers have the same number of nodes.
 *
 */
template<int I, int O, int NumHiddenLayers, int NodesPerHiddenLayer>
class NeuralNetwork {
public:
    
    // compute number of weights for this classs
    static const int numWeights = NumWeights(I,O,NumHiddenLayers,NodesPerHiddenLayer);
    
    //
    // Define typedefs to make code more readable
    //
    typedef Coordinate<numWeights> Weights;
    typedef Coordinate<I> Input;
    typedef Coordinate<O> Output;
    typedef NodeFunc ActivationFuncs;
    
    
    //
    // Neural Network constructor
    //
    NeuralNetwork();

    //
    // Neural Network Destructor
    //
    ~NeuralNetwork();
    

    //
    // Operators for computing values using neural network
    //
    Output operator()( const Input & input ) const;
    void operator()( const Input & input, Output & output ) const;
    
    
    /*!
     * Methods to get/set a weight, based on the left layer it stems from,
     * the node number in the left layer, and the node number in the right layer
     *
     */
    double & operator()(int preLayer, int nodeLeft, int nodeRight);
    const double & operator()(int preLayer, int nodeLeft, int nodeRight) const;
    
    /*!
     * Methods to get/set the value of a weight by referencing it's 1D index
     *
     */
    double & operator[](int index);
    const double & operator[](int index) const;
    
    
    //
    // Back propogation algorithm
    //
    void backPropogate( const Input & input, const Output & output );

    //
    // Method to save the weights to file
    //
    void saveWeights(char* filename);
    



    //
    // Provides the pointer to the weights,
    // in the event the neural network will be
    // formed using a non-derivative method
    // like PSO or GA
    //
    Weights * getWeightsPointer(){ return weights; }


    //
    // Get the weight value at a given index
    //
    double getWeight(int index) const { return (*weights)[index]; }

    //
    // Print the weights to the screen
    //
    void printWeightsLn(){ weights->println(); }

    //
    // Get the number of weights in the network
    //
    int size() const { return numWeights; }


    //
    // Get the number of functions in the network
    //
    int numFuncs() const { return NumHiddenLayers + 1; }
    
    
    // This method represents a list of the activation functions.
    ActivationFuncs** funcs;
    


private:
    
    // Weights for neural network
    Weights* weights;
    
    // This is the default node func, which is actually linear
    NodeFunc defaultfunc;

    // array that holds the number of nodes in the ith layer
    int nodesPerLayer[NumHiddenLayers+2];
    
    // array that holds weight counter up to ith layer to more efficiently
    // obtain weight index
    int layerIndexTracker[NumHiddenLayers+1];
    
    
};


#ifndef _ann_cpp_
#include "NeuralNetwork.cpp"
#endif

#endif /* defined(__Data_Structs__NeuralNetwork__) */
