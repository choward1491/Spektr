//
//  NNNeighbors.hpp
//  NumCH
//
//  Created by Christian J Howard on 12/28/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef NNNeighbors_hpp
#define NNNeighbors_hpp

#include <stdio.h>
#include "LinkedList.hpp"


namespace ANN {

class Neighbors {
public:
    typedef LinkedList<unsigned int> IDList;
    typedef IDList::Iter Iter;
    
    
    Neighbors();
    void connectForwardNode( unsigned int nodeID );
    void connectBackwardNode( unsigned int nodeID );
    
    
    Iter beginForward();
    Iter beginBackward();
    
    
private:
    IDList forward;
    IDList backward;
};
    
    
}

#endif /* NNNeighbors_hpp */
