//
//  ANN.hpp
//  NumCH
//
//  Created by Christian J Howard on 12/28/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef ANN_hpp
#define ANN_hpp

#include <stdio.h>
#include <vector>
#include "Neighbors.hpp"
#include "Node.hpp"
#include "ActivationFunc.hpp"
#include "ActivationFactory.hpp"

class Builder;

namespace ANN{
    
    typedef ActivationFactory::Type FuncType;

    
    class Network {
    public:
        Network();
        Network( const std::vector<int> & layers );
        
        void setLayers( const std::vector<int> & layers );
        void addPair( Pair & p );
        void addPair( int leftLayer, int ln, int rightLayer, int rn );
        
        void setNodeFunc( unsigned int nodeID, FuncType type );
        void setNodeFunc( int layer, int localnode, FuncType type );
        void setLayerFunc( int layer , FuncType type );
        
        void setWeight( double value, int leftlayer, int lnode, int rightLayer, int rnode );
        void setWeight( double value, int index);
        void randomizeWeights();
        
        void print() const;
        
        std::vector<double> operator()( const std::vector<double> & input );
        
        
    private:
        void buildNetwork( const std::vector<int> & layers );
        
        bool setInput( const std::vector<double> & in);
        std::vector<double> getOutput();
        
        friend class Builder;
        int numIn;
        int numOut;
        std::vector<Neighbors> nbrs;
        std::vector<Node> nodes;
        std::vector<ActivationFunc*> funcs;
        ActivationFactory factory;
        std::vector<int> layerSizes;
        std::vector<int> startIndices;
        Weights w;
    };
    
    
}

#endif /* ANN_hpp */
