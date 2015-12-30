//
//  GaussRBF.hpp
//  NumCH
//
//  Created by Christian J Howard on 12/28/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef GaussRBF_hpp
#define GaussRBF_hpp

#include "ActivationFunc.hpp"

namespace ANN {
    
    class GaussRBF : public ActivationFunc {
    public:
        
        virtual Output operator()(double input){
            double e = exp(-input);
            return Output{e,-e};
        }
        virtual ~GaussRBF(){}
        
        virtual double Z(unsigned int id, Neighbors::Iter & iter,
                         std::vector<Node> & nodes, Weights & w )
        {
            Pair p;
            p.iTo = id;
            double eps = 1e-8;
            double weight = 0.0;
            double sum = 0.0;
            
            
            /*for (; !iter.atEnd(); iter++) {
                p.i1 = iter.n->data;
                weight = w(p);
                sum += weight * nodes[p.i1].getNetOutput();
            }*/
            
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

#endif /* GaussRBF_hpp */
