//
//  NNNeighbors.cpp
//  NumCH
//
//  Created by Christian J Howard on 12/28/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "Neighbors.hpp"

namespace ANN{
    
    
    Neighbors::Neighbors(){
        
    }
    void Neighbors::connectForwardNode( unsigned int nodeID ){
        forward.push(nodeID);
    }
    void Neighbors::connectBackwardNode( unsigned int nodeID ){
        backward.push(nodeID);
    }
    
    
    Neighbors::Iter Neighbors::beginForward(){
        return forward.begin();
    }
    Neighbors::Iter Neighbors::beginBackward(){
        return backward.begin();
    }
    
    
    
}