//
//  SwarmParticle.h
//  Data_Structs
//
//  Created by Christian J Howard on 9/4/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#ifndef __Data_Structs__SwarmParticle__
#define __Data_Structs__SwarmParticle__

#include <stdio.h>
#include "Coordinate.h"
#include <math.h>


template<int Dim>
class SwarmParticle {
public:
    SwarmParticle():bestCost(1e200){}
    typedef Coordinate<Dim> State;
    virtual void updateState( const State & bestPose );
    State pose;
    State velocity;
    State best;
    double velBound;
    double bestCost;
    double cost;
    
    
};

#ifndef _swarmparticle_cpp_
#include "SwarmParticle.cpp"
#endif

#endif /* defined(__Data_Structs__SwarmParticle__) */
