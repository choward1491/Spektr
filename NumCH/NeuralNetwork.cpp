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


template<int I, int O, int Nh, int Nn>
NeuralNetwork<I,O,Nh,Nn>::NeuralNetwork(){
    weights = new Weights;
    funcs = new ActivationFuncs*[Nh+1];
    nodesPerLayer[0] = I;
    layerIndexTracker[0] = 0;
    funcs[0] = &defaultfunc;
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








template<int I, int O, int Nh, int Nn>
NeuralNetwork<I,O,Nh,Nn>::~NeuralNetwork(){
    if( weights != 0 ){
        delete weights; weights = 0;
    }

    
    if( funcs != 0 ){
        delete [] funcs; funcs = 0;
    }
}










template<int I, int O, int Nh, int Nn>
typename NeuralNetwork<I,O,Nh,Nn>::Output NeuralNetwork<I,O,Nh,Nn>::operator()( const Input & input ) const {
    Output out;
    (*this)(input, out);
    return out;
}









template<int I, int O, int Nh, int Nn>
void NeuralNetwork<I,O,Nh,Nn>::operator()( const Input & input, Output & output ) const{
    Coordinate<Nn> preLayerValues;
    Coordinate<Nn> postLayerValues;

    if( funcs == 0 ){ return; }
    int numLayerComputations = Nh + 1;
    int numConnections = 0;
    int counter = 0;
    double sum = 0;

    for(int iL = 0; iL < numLayerComputations; iL++ ){

        int preLayerCnt = nodesPerLayer[iL]+1;
        int nextLayerCnt = nodesPerLayer[iL+1];
        numConnections = preLayerCnt * nextLayerCnt;

        counter = layerIndexTracker[iL];
        if( iL+1 == numLayerComputations ){
            
            if( numLayerComputations == 1 ){
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
            }else{
            
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
        }else if( iL == 0 ){
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
        }else{
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
        
        
        
    }

    
    

}








template<int I, int O, int Nh, int Nn>
void NeuralNetwork<I,O,Nh,Nn>::backPropogate( const Input & input, const Output & output ){
    Coordinate<Nn> layerValues;
    Output approx;
    (*this)(input, approx);
    
}


template<int I, int O, int Nh, int Nn>
double & NeuralNetwork<I,O,Nh,Nn>::operator()(int preLayer, int nodeLeft, int nodeRight){
    int n = 0;
    if( preLayer == 0 ){ n = I; }
    else{ n = Nn; }
    int index = layerIndexTracker[preLayer] + n*nodeRight + nodeLeft;
    return (*weights)[index];
}

template<int I, int O, int Nh, int Nn>
const double & NeuralNetwork<I,O,Nh,Nn>::operator()(int preLayer, int nodeLeft, int nodeRight) const{
    int n = 0;
    if( preLayer == 0 ){ n = I; }
    else{ n = Nn; }
    int index = layerIndexTracker[preLayer] + n*nodeRight + nodeLeft;
    return (*weights)[index];
}

template<int I, int O, int Nh, int Nn>
double & NeuralNetwork<I,O,Nh,Nn>::operator[](int index){
    return (*weights)[index];
}

template<int I, int O, int Nh, int Nn>
const double & NeuralNetwork<I,O,Nh,Nn>::operator[](int index) const{
    return (*weights)[index];
}


#endif