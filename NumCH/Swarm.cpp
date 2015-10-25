//
//  Swarm.cpp
//  Data_Structs
//
//  Created by Christian J Howard on 9/4/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#include "Swarm.h"



/*
typedef SwarmParticle<Dim> Particle;
typedef Vec<Particle> Particles;
typedef CostFunc<Dim> Cost;
typedef MinHeap<double, Coordinate<Dim>> Result;
 */

#ifndef _swarm_cpp_
#define _swarm_cpp_

template<int Dim>
Swarm<Dim>::Swarm( int numParticles ):p(numParticles){
    func = 0;
    maxIters = 100;
}

template<int Dim>
void Swarm<Dim>::runOptimization(){
    int currIter = 0;
    int minIndex = -1;
    double minCost = 1e250;
    double tmpIndex = -1;
    Coordinate<Dim> bestPose;
    
    if( func == 0 ){
        printf("Optimization couldn't run! No cost function setup.\n");
        return;
    }
    
    while ( currIter < maxIters ) {
        
        for (int i = 0; i < p.size() ; i++ ) {
            if( i != minIndex ){
                p[i].cost = (*func)(p[i].pose);
                
                if( p[i].cost < minCost ){
                    minCost = p[i].cost;
                    tmpIndex = i;
                }
                if( p[i].cost < p[i].bestCost ){
                    p[i].bestCost = p[i].cost;
                    p[i].best = p[i].pose;
                }
            }
        }
        
        minIndex = tmpIndex;
        
        for( int i = 0; i < p.size(); i++ ){
            p[i].updateState( p[minIndex].pose );
        }
        
        currIter++;
        printf("Current Iteration = %i\n", currIter);
    }
    
}

template<int Dim>
typename Swarm<Dim>::Result Swarm<Dim>::getResults( int numberOfTopPoints ){
    Result results(numberOfTopPoints);
    MaxHeap<double, Coordinate<Dim>> set(numberOfTopPoints);
    
    for (int i = 0; i < p.size(); i++ ) {
        if( set.size() < numberOfTopPoints || p[i].bestCost < set.getRootKey() ){
            if( set.size() >= numberOfTopPoints ){
                set.pop();
            }
            set.push( p[i].bestCost, p[i].best );
        }
    }
    
    for( int i = 0; i < numberOfTopPoints; i++ ){
        results.push( set.getRootKey(), set.getRootData() );
        set.pop();
    }
    
    return results;
}


#endif
    
    //Cost* func;
    //Particles p;
    //int maxIters;
