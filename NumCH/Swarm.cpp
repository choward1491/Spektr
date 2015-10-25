//
//  Swarm.cpp
//  Data_Structs
//
//  Created by Christian J Howard on 9/4/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#include "Swarm.h"



#ifndef _swarm_cpp_
#define _swarm_cpp_


// Initialize the swarm
template<int Dim>
Swarm<Dim>::Swarm( int numParticles ):p(numParticles){
    func = 0;
    maxIters = 100;
    printStatus = true;
}






// Method to do the optimization
template<int Dim>
void Swarm<Dim>::runOptimization(){
    
    // Initialize variables for optimization algorithm
    int currIter = 0;
    int minIndex = -1;
    double minCost = 1e250;
    Coordinate<Dim> bestPose;
    
    // If no cost function is assigned, end the optimization
    // with an appropriate message
    if( func == 0 ){
        printf("Optimization couldn't run! No cost function setup.\n");
        return;
    }
    
    // While we haven't hit the max number of iterations
    while ( currIter < maxIters ) {
        
        
        // Loop through the points
        for (int i = 0; i < p.size() ; i++ ) {
            
            // Obtain the cost for this particle
            p[i].cost = (*func)(p[i].pose);
            
            // Check if it's the global best
            if( p[i].cost < minCost ){
                minCost = p[i].cost;
                minIndex = i;
            }
            
            // Check if this value is the particle's
            // personal best
            if( p[i].cost < p[i].bestCost ){
                p[i].bestCost = p[i].cost;
                p[i].best = p[i].pose;
            }
        }
        
        
        
        // Loop through points
        for( int i = 0; i < p.size(); i++ ){
            
            // Update position of particles based on global best
            p[i].updateState( p[minIndex].pose );
        }
        
        
        
        
        // increment current iteration
        currIter++;
        
        
        // Print status message
        if( printStatus ){
            printf("Current Iteration = %i | Current Min Cost = %lf\n", currIter, minCost);
        }
    }
    
}






/*!
 * Method to get an ordered set of the best N results from the optimization
 *
 */
template<int Dim>
typename Swarm<Dim>::Result Swarm<Dim>::getResults( int numberOfTopPoints ){
    
    // Initialize min heap
    Result results(numberOfTopPoints);
    
    // Initialize max heap
    MaxHeap<double, Coordinate<Dim>> set(numberOfTopPoints);
    
    // Loop through the swarm particles
    for (int i = 0; i < p.size(); i++ ) {
        
        // Add particles to max heap if their cost are smaller
        // than the current largest in the max heap or the heap isn't full
        if( set.size() < numberOfTopPoints || p[i].bestCost < set.getRootKey() ){
            if( set.size() >= numberOfTopPoints ){
                set.pop();
            }
            set.push( p[i].bestCost, p[i].best );
        }
    }
    
    // Add the best points to the min heap
    for( int i = 0; i < numberOfTopPoints; i++ ){
        results.push( set.getRootKey(), set.getRootData() );
        set.pop();
    }
    
    // return results
    return results;
}


#endif
