//
//  Swarm.h
//  Data_Structs
//
//  Created by Christian J Howard on 9/4/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#ifndef __Data_Structs__Swarm__
#define __Data_Structs__Swarm__

#include <stdio.h>
#include "ParticleDistributor.h"
#include "CostFunc.h"
#include "heap.h"





template<int Dim>
class Swarm {
public:
    typedef SwarmParticle<Dim> Particle;
    typedef Vec<Particle> Particles;
    typedef CostFunc<Dim> Cost;
    typedef MinHeap<double, Coordinate<Dim>> Result;
    typedef ParticleDistributor<Dim> Distributor;
    typedef Coordinate<2> Point2D;
    typedef Vec<Point2D> Bounds;
    
    
    
    
    Swarm( int numParticles );
    void assignBounds( Bounds * newBounds ){ bounds = newBounds; }
    void assignDistributor( Distributor* _distributor ){ distributor = _distributor; }
    void initializePoints(){ if( distributor != 0 ){ distributor->distribute(p, *bounds); } }
    void assignCostFunc( Cost* _func ){ func = _func; }
    void setMaxIters( int _maxIters = 100 ){ maxIters = _maxIters; }
    void runOptimization();
    Result getResults( int numberOfTopPoints );
    
    Particles p;
    
private:
    
    Bounds* bounds;
    Distributor* distributor;
    Cost* func;
    
    int maxIters;
};


#ifndef _swarm_cpp_
#include "Swarm.cpp"
#endif


#endif /* defined(__Data_Structs__Swarm__) */
