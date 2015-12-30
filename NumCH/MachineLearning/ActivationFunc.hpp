//
//  ActivationFunc.hpp
//  NumCH
//
//  Created by Christian J Howard on 12/28/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef ActivationFunc_hpp
#define ActivationFunc_hpp

#include <stdio.h>
#include <vector>
#include "Neighbors.hpp"
#include "Weights.hpp"
#include "Node.hpp"


namespace ANN {
    
class ActivationFactory;

class ActivationFunc {
public:
    
    struct Output{
        double activation;
        double derivative;
    };
    
    virtual Output operator()(double input) = 0;
    virtual ~ActivationFunc(){}
    
    virtual double Z(unsigned int id, Neighbors::Iter & iter,
                                 std::vector<Node> & nodes, Weights & w )
    {
        Pair p;
        p.iTo = id;
        double weight = 0.0;
        double sum = 0.0;
        
        for (; !iter.atEnd(); iter++) {
            p.iFrom = iter.n->data;
            weight = w(p);
            sum += weight * nodes[p.iFrom].getNetOutput();
        }
        
        return sum;
    }
    
    virtual double dZdX( unsigned int id, unsigned int nid,
                         std::vector<Node> & nodes, Weights & w )
    {
        Pair p{nid,id};
        return w(p);
    }
};

}
#endif /* ActivationFunc_hpp */
