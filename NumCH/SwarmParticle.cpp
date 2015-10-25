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

template<int Dim>
void SwarmParticle<Dim>::updateState( const State & globalBestPose ){

    for (int i = 0; i < Dim; i++ ) {
        velocity[i] = 0.5*velocity[i] + 0.7*(best[i]-pose[i]) + 0.1 * (globalBestPose[i] - pose[i]);
        if( fabs(velocity[i]) > velBound ){
            velocity[i] = 0;
        }
        pose[i] = pose[i] + velocity[i];
    }
}

#endif