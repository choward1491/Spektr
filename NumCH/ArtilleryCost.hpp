//
//  ArtilleryCost.hpp
//  Data_Structs
//
//  Created by Christian J Howard on 10/16/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef ArtilleryCost_hpp
#define ArtilleryCost_hpp

#include <stdio.h>
#include "CostFunc.h"
#include "PseudoRandomGenerator.h"
#include "NeuralNetwork.h"
#include "Sigmoid.h"


class ArtilleryCost : public CostFunc<13> {
public:
    ArtilleryCost(){
        net.funcs[0] = &func;
        net.funcs[1] = &func;
    }
    typedef Coordinate<13> State;
    typedef Coordinate<(13*14)/2> Hessian;
    typedef PseudoRandomGenerator PRG;
    typedef NeuralNetwork<4, 2, 1, 1> ANN;
    virtual double operator()( State & x );
    virtual double gradient( State & x, State & gradient, Hessian * hessian = 0 );
    
private:
    PRG rnd;
    ANN net;
    Sigmoid func;
    
};

#endif /* ArtilleryCost_hpp */
