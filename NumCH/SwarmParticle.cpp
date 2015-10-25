//
//  SwarmParticle.cpp
//  Data_Structs
//
//  Created by Christian J Howard on 9/4/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#include "SwarmParticle.h"


#ifndef _swarmparticle_cpp_
#define _swarmparticle_cpp_

/*!
 * This method updates a particle in the swarm using a momentum approach
 *
 */
template<int Dim>
void SwarmParticle<Dim>::updateState( const State & globalBestPose ){

    for (int i = 0; i < Dim; i++ ) {
        
        // update velocity based on momentum, current best location,
        // and best location globally
        velocity[i] = momentumCoef      * velocity[i] +
                      particleBestCoef  * (best[i]-pose[i]) +
                      globalBestCoef    * (globalBestPose[i] - pose[i]);
        
        
        // If velocity exceeds limit, set it back to 0
        if( fabs(velocity[i]) > velBound ){
            velocity[i] = 0;
        }
        
        
        // Update position
        pose[i] = pose[i] + velocity[i];
    }
}

#endif