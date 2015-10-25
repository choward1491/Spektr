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




/*!
 * This is a class representing a particle swarm
 * that will be used in a PSO solution for a D-Dimensional Problem
 */
template<int Dim>
class Swarm {
public:
    
    // typedef variable quantities to make them easy to read
    typedef SwarmParticle<Dim>                  Particle;
    typedef Vec<Particle>                       Particles;
    typedef CostFunc<Dim>                       Cost;
    typedef MinHeap<double, Coordinate<Dim>>    Result;
    typedef ParticleDistributor<Dim>            Distributor;
    typedef Coordinate<2>                       Point2D;
    typedef Vec<Point2D>                        Bounds;
    
    
    
    // Initialize a swarm based on a number of particles
    Swarm( int numParticles );
    
    
    
    // Assign the search bounds (must be assigned before initializing points)
    void assignBounds( Bounds * newBounds ){ bounds = newBounds; }
    
    // Assign the swarm particle distributor (must be assigned before initializing points)
    void assignDistributor( Distributor* _distributor ){ distributor = _distributor; }
    
    // Method to initialize the points
    void initializePoints(){ if( distributor != 0 ){ distributor->distribute(p, *bounds); } }
    
    
    
    
    // Method to set cost function (must be assigned before doing optimization)
    void assignCostFunc( Cost* _func ){ func = _func; }
    
    // Method to set max number of iterations
    void setMaxIters( int _maxIters ){ maxIters = _maxIters; }
    
    // Method to run an optimization
    void runOptimization();
    
    
    
    // Choose to print iteration status or not
    void setPrintStatus( bool choice ){ printStatus = choice; }
    
    
    // Method to obtain the best N results
    // in the form of a min heap
    Result getResults( int numberOfTopPoints );
    
    
    
    
    // List of particles
    Particles p;
    
private:
    
    // Bounds, distributor, and cost function references
    Bounds* bounds;
    Distributor* distributor;
    Cost* func;
    
    // Flag to print Iteration status or not. Defaults to true
    bool printStatus;
    
    // Maximum number of iterations
    int maxIters;
};


#ifndef _swarm_cpp_
#include "Swarm.cpp"
#endif


#endif /* defined(__Data_Structs__Swarm__) */
