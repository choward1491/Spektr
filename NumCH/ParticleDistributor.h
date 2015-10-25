//
//  ParticleDistributor.h
//  Data_Structs
//
//  Created by Christian J Howard on 9/4/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#ifndef __Data_Structs__ParticleDistributor__
#define __Data_Structs__ParticleDistributor__

#include <stdio.h>
#include "SwarmParticle.h"
#include "Vec.h"
#include <math.h>


/*!
 * This is a abstract base class that represents a
 * particle swarm particle distributor
 *
 */
template<int Dim>
class ParticleDistributor {
public:
    // specify valuable swarm particle typedefs
    typedef SwarmParticle<Dim> Particle;
    typedef Vec<Particle> Particles;
    typedef Coordinate<2> Point2D;
    
    // abstract virtual method to distribute particles
    virtual void distribute( Particles & particles, Vec<Point2D> & bounds ) = 0;
    
    
};

#endif /* defined(__Data_Structs__ParticleDistributor__) */
