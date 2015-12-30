//
//  Builder.cpp
//  NumCH
//
//  Created by Christian J Howard on 12/28/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "Builder.hpp"

namespace ANN {
    
    Builder::Builder(){
        
    }
    void Builder::operator()( Network & net , Builder::Type type ){
        switch (type) {
            case FeedForward:
            default:
                feedForwardSetup(net);
                break;
        }
    }
    
    void Builder::buildNetwork( Network & net, Builder::Type type ){
        this->operator()(net,type);
    }
    
    void Builder::feedForwardSetup( Network & net ){
        if( net.layerSizes.size() == 0 ){ return; }
        
        int iter = 0, iFrom = 0, iTo = 0;
        int nlL, nlR;
        
        for (int i = 1; i < net.layerSizes.size(); i++) {
            iFrom = iTo; iTo = i;
            nlL = net.layerSizes[iFrom]; nlR = net.layerSizes[iTo]-(i!=net.layerSizes.size()-1);
            
            buildConnectionsBetweenLayers( net, iter, nlL, nlR );
            
            if( i < net.layerSizes.size()-1){ net.setLayerFunc( i , FuncType::Sigmoid ); }
            else{ net.setLayerFunc( i , FuncType::Linear ); }
            
            iter += nlL;
            net.nodes[iter-1].makeBias();
        }
    }
    
    void Builder::buildConnectionsBetweenLayers( Network & net, int si, int nL, int nR ){
        ANN::Pair p;
        
        for (int il = 0; il < nL; il++) {
            p.iFrom = si + il;
            
            for (int ir = 0; ir < nR; ir++) {
                p.iTo = si + nL + ir;
                net.addPair(p);
            }
        }
    }
    
    
}