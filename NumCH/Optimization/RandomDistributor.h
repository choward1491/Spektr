//
//  RandomDistributor.h
//  Data_Structs
//
//  Created by Christian J Howard on 9/4/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#ifndef __Data_Structs__RandomDistributor__
#define __Data_Structs__RandomDistributor__

#include <stdio.h>
#include "RandomNumberGenerator.hpp"
#include "ParticleDistributor.h"


/*!
 * This class represents a pseudorandom particle distributor
 * to distribute particle swarm particles in the search domain
 */
template<int Dim>
class RandomDistributor : public ParticleDistributor<Dim> {
public:
    // specify valuable typedefs
    typedef SwarmParticle<Dim>  Particle;
    typedef Vec<Particle>       Particles;
    typedef Coordinate<2>       Point2D;
    
    
    // Overwrite the distribute method
    virtual void distribute( Particles & particles, Vec<Point2D> & bounds ){
        int numParticles = particles.size();
        double del = 0;
        
        // loop through all particles
        for (int i = 0; i < numParticles; i++) {
            
            // loop through each dimension
            for (int j = 0; j < Dim; j++) {
                
                //compute random location based on bound for current dimension
                del = generator.rand();
                particles[i].pose[j] = bounds[j][0]*(1-del) + bounds[j][1]*del;
            }
        }
    }
    
private:
    RandomNumberGenerator generator;
    
    
    
};


#endif /* defined(__Data_Structs__RandomDistributor__) */
