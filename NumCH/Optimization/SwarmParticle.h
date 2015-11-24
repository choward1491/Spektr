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



/*!
 * This class represents a D-Dimensional PSO swarm particle
 *
 * This class updates it's state based on various values
 * and keeps track of it's best solution
 */
template<int Dim>
class SwarmParticle {
public:
    typedef Coordinate<Dim> State;
    
    // default constructor
    SwarmParticle():bestCost(1e200),momentumCoef(0.5),particleBestCoef(0.7),globalBestCoef(0.1){}
    
    // method to update the particle position
    virtual void updateState( const State & bestPose );
    
    // current pose, velocity, and best pose states
    State pose;
    State velocity;
    State best;
    
    // bounding velocity, best cost, current cost
    double velBound;
    double bestCost;
    double cost;
    
    
    
    // Setter methods for coefficients in particle
    void setMomentumCoef( double mc ){ momentumCoef = mc; }
    void setParticleBestCoef( double pc ){ particleBestCoef = pc; }
    void setGlobalBestCoef( double gc ){ globalBestCoef = gc; }
    
    
private:
    double momentumCoef;
    double particleBestCoef;
    double globalBestCoef;
    
    
};

#ifndef _swarmparticle_cpp_
#include "SwarmParticle.cpp"
#endif

#endif /* defined(__Data_Structs__SwarmParticle__) */
